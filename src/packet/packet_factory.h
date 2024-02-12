#pragma once

#include "network/serveraopacket.h"
#include "server_global.h"

class ECHO_SERVER_EXPORT PacketFactory
{
public:
  // thingy here to register/map strings to constructors
  static ServerAOPacket *createPacket(QString header, QStringList contents);
  static ServerAOPacket *createPacket(QString raw_packet);
  template <typename T>
  static void registerClass(QString header)
  {
    class_map[header] = &createInstance<T>;
  };

private:
  template <typename T>
  static ServerAOPacket *createInstance(QStringList contents)
  {
    return new T(contents);
  };
  template <typename T>
  static ServerAOPacket *createInstance(QString header, QStringList contents)
  {
    return new T(header, contents);
  };
  typedef std::map<QString, ServerAOPacket *(*)(QStringList)> type_map;

  static inline type_map class_map;
};
