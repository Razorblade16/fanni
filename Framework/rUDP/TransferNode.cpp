/*
 * TransferNode.cpp
 *
 *  Created on: Oct 18, 2009
 *      Author: lulu
 */

#include <list>

#include "fanni/Logger.h"
#include "DefaultPacketAckPacket.h"
#include "TransferNode.h"

using namespace std;
using namespace Poco;
using namespace Poco::Net;
using namespace Fanni;

TransferNode::TransferNode(PacketFactory &packet_factory, const std::string &addr, uint16_t port, int thread_number) :
	packet_factory(packet_factory), isRunning(false) {
	DefaultPacketAckPacket packet;
	this->packet_factory.registerPacket(DefaultPacketAckPacket::DefaultPacketAck_ID, packet);
	// init scoket
	SocketAddress sock_addr(addr, port);
	this->socket.bind(sock_addr, true);
	// init Receiver, Sender
	this->receiver_manager = new ReceiverManager(thread_number, *this, this->packet_factory, this->packet_handler_factory);
	this->sender_manager = new SenderManager(thread_number, this->socket, *this, this->packet_factory);
	// init UDP server
	this->udp_server_handler = new UDPServerHandler(this->socket, *this->receiver_manager);
	this->reactor.addEventHandler(this->socket, NObserver<UDPServerHandler,
			ReadableNotification> (*this->udp_server_handler, &UDPServerHandler::onReadable));
	this->reactor.addEventHandler(this->socket, NObserver<UDPServerHandler,
			ShutdownNotification> (*this->udp_server_handler, &UDPServerHandler::onShutdown));
	// init timers
	this->check_ACK_timer = new Poco::Timer(0, 3000);
	this->check_RESEND_timer = new Poco::Timer(0, 3000);
	this->check_ALIVE_timer = new Poco::Timer(0, 15000);
}

TransferNode::~TransferNode() {
	delete this->receiver_manager;
	delete this->sender_manager;
	delete this->udp_server_handler;

	delete this->check_ACK_timer;
	delete this->check_RESEND_timer;
	delete this->check_ALIVE_timer;
}

void TransferNode::start() {
	TRACE_LOG("enter");
	// start UDP server
	INFO_LOG("start receiver sender");
	this->receiver_manager->start();
	this->sender_manager->start();
	INFO_LOG("start udp server");
	this->udp_server_thread.start(this->reactor);
	// start timers
	INFO_LOG("start ack resend timers");
	// TODO @@@ use dedicated thread pool
	this->check_ACK_timer->start(Poco::TimerCallback<TransferNode>(*this, &TransferNode::onCheckACKTimer));
	this->check_RESEND_timer->start(Poco::TimerCallback<TransferNode>(*this, &TransferNode::onCheckRESENDTimer));
	this->check_ALIVE_timer->start(Poco::TimerCallback<TransferNode>(*this, &TransferNode::onCheckALIVETimer));

	TRACE_LOG("exit");
}

void TransferNode::stop() {
	// stop timers
	INFO_LOG("stop ack resend timers");
	this->check_ACK_timer->stop();
	this->check_RESEND_timer->stop();
	this->check_ALIVE_timer->stop();
	// stop UDP server
	INFO_LOG("stop udp server");
	this->reactor.stop();
	this->udp_server_thread.join();
	INFO_LOG("stop receiver sender");
	this->receiver_manager->stop();
	this->sender_manager->stop();
}

void TransferNode::sendPacket(PacketBase *packet, const Poco::Net::SocketAddress &addr) {
	TRACE_LOG("enter");
	if (!packet->header.isResent()) {
		this->ac++;
		packet->setSequence(this->ac.value());
	}
	SenderTask *data = new SenderTask(packet, addr);
	this->sender_manager->deliverTask(data);
	TRACE_LOG("exit");
}

// PacketTransfer Management
void TransferNode::addConnection(ConnectionBase *connection) {
	INFO_LOG("add connection: " << connection->getAddr().toString());
	Poco::FastMutex::ScopedLock l(this->connection_map);
	// TODO @@@ check if already exists
	this->connection_map[connection->getAddr().toString()] = connection;
}

ConnectionBase *TransferNode::getConnection(const Poco::Net::SocketAddress &addr) {
	Poco::FastMutex::ScopedLock l(this->connection_map);
	return this->getConnection_nolock(addr);
}

ConnectionBase *TransferNode::getConnection_nolock(const Poco::Net::SocketAddress &addr) {
	CONNECTION_MAP::iterator it = this->connection_map.find(addr.toString());
	if (it == this->connection_map.end()) {
		// not found
		return NULL;
	} else {
		return it->second;
	}
}

void TransferNode::removeConnection(const Poco::Net::SocketAddress &addr) {
	Poco::FastMutex::ScopedLock l(this->connection_map);
	this->removeConnection_nolock(addr);
}

void TransferNode::removeConnection_nolock(const Poco::Net::SocketAddress &addr) {
	INFO_LOG("remove connection: " << addr.toString());
	ConnectionBase *connection = this->getConnection(addr);
	if (connection != NULL) {
		this->connection_map.erase(addr.toString());
		delete connection;
	}
}

void TransferNode::onCheckACKTimer(Poco::Timer &timer) {
	TRACE_LOG("enter");
	for (CONNECTION_MAP::iterator it = this->connection_map.begin(); it
			!= this->connection_map.end(); it++) {
		it->second->checkACK();
	}
	TRACE_LOG("exit");
}

void TransferNode::onCheckRESENDTimer(Poco::Timer &timer) {
	TRACE_LOG("enter");
	for (CONNECTION_MAP::iterator it = this->connection_map.begin(); it
			!= this->connection_map.end(); it++) {
		it->second->checkRESEND();
	}
	TRACE_LOG("exit");
}

void TransferNode::onCheckALIVETimer(Poco::Timer &timer) {
	TRACE_LOG("enter");
	Poco::FastMutex::ScopedLock l(this->connection_map);
	if (this->connection_map.empty())
		return;
	list<const Poco::Net::SocketAddress *> remove_connection_list;
	for (CONNECTION_MAP::iterator it = this->connection_map.begin(); it
			!= this->connection_map.end(); it++) {
		if (it->second->checkALIVE()) {
			remove_connection_list.push_back(&it->second->getAddr());
		}
	}
	if (remove_connection_list.size() > 0) {
		INFO_LOG("remove " << remove_connection_list.size() << " client connections");
		for (list<const Poco::Net::SocketAddress *>::iterator it =
				remove_connection_list.begin(); it
				!= remove_connection_list.end(); it++) {
			this->removeConnection_nolock(*(*it));
		}
	}
	TRACE_LOG("exit");
}

// Reliable Packet Transfer
void TransferNode::processIncomingPacket(const PacketBase *packet, const Poco::Net::SocketAddress &addr) {
	ConnectionBase *connection = NULL;
	if (this->isNewConnection(packet)) {
		connection = this->createConnection(packet, addr);
		this->addConnection(connection);
	} else {
		connection = this->getConnection(addr);
	}
	if (connection) {
		connection->processIncomingPacket(packet);
	} else {
		WARN_LOG("unknown packet from: " << addr.toString());
	}
}

void TransferNode::processOutgoingPacket(const PacketBase *packet, const Poco::Net::SocketAddress &addr) {
	ConnectionBase *connection = this->getConnection(addr);
	if (connection) {
		connection->processOutgoingPacket(packet);
	} else {
		WARN_LOG("unknown packet to: " << addr.toString());
	}
}

PacketHandlerFactory &TransferNode::getPacketHandlerFactory() {
	return this->packet_handler_factory;
}

