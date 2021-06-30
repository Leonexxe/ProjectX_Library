#include "net/connection.h"

#if defined(PX_WIN)
    #include "net/windows/connection.cpp"
    #include "net/windows/server.cpp"
#elif defined(PX_UNIX)
    #include "net/unix/connection.cpp"
#else
    #error os not supported
#endif