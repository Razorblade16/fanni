#ifndef PACKETBASE_H_
#define PACKETBASE_H_

#include <vector>

#include "Poco/SharedPtr.h"
#include "fanni/PacketBuffer.h"
#include "fanni/Serializable.h"
#include "fanni/Packets/Packets_def.h"
#include "PacketHeader.h"

namespace Fanni {

class Fanni_Packets_API PacketBase : public PacketSerializable {
public:
	typedef std::vector<uint32_t> ACK_LIST_TYPE;
	ACK_LIST_TYPE appended_acks;

protected:
	virtual void serialize(PacketBuffer &buffer) const = 0;
	virtual void deserialize(PacketBuffer &buffer) = 0;

public:
	PacketBase();
	PacketHeader header; // TODO @@@ should be protected

	virtual ~PacketBase();

	void setFlag(PacketHeader::Flag flag);
	void setSequence(uint32_t seq);
	void setID(uint32_t id);
	void appendAck(uint32_t ack_seq);

	const ACK_LIST_TYPE &getAppendedAcks() const;

	virtual void serializePacket(PacketBuffer &buffer) const;
	virtual void deserializePacket(PacketBuffer &buffer);

	virtual PacketBase *clone() const = 0;
	virtual PacketBase *clone(const PacketBase *packet) const = 0;
};

typedef Poco::SharedPtr<PacketBase> PacketBasePtr;

}

#endif /* PACKETBASE_H_ */
