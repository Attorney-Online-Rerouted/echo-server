#pragma once

#include "network/serveraopacket.h"
#include "server_global.h"

class ECHO_SERVER_EXPORT PacketMC : public ServerAOPacket
{
public:
  PacketMC(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
  virtual bool validatePacket() const;
};
