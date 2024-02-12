#ifndef PACKET_RC_H
#define PACKET_RC_H

#include "network/serveraopacket.h"

class PacketRC : public ServerAOPacket
{
public:
  PacketRC(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
