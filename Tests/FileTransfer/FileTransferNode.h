/*
 * FileTransferNode.h
 *
 *  Created on: Aug 26, 2009
 *      Author: lulu
 */

#ifndef FILETRANSFERNODE_H_
#define FILETRANSFERNODE_H_

#include <string>
#include <tr1/unordered_map>

#include "fanni/EndPoint.h"
#include "Packets/PacketBase.h"
#include "PacketTransfer/PacketTransferBase.h"
#include "FileTransferPackets/FileTransferPacketsID.h"

namespace Fanni {
namespace Tests {

class FileTransferNode : public PacketTransferBase {
private:
	static const PacketHeader::PACKET_ID_TYPE OPEN_CONNECTION_PACKET = UseCircuitCode_ID;
	static const PacketHeader::PACKET_ID_TYPE CLOSE_CONNECTION_PACKET = CloseCircuit_ID;

public:
	FileTransferNode(const std::string &addr, int port, int thread_number);
	virtual ~FileTransferNode();
	virtual void init();

	// specified (client) methods
	void openConnection(const EndPoint &ep);
	void closeConnection(const EndPoint &ep);
	void sendFile(const string &file_path, const EndPoint &ep);

	virtual ClientConnectionBase *createClientConnection(uint32_t circuit_code, const EndPoint *ep);
	virtual bool ignoreInProcessIncomingPacket(PacketHeader::PACKET_ID_TYPE packet_id);

};

}
}

#endif /* FILETRANSFERNODE_H_ */