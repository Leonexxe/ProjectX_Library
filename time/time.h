#pragma once
#include <string>

namespace px
{
    std::string datetimeNow();
    std::string now();
}

// OS
#ifdef PX_WIN
    #include "time_WIN.cpp"
    #define PX_TIME_OS
#endif
#ifdef PX_UNIX
    #include "time_UNIX.cpp"
    #define PX_TIME_OS
#endif

#ifndef PX_TIME_OS
    #error PX_TIME : OS not supported
#endif
#include "time.cpp"