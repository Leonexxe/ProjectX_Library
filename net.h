#pragma once
#ifndef PX_NET_BUFFER_SIZE
    #define PX_NET_BUFFER_SIZE 4096
#endif
#include "net/connection.h"

#if defined(PX_WIN)
    #include <winsock2.h>
    #pragma comment(lib,"ws2_32.lib") //Winsock Library
    #include "net/windows/connection.cpp"
    #include "net/windows/server.cpp"
#elif defined(PX_UNIX)
    #include "net/unix/connection.cpp"
    #include "net/unix/server.cpp"
#else
    #error os not supported
#endif
