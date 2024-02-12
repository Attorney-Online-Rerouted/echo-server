#ifndef PACKET_SETCASE_H
#define PACKET_SETCASE_H

#include "network/serveraopacket.h"

class PacketSetcase : public ServerAOPacket
{
public:
  PacketSetcase(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
