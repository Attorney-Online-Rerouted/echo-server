#pragma once

#include "qcompilerdetection.h"

#ifdef ECHO_SERVER_LIBRARY
#define ECHO_SERVER_EXPORT Q_DECL_EXPORT
#else
#define ECHO_SERVER_EXPORT Q_DECL_IMPORT
#endif
