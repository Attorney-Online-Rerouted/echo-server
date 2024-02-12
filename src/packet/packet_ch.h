#ifndef PACKET_CH_H
#define PACKET_CH_H

#include "network/serveraopacket.h"

class PacketCH : public ServerAOPacket
{
public:
  PacketCH(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
