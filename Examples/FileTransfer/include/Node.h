/*
 * FileTransferNode.h
 *
 *  Created on: Aug 26, 2009
 *      Author: lulu
 */

#ifndef FILETRANSFERNODE_H_
#define FILETRANSFERNODE_H_

#include <string>

#include "fanni/Packets/PacketBase.h"
#include "fanni/rUDP/TransferNode.h"
#include "fanni/FTPackets/FTPacketsID.h"

namespace Fanni {
namespace FileTransfer {

class Node : public TransferNode {
private:
	std::string send_file_path;

	void connect(const Poco::Net::SocketAddress &addr);
	void close(const Poco::Net::SocketAddress &addr);

public:
	Node(const std::string &addr, uint16_t port, int thread_number);
	virtual ~Node();
	virtual ConnectionBase &createConnection(const PacketBase *packet, const Poco::Net::SocketAddress &addr);
	virtual bool isSystemPacket(const PacketBase *packet) const;

	void startSendFile(const std::string &file_path, const Poco::Net::SocketAddress &addr);

	const std::string &getSendFile() const;
};

}
}

#endif /* FILETRANSFERNODE_H_ */