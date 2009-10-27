#ifndef PACKETFACTORY_H_
#define PACKETFACTORY_H_

#include "Poco/HashMap.h"

#include "fanni/Serializable.h"
#include "fanni/Packets/Packets_def.h"
#include "fanni/Packets/PacketHeader.h"
#include "fanni/Packets/PacketBase.h"

namespace Fanni {

class Fanni_Packets_API PacketFactory {
protected:
	typedef Poco::HashMap<PacketHeader::PACKET_ID_TYPE, const PacketBase*> PACKET_MAP_TYPE;
	//typedef std::tr1::unordered_map<PacketHeader::PACKET_ID_TYPE, const PacketBase*> PACKET_MAP_TYPE;
	PACKET_MAP_TYPE PacketList;

	PacketFactory();
public:
	virtual ~PacketFactory();
	PacketBase *createPacket(PacketHeader::PACKET_ID_TYPE packet_id) const;
	PacketBase *createPacketCopy(PacketHeader::PACKET_ID_TYPE packet_id, const PacketBase *packet) const;
	virtual void registerPacket(PacketHeader::PACKET_ID_TYPE id, const PacketBase &packet);
};

}

#endif /* PACKETFACTORY_H_ */