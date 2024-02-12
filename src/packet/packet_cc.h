#ifndef PACKET_CC_H
#define PACKET_CC_H

#include "network/serveraopacket.h"

class PacketCC : public ServerAOPacket
{
public:
  PacketCC(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
