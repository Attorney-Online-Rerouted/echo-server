#ifndef PACKET_PW_H
#define PACKET_PW_H

#include "network/serveraopacket.h"

class PacketPW : public ServerAOPacket
{
public:
  PacketPW(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
#endif
