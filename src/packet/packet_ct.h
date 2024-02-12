#ifndef PACKET_CT_H
#define PACKET_CT_H

#include "network/serveraopacket.h"

class PacketCT : public ServerAOPacket
{
public:
  PacketCT(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
