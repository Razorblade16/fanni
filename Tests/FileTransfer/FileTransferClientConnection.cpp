/*
 * FileTransferClientConnection.cpp
 *
 *  Created on: Aug 26, 2009
 *      Author: lulu
 */

#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include "FileTransferPackets/FileTransferPacketFactory.h"
#include "FileTransferPackets/FileTransferPacketsID.h"
#include "FileTransferPackets/FileTransferPackets.h"
#include "FileTransferNode.h"
#include "FileTransferClientConnection.h"
#include "FileUtils.h"

using namespace std;
using namespace Fanni;
using namespace Fanni::Tests;

FileTransferClientConnection::FileTransferClientConnection(uint32_t circuit_code, const EndPoint &ep, PacketTransferBase *transfer_base) :
	ClientConnectionBase(circuit_code, ep, transfer_base){
}

FileTransferClientConnection::~FileTransferClientConnection() {
	for(FILE_TRANSFER_STATUS_MAP_TYPE::iterator it=this->receive_transfer_status_map.begin(); it!=this->receive_transfer_status_map.end(); it++) {
		delete it->second;
	}
	for(FILE_TRANSFER_STATUS_MAP_TYPE::iterator it=this->send_transfer_status_map.begin(); it!=this->send_transfer_status_map.end(); it++) {
		delete it->second;
	}
}

void FileTransferClientConnection::addReceiveFileTransfer(FileTransferStatus *status) {
	S_MUTEX_LOCK l;
	l.lock(&this->receive_transfer_status_map.getMutex());
	this->receive_transfer_status_map[status->getReceiverTransferID().toString()] = status;
}

FileTransferStatus *FileTransferClientConnection::getReceiveFileTransfer(const UUID &receiver_transfer_id) {
	S_MUTEX_LOCK l;
	l.lock(&this->receive_transfer_status_map.getMutex());
	LOCKABLE_FILE_TRANSFER_STATUS_MAP_TYPE::iterator it = this->receive_transfer_status_map.find(receiver_transfer_id.toString());
	if (it == this->receive_transfer_status_map.end()) {
		// not found
		return NULL;
	} else {
		return it->second;
	}
}

void FileTransferClientConnection::addSendFileTransfer(FileTransferStatus *status) {
	S_MUTEX_LOCK l;
	l.lock(&this->send_transfer_status_map.getMutex());
	TRACE_LOG("adding sender transfer id: " << status->getSenderTransferID().toString());
	this->send_transfer_status_map[status->getSenderTransferID().toString()] = status;
}

FileTransferStatus *FileTransferClientConnection::getSendFileTransfer(const UUID &sender_transfer_id) {
	S_MUTEX_LOCK l;
	l.lock(&this->send_transfer_status_map.getMutex());
	TRACE_LOG("getting sender transfer id: " << sender_transfer_id.toString());
	LOCKABLE_FILE_TRANSFER_STATUS_MAP_TYPE::iterator it = this->send_transfer_status_map.find(sender_transfer_id.toString());
	if (it == this->send_transfer_status_map.end()) {
		// not found
		return NULL;
	} else {
		return it->second;
	}
}

// =============
// events
void FileTransferClientConnection::OnOpenConnectionReplyEvent::operator ()(FileTransferClientConnection *connection) {
	FileTransferNode *file_transfer_peer = dynamic_cast<FileTransferNode *>(connection->transfer_peer);
	assert(file_transfer_peer);
	string file_path = file_transfer_peer->getSendFile();
	size_t file_size =FileUtils::get_file_size(file_path);
	FileTransferStatus *status = new FileTransferStatus(file_size, file_path, UUIDGeneratorSingleton::get().Zero(), UUIDGeneratorSingleton::get().Create());
	connection->addSendFileTransfer(status);
	// send a FileInfoPacket
	PacketBase *packet = FileTransferPacketFactorySingleton::get().createPacket(FileInfo_ID);
	FileInfoPacket *file_info_packet = dynamic_cast<FileInfoPacket *>(packet);
	file_info_packet->FileInfo.SenderTransferID = status->getSenderTransferID();
	file_info_packet->FileInfo.Size = status->getFileSize();
	PacketBuffer buffer(reinterpret_cast<const unsigned char*>(status->getFileName().c_str()), status->getFileName().size());
	file_info_packet->FileInfo.Name = buffer;
	connection->sendPacket(file_info_packet);
}

void FileTransferClientConnection::OnFileInfoEvent::operator ()(uint32_t file_size, const std::string &file_name, const UUID &sender_transfer_id, FileTransferClientConnection *connection) {
	TRACE_LOG("enter");
	UUID receiver_transfer_id = UUIDGeneratorSingleton::get().Create();
	FileTransferStatus *status = new FileTransferStatus(file_size, file_name, receiver_transfer_id, sender_transfer_id);
	connection->addReceiveFileTransfer(status);
	// send reply packet
	PacketBase *packet = FileTransferPacketFactorySingleton::get().createPacket(FileInfoReply_ID);
	FileInfoReplyPacket *file_info_reply_packet = dynamic_cast<FileInfoReplyPacket *>(packet);
	file_info_reply_packet->FileInfo.ReceiverTransferID = status->getReceiverTransferID();
	file_info_reply_packet->FileInfo.SenderTransferID = status->getSenderTransferID();
	connection->sendPacket(file_info_reply_packet);
	TRACE_LOG("exit");
}

// memo @@@ client_transfer_id is for multiple file transfer ...
void FileTransferClientConnection::OnFileInfoReplyEvent::operator ()(const UUID &receiver_transfer_id, const UUID &sender_transfer_id, FileTransferClientConnection *connection) {
	TRACE_LOG("enter");
	FileTransferStatus *status = connection->getSendFileTransfer(sender_transfer_id);
	if (!status) {
		ERROR_LOG( "can not find file transfer status for " << sender_transfer_id.toString());
		return;
	}
	// update receiver transfer id
	status->setReceiverTransferID(receiver_transfer_id);
	// read file , send
	ifstream fs(status->getFileName().c_str(), ios::binary);
	if (fs.fail()) {
		ERROR_LOG( "unable to open file for reading" << status->getFileName());
		return;
	}

	INFO_LOG("start transferring file: " << status->getFileName() << " " << status->getFileSize());
	size_t total_size = status->getFileSize();
	size_t left_size = total_size;
	int data_number = 0;
	while(left_size > 0) {
		int read_size = left_size > FILE_PART_SIZE ? FILE_PART_SIZE : left_size;
		PacketBuffer buffer;
		fs.read(reinterpret_cast<char*>(buffer.getBuffer()), read_size);
		if (read_size != fs.gcount()) {
			WARN_LOG("unmatched read size: " << read_size << " " << fs.gcount());
		}
		buffer.setLength(fs.gcount());
		// send file data packet
		FileDataPacket *packet = dynamic_cast<FileDataPacket *>(FileTransferPacketFactorySingleton::get().createPacket(FileData_ID));
		packet->FileData.ReceiverTransferID = status->getReceiverTransferID();
		packet->FileData.DataNumber = data_number++;
		packet->FileData.Data = buffer;
		packet->setFlag(PacketHeader::FLAG_RELIABLE);
		connection->sendPacket(packet);
		left_size -= read_size;
	}
	fs.close();

	TRACE_LOG("exit");
}

void FileTransferClientConnection::OnFileDataEvent::operator ()(const UUID &receiver_transfer_id, int data_number, const vector<unsigned char> &data_buf, FileTransferClientConnection *connection) {
	FileTransferStatus *status = connection->getReceiveFileTransfer(receiver_transfer_id);
	if (status == NULL) {
		ERROR_LOG("unknown transfer id: " << receiver_transfer_id.toString());
		return;
	}
	if (status->update(data_number, &data_buf[0], data_buf.size())) {
		INFO_LOG("TransferComplete: " << status->getFileName() << " " << status->getReceiverTransferID().toString());
	}
}

void FileTransferClientConnection::OnFileTransferCompleteEvent::operator ()(const UUID &sender_transfer_id, FileTransferClientConnection *connection) {
	;
}

