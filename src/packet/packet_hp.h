#ifndef PACKET_HP_H
#define PACKET_HP_H

#include "network/serveraopacket.h"

class PacketHP : public ServerAOPacket
{
public:
  PacketHP(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
