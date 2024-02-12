cmake_minimum_required(VERSION 3.27.0)

find_package(Qt6 COMPONENTS Core Sql Network Websockets REQUIRED)

project(echo-server LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED ECHO_BUILD_TYPE)
set(ECHO_BUILD_TYPE SHARED)
endif()

if(NOT DEFINED ECHO_BUILD_SERVER_RUNTIME)
set(ECHO_BUILD_SERVER_RUNTIME ON)
endif()

add_library(echo-server ${ECHO_BUILD_TYPE}
  src/acl_roles_handler.h src/acl_roles_handler.cpp
  src/advertiser.h src/advertiser.cpp
  src/akashidefs.h
  src/akashiutils.h
  src/aoclient.h src/aoclient.cpp
  src/area_data.h src/area_data.cpp
  src/commands/area.cpp
  src/commands/authentication.cpp
  src/commands/casing.cpp
  src/commands/command_helper.cpp
  src/commands/messaging.cpp
  src/commands/moderation.cpp
  src/commands/music.cpp
  src/commands/roleplay.cpp
  src/command_extension.cpp
  src/command_extension.h
  src/config_manager.h src/config_manager.cpp
  src/data_types.h
  src/db_manager.h src/db_manager.cpp
  src/discord.h src/discord.cpp
  src/logger/u_logger.h src/logger/u_logger.cpp
  src/logger/writer_full.h src/logger/writer_full.cpp
  src/logger/writer_modcall.h src/logger/writer_modcall.cpp
  src/music_manager.h src/music_manager.cpp
  src/network/serveraopacket.h src/network/serveraopacket.cpp
  src/network/network_socket.h src/network/network_socket.cpp
  src/packet/packet_askchaa.h src/packet/packet_askchaa.cpp
  src/packet/packet_casea.h src/packet/packet_casea.cpp
  src/packet/packet_cc.h src/packet/packet_cc.cpp
  src/packet/packet_ch.h src/packet/packet_ch.cpp
  src/packet/packet_ct.h src/packet/packet_ct.cpp
  src/packet/packet_de.h src/packet/packet_de.cpp
  src/packet/packet_ee.h src/packet/packet_ee.cpp
  src/packet/packet_factory.h src/packet/packet_factory.cpp
  src/packet/packet_generic.h src/packet/packet_generic.cpp
  src/packet/packet_hi.h src/packet/packet_hi.cpp
  src/packet/packet_hp.h src/packet/packet_hp.cpp
  src/packet/packet_id.h src/packet/packet_id.cpp
  src/packet/packet_info.h
  src/packet/packet_mc.h src/packet/packet_mc.cpp
  src/packet/packet_ms.h src/packet/packet_ms.cpp
  src/packet/packet_pe.h src/packet/packet_pe.cpp
  src/packet/packet_pw.h src/packet/packet_pw.cpp
  src/packet/packet_rc.h src/packet/packet_rc.cpp
  src/packet/packet_rd.h src/packet/packet_rd.cpp
  src/packet/packet_rm.h src/packet/packet_rm.cpp
  src/packet/packet_rt.h src/packet/packet_rt.cpp
  src/packet/packet_setcase.h src/packet/packet_setcase.cpp
  src/packet/packet_zz.h src/packet/packet_zz.cpp
  src/packets.cpp
  src/server.h src/server.cpp
  src/testimony_recorder.cpp
  src/typedefs.h
  src/server_global.h
)

target_compile_definitions(echo-server PRIVATE
  ECHO_SERVER_LIBRARY
)

target_include_directories(echo-server PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(NOT TARGET echo-core)
include(FetchContent)
message("Fetching core...")
FetchContent_Declare(
    echo-core
    GIT_REPOSITORY https://github.com/Attorney-Online-Rerouted/echo-core.git
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/core
)
FetchContent_MakeAvailable(echo-core)
endif()

target_link_libraries(echo-server PUBLIC
  Qt::Core
  Qt::Sql
  Qt::Network
  Qt::WebSockets
  echo-core
)

if (ECHO_BUILD_SERVER_RUNTIME)
  add_executable(echo-server-runtime WIN32
    src/main.cpp
  )

  target_link_libraries(echo-server-runtime PRIVATE
    echo-server
  )

  if(WIN32)
    set_target_properties(echo-server-runtime PROPERTIES WIN32_EXECUTABLE true)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resource/icon.rc")
    target_sources(echo-server-runtime PRIVATE ${APP_ICON_RESOURCE_WINDOWS})
  endif()
endif()
