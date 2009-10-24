/*
 * FileTransferNode.h
 *
 *  Created on: Aug 26, 2009
 *      Author: lulu
 */

#ifndef FILETRANSFERNODE_H_
#define FILETRANSFERNODE_H_

#include <string>

#include "Packets/PacketBase.h"
#include "rUDP/TransferNode.h"
#include "FileTransferPackets/FileTransferPacketFactory.h"
#include "FileTransferPackets/FileTransferPacketsID.h"

namespace Fanni {

class FileTransferNode : public TransferNode {
private:
	static const PacketHeader::PACKET_ID_TYPE OPEN_CONNECTION_PACKET = OpenConnection_ID;
	static const PacketHeader::PACKET_ID_TYPE CLOSE_CONNECTION_PACKET = CloseConnection_ID;

	std::string send_file_path;
	void openConnection(const Poco::Net::SocketAddress &addr);
	void closeConnection(const Poco::Net::SocketAddress &addr);

public:
	FileTransferNode(const std::string &addr, uint16_t port, int thread_number);
	virtual ~FileTransferNode();
	virtual ConnectionBase *createConnection(const PacketBase *packet, const Poco::Net::SocketAddress &addr);
	virtual bool isNewConnection(const PacketBase *packet);

	void startSendFile(const std::string &file_path, const Poco::Net::SocketAddress &addr);
	const std::string &getSendFile() const {
		return this->send_file_path;
	}
};

}

#endif /* FILETRANSFERNODE_H_ */
