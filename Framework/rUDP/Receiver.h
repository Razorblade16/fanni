/*
 * Receiver.h
 *
 *  Created on: Oct 18, 2009
 *      Author: lulu
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "Poco/Net/SocketAddress.h"

#include "fanni/ThreadWorker.h"
#include "fanni/ThreadManager.h"
#include "Packets/PacketHeader.h"
#include "Packets/PacketSerializer.h"
#include "PacketHandlerFactory.h"

namespace Fanni {

class ReceiverTask: public Poco::Notification {
public:
	PacketBuffer *data;
	Poco::Net::SocketAddress addr;

	ReceiverTask(PacketBuffer *data, const Poco::Net::SocketAddress &addr) :
		data(data), addr(addr) {
	}
	~ReceiverTask() {
		delete this->data;
	}
};

class TransferNode;
class Receiver: public Fanni::Worker {
	friend class ReceiverManager;
private:
	TransferNode &node;
	const PacketHandlerFactory &packet_handler_factory;
	PacketSerializer *packet_serializer;

protected:
	Receiver(TransferNode &node, const PacketFactory &packet_factory,
			const PacketHandlerFactory &packet_handler_factory);

public:
	virtual ~Receiver();
	void doTask(Poco::Notification *data);
};

class ReceiverManager: public ThreadManager {
private:
	TransferNode &node;
	const PacketFactory &packet_factory;
	const PacketHandlerFactory &packet_handler_factory;

public:
	ReceiverManager(int receiver_number, TransferNode &node,
			const PacketFactory &packet_factory,
			const PacketHandlerFactory &packet_handler_factory);
	~ReceiverManager();
};

}

#endif /* RECEIVER_H_ */
