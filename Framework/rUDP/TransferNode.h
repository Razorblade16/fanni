/*
 * TransferNode.h
 *
 *  Created on: Oct 18, 2009
 *      Author: lulu
 */

#ifndef TRANSFERNODE_H_
#define TRANSFERNODE_H_

#include <string>
#include <tr1/unordered_map>
#include "Poco/Thread.h"
#include "Poco/Timer.h"
#include "Poco/Mutex.h"
#include "Poco/AtomicCounter.h"
#include "Poco/Net/SocketReactor.h"

#include "fanni/LockableTemplate.h"
#include "Packets/PacketHeader.h"
#include "Packets/PacketBase.h"
#include "Receiver.h"
#include "Sender.h"
#include "ConnectionBase.h"
#include "UDPReceiveHandler.h"

namespace Fanni {

class TransferNode {
protected:
	PacketFactory &packet_factory;
	PacketHandlerFactory packet_handler_factory;

	// UDP server
	Poco::Net::DatagramSocket socket;
	Poco::Net::SocketReactor reactor;
	Poco::Thread udp_server_thread;
	UDPServerHandler *udp_server_handler;
	ReceiverManager *receiver_manager;
	SenderManager *sender_manager;
	// Timers
	Poco::Timer *check_ACK_timer;
	Poco::Timer *check_RESEND_timer;
	Poco::Timer *check_ALIVE_timer;
	void onCheckACKTimer(Poco::Timer &timer);
	void onCheckRESENDTimer(Poco::Timer &timer);
	void onCheckALIVETimer(Poco::Timer &timer);

	Poco::AtomicCounter ac;
	bool isRunning;

public:
	TransferNode(PacketFactory &packet_factory, const std::string &addr, uint16_t port, int thread_number);
	virtual ~TransferNode();

	virtual void start();
	virtual void stop();
	virtual void sendPacket(PacketBase *packet, const Poco::Net::SocketAddress &addr);

	// Reliable Packet Transfer
	void processIncomingPacket(const PacketBase *packet, const Poco::Net::SocketAddress &addr);
	void processOutgoingPacket(const PacketBase *packet, const Poco::Net::SocketAddress &addr);

	// Connection Management
private:
	typedef std::tr1::unordered_map<std::string, ConnectionBase *> __CONNECTION_MAP;
public:
	typedef lockable<__CONNECTION_MAP> CONNECTION_MAP;
private:
	CONNECTION_MAP connection_map;

	void removeConnection_nolock(const Poco::Net::SocketAddress &addr);
	ConnectionBase *getConnection_nolock(const Poco::Net::SocketAddress &addr);
public:
	virtual bool isNewConnection(const PacketBase *packet) = 0;
	virtual ConnectionBase *createConnection(const PacketBase *packet, const Poco::Net::SocketAddress &addr) = 0;
	void addConnection(ConnectionBase *connection);
	void removeConnection(const Poco::Net::SocketAddress &addr);
	ConnectionBase *getConnection(const Poco::Net::SocketAddress &addr);

public:
	PacketHandlerFactory &getPacketHandlerFactory();
};

}

#endif /* TRANSFERNODE_H_ */
