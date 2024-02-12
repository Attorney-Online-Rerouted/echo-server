#ifndef PACKET_ZZ_H
#define PACKET_ZZ_H

#include "network/serveraopacket.h"

class PacketZZ : public ServerAOPacket
{
public:
  PacketZZ(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
