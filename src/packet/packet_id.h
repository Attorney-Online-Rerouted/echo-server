#ifndef PACKET_ID_H
#define PACKET_ID_H

#include "network/serveraopacket.h"

class PacketID : public ServerAOPacket
{
public:
  PacketID(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
