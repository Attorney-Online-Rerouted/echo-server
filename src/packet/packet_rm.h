#ifndef PACKET_RM_H
#define PACKET_RM_H

#include "network/serveraopacket.h"

class PacketRM : public ServerAOPacket
{
public:
  PacketRM(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
