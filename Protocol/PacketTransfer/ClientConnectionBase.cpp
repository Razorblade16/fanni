/*
 * ClientConnectionBase.cpp
 *
 *  Created on: Aug 16, 2009
 *      Author: lulu
 */

#include "ClientConnectionBase.h"
#include "PacketTransferBase.h"
#include "FileTransferPackets/FileTransferPackets.h"
#include "FileTransferPackets/FileTransferPacketFactory.h"

using namespace std;
using namespace Fanni;

static const int MAX_ACK_NUMBER = 250;

ClientConnectionBase::ClientConnectionBase() {
	this->circuit_code = 0;
	this->transfer_peer = NULL;
	this->updateLastReceived();
}

ClientConnectionBase::ClientConnectionBase(uint32_t circuit_code, const EndPoint &ep, PacketTransferBase *transfer_peer) :
	circuit_code(circuit_code), ep(ep), transfer_peer(transfer_peer) {
	this->updateLastReceived();
}

ClientConnectionBase::~ClientConnectionBase() {
	for(RESEND_PACKET_MAP_TYPE::iterator it=this->resend_packet_map.begin(); it!=this->resend_packet_map.end(); it++) {
		delete it->second;
	}
}

void ClientConnectionBase::updateLastReceived() {
	this->last_packet_received = time(NULL);
}

void ClientConnectionBase::checkACK() {
	if (this->ack_packet_queue.empty()) return;
	PacketAckPacket *packet = new PacketAckPacket();
	S_MUTEX_LOCK l;
	l.lock(&this->ack_lock);
	int count = 0;
	while (!this->ack_packet_queue.empty()) {
		PacketAckPacket::PacketsBlock packets_block;
		packets_block.ID = this->ack_packet_queue.front();
		// TODO @@@ memory reallocate inside "push" + coping packets_block
		packet->Packets.push(packets_block);
		this->ack_packet_queue.pop();
		if (++count == MAX_ACK_NUMBER) break;
	}
	this->sendPacket(packet);
}

void ClientConnectionBase::checkRESEND() {
	if (this->resend_packet_map.empty()) return;
	S_MUTEX_LOCK l;
	l.lock(&this->resend_lock);
	DEBUG_LOG("number of resend packets: " << this->resend_packet_map.size());
	for(RESEND_PACKET_MAP_TYPE::iterator it=this->resend_packet_map.begin(); it!=this->resend_packet_map.end(); it++) {
		; // RESEND unACKed packets
		PacketBase *packet = it->second;
		packet->setFlag(PacketHeader::FLAG_RESENT);
		this->sendPacket(packet);
	}
}

bool ClientConnectionBase::checkAlive() {
	time_t now = time(NULL);
	if ((now - this->last_packet_received) > CONNECTION_TIMEOUT) {
		return true;
	}
	return false;
}

void ClientConnectionBase::processIncomingPacket(PacketBase *packet) {
	this->updateLastReceived();
	if (packet->header.isReliable()) {
		S_MUTEX_LOCK l;
		l.lock(&this->ack_lock);
		this->ack_packet_queue.push(packet->header.getSequenceNumber());
	}
	if (packet->header.isAppendedAcks()) {
		S_MUTEX_LOCK l;
		l.lock(&this->resend_lock);
		PacketBase::ACK_LIST_TYPE::const_iterator it = packet->appended_acks.begin();
		for (; it != packet->appended_acks.end(); it++) {
			this->remove_resend_packet(*it);
		}
	}
	if (packet->header.getPacketID() == PacketAck_ID) {
		PacketAckPacket *ack_packet = dynamic_cast<PacketAckPacket *>(packet);
		assert(ack_packet);
		for(vector<PacketAckPacket::PacketsBlock>::iterator it = ack_packet->Packets.val.begin(); it!=ack_packet->Packets.val.end(); it++) {
			this->remove_resend_packet(it->ID);
		}

	}
}

void ClientConnectionBase::processOutgoingPacket(PacketBase *packet) {
	if (packet->header.isReliable() && !packet->header.isResent()) {
		S_MUTEX_LOCK l;
		l.lock(&this->resend_lock);
		this->add_resend_packet(packet);
	}
}

void ClientConnectionBase::remove_resend_packet(uint32_t seq) {
	RESEND_PACKET_MAP_TYPE::const_iterator it = this->resend_packet_map.find(seq);
	if (it != this->resend_packet_map.end()) {
		this->resend_packet_map.erase(seq);
		if (it->second != NULL) delete it->second;
		this->resend_status_map.erase(seq);
	}
}

void ClientConnectionBase::add_resend_packet(PacketBase* packet) {
	uint32_t seq_key = packet->header.sequence;
	// @@@ take a copy of the packet
	this->resend_packet_map[seq_key] = FileTransferPacketFactorySingleton::get().createPacketCopy(
			packet->header.getPacketID(), packet);
	this->resend_status_map[seq_key] = ::time(NULL);
}

void ClientConnectionBase::sendPacket(PacketBase *packet) {
	this->transfer_peer->sendPacket(packet,& this->ep);
}

