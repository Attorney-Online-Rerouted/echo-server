#ifndef PACKET_CASEA_H
#define PACKET_CASEA_H

#include "network/serveraopacket.h"

class PacketCasea : public ServerAOPacket
{
public:
  PacketCasea(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
