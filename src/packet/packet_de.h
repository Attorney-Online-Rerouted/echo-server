#ifndef PACKET_DE_H
#define PACKET_DE_H

#include "network/serveraopacket.h"

class PacketDE : public ServerAOPacket
{
public:
  PacketDE(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
