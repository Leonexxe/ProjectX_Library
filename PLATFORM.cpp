#pragma once
#include <string>

static unsigned short PX_PLATFORM = 0;

//platform definitions
const static unsigned short PX_PLATFORM_INDEPENDENT  = 0;
const static unsigned short PX_WIN32                 = 1;
const static unsigned short PX_WIN64                 = 2;
const static unsigned short PX_LINUX                 = 3;
const static unsigned short PX_OSX                   = 4;
const static unsigned short PX_FREEBSD               = 5;
const static unsigned short PX_UNIX                  = 6;
const static unsigned short PX_UNKOWN                = 7;

static std::string getOSname()
{
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
}

/**
 * @brief figures out which platform the program is running on and then sets PX_PLATFORM.
 */
static void getPlatform()
{
    std::string OS = getOSname();
         if(OS == "Windows 32-bit"){PX_PLATFORM = PX_WIN32;  }
    else if(OS == "Windows 64-bit"){PX_PLATFORM = PX_WIN64;  }
    else if(OS == "Mac OSX"       ){PX_PLATFORM = PX_OSX;    }
    else if(OS == "Linux"         ){PX_PLATFORM = PX_LINUX;  }
    else if(OS == "FreeBSD"       ){PX_PLATFORM = PX_FREEBSD;}
    else if(OS == "Unix"          ){PX_PLATFORM = PX_UNIX;   }
    else if(OS == "Other"         ){PX_PLATFORM = PX_UNKOWN; }
}