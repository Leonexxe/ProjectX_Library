/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
OS_AUTOCONFIG.h (c) 2021
Desc: description
Created:  2021-07-03T18:03:18.913Z
Modified: 2021-07-03T18:03:30.997Z
*/

#if !defined(PX_OS_CONFIG) || defined(IGNORE_AUTOCONFIG_HEADERGAURD)
    // do unix stuff
    #ifdef __unix__
        #pragma message "OS_AUTOCONFIG : UNIX"
        #ifndef PX_UNIX
            #define PX_UNIX
        #endif
        #define PX_OS_CONFIG
    #endif

    // do windows stuff
    #ifdef _WIN32
        #pragma message("OS_AUTOCONFIG : WINDOWS")
        #ifndef PX_WIN
            #define PX_WIN
        #endif
        #ifndef PX_ALTERNATIVE_LISTSIZE
            #define PX_ALTERNATIVE_LISTSIZE
        #endif
        #define PX_OS_CONFIG
    #endif

    #ifndef PX_OS_CONFIG
    #error OS_AUTOCONFIG : OS not supported
    #endif
#else
#pragma message "OS_AUTOCONFIG : autoconfig has already been completed,use '#define IGNORE_AUTOCONFIG_HEADERGAURD' to do so anyway."
#endif
