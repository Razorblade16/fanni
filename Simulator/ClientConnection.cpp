/*
 * ClientConnection.cpp
 *
 *  Created on: Sep 19, 2009
 *      Author: lulu
 */

#include "ClientConnection.h"

namespace Fanni {

ClientConnection::ClientConnection(uint32_t circuit_code, const EndPoint &ep, PacketTransferBase *transfer_base) :
	ClientConnectionBase(circuit_code, ep, transfer_base){
}

ClientConnection::~ClientConnection() {
	// TODO Auto-generated destructor stub
}

}