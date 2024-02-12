#ifndef PACKET_EE_H
#define PACKET_EE_H

#include "network/serveraopacket.h"

class PacketEE : public ServerAOPacket
{
public:
  PacketEE(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
