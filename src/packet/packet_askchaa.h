#ifndef PACKET_ASKCHAA_H
#define PACKET_ASKCHAA_H

#include "network/serveraopacket.h"

class PacketAskchaa : public ServerAOPacket
{
public:
  PacketAskchaa(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
