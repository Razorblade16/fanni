#ifndef PACKETSERIALIZER_H_
#define PACKETSERIALIZER_H_

#include "fanni/PacketBuffer.h"
#include "PacketBase.h"
#include "PacketFactory.h"

namespace Fanni {

class PacketSerializer {
private:
	PacketBuffer buf;
	PacketFactory *factory;

public:
	PacketSerializer();
	virtual ~PacketSerializer();

	const unsigned char *serialize(const PacketBase *packet, int *len);
	PacketBase *deserialize(const unsigned char *in, int len);
	PacketBase *deserialize(PacketBuffer &buf);

	static bool isZerocoded(PacketBuffer &buf);
	static bool isAppendedAcks(PacketBuffer &buf);

	static void zeroEncode(PacketBuffer &buf);
	static void zeroDecode(PacketBuffer &buf);

};

}

#endif /* PACKETSERIALIZER_H_ */
