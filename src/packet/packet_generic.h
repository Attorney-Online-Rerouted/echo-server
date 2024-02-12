#ifndef PACKET_GENERIC_H
#define PACKET_GENERIC_H

#include "network/serveraopacket.h"

class PacketGeneric : public ServerAOPacket
{
public:
  PacketGeneric(QString header, QStringList contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;

private:
  QString header;
};
#endif
