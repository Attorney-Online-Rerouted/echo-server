#ifndef PACKET_MS_H
#define PACKET_MS_H

#include "network/serveraopacket.h"

class PacketMS : public ServerAOPacket
{
public:
  PacketMS(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;

private:
  ServerAOPacket *validateIcPacket(AOClient &client) const;
};
#endif
