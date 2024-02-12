#pragma once

#include "acl_roles_handler.h"
#include "server_global.h"

/// Describes a packet's interpretation details.
class ECHO_SERVER_EXPORT PacketInfo
{
public:
  ACLRole::Permission acl_permission; //!< The permissions necessary for the packet.
  int min_args;                       //!< The minimum arguments needed for the packet to be interpreted correctly / make sense.
  QString header;
};
