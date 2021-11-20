/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
AUTOCONFIG.h (c) 2021
Desc: description
Created:  2021-08-19T09:17:18.823Z
Modified: 2021-08-19T09:18:15.845Z
*/
#define PX_CONFIG_COMPILER ""
#define PX_CONFIG_ARCH ""
#define PX_CONFIG_BITS 16
#define PX_CONFIG_PLATFROM ""
//!█████████████████████████████████████████████████████████████████████████████████████████████████
//!█████████████████████████████████████████████████████████████████████████████████████████████████
//!█████████████████████████████████████████████████████████████████████████████████████████████████
//!                  ██████  ██████  ███    ███ ██████  ██ ██      ███████ ██████  
//!                 ██      ██    ██ ████  ████ ██   ██ ██ ██      ██      ██   ██ 
//!                 ██      ██    ██ ██ ████ ██ ██████  ██ ██      █████   ██████  
//!                 ██      ██    ██ ██  ██  ██ ██      ██ ██      ██      ██   ██ 
//!                  ██████  ██████  ██      ██ ██      ██ ███████ ███████ ██   ██ 
//!█████████████████████████████████████████████████████████████████████████████████████████████████
//!█████████████████████████████████████████████████████████████████████████████████████████████████
//!█████████████████████████████████████████████████████████████████████████████████████████████████
#if defined(__clang__)
    #warning (PX) using clang compiler config
    #define PX_COMPILER_CLANG
    #define PX_CONFIG_COMPILER "clang"
#elif defined(__GNUC__)
    #pragma message("(PX) using GNU compiler config")
    #define PX_COMPILER_GNUC
    #define PX_CONFIG_COMPILER "GNU"
#elif defined(_MSC_VER)
    #pragma message("(PX) using MSVC compiler config")
    #define PX_COMPILER_MSVC
    #define PX_CONFIG_COMPILER = "MSVC"
#else
    #error Unsupported compiler
#endif

//?█████████████████████████████████████████████████████████████████████████████████████████████████
//?█████████████████████████████████████████████████████████████████████████████████████████████████
//?█████████████████████████████████████████████████████████████████████████████████████████████████
//?                                  ██████ ██████  ██    ██ 
//?                                 ██      ██   ██ ██    ██ 
//?                                 ██      ██████  ██    ██ 
//?                                 ██      ██      ██    ██ 
//?                                  ██████ ██       ██████  
//?█████████████████████████████████████████████████████████████████████████████████████████████████
//?█████████████████████████████████████████████████████████████████████████████████████████████████
//?█████████████████████████████████████████████████████████████████████████████████████████████████
#ifdef PX_COMPILER_CLANG
    #ifdef __aarch64__
        #define PX_ARM64
        #define PX_CPU64
        #warning (PX) using arm 64 bit CPU config
        #define PX_CONFIG_ARCH "ARM"
        #define PX_CONFIG_BITS 64
    #elif defined(__arm__)
        #define PX_ARM32
        #define PX_CPU32
        #warning (PX) using arm 32 bit CPU config
        #define PX_CONFIG_ARCH "ARM"
        #define PX_CONFIG_BITS 32
    #elif defined(__x86_64__)
        #define PX_X86
        #define PX_CPU64
        #warning (PX) using x86 64 bit CPU config
        #define PX_CONFIG_ARCH "x86"
        #define PX_CONFIG_BITS 64
    #else
        #error Unknown CPU architecture!
    #endif
#else
    #error compiler not supported
#endif

//*█████████████████████████████████████████████████████████████████████████████████████████████████
//*█████████████████████████████████████████████████████████████████████████████████████████████████
//*█████████████████████████████████████████████████████████████████████████████████████████████████
//*                                      ██████  ███████ 
//*                                     ██    ██ ██      
//*                                     ██    ██ ███████ 
//*                                     ██    ██      ██ 
//*                                      ██████  ███████ 
//*█████████████████████████████████████████████████████████████████████████████████████████████████
//*█████████████████████████████████████████████████████████████████████████████████████████████████
//*█████████████████████████████████████████████████████████████████████████████████████████████████
#if !defined(PX_OS_CONFIG) || defined(IGNORE_AUTOCONFIG_HEADERGAURD)
    // do unix stuff
    #if defined(__unix__)
        #pragma message "OS_AUTOCONFIG : UNIX"
        #warning (PX) using UNIX OS config
        #ifndef PX_UNIX
            #define PX_UNIX
        #endif
        #define PX_OS_CONFIG
    #endif

    // do OSX stuff
    #if defined (__APPLE__)
        #pragma message "OS_AUTOCONFIG : mac OSX"
        #warning (PX) using macOS OS config
        #ifndef PX_UNIX
            #define PX_UNIX
        #endif
        #ifndef PX_OSX
            #define PX_OSX
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

//!█████████████████████████████████████████████████████████████████████████████████████████████████
//!█████████████████████████████████████████████████████████████████████████████████████████████████
//!█████████████████████████████████████████████████████████████████████████████████████████████████
//!                         ██      ██ ██████  ██████   █████  ██████  ██    ██ 
//!                         ██      ██ ██   ██ ██   ██ ██   ██ ██   ██  ██  ██  
//!                         ██      ██ ██████  ██████  ███████ ██████    ████   
//!                         ██      ██ ██   ██ ██   ██ ██   ██ ██   ██    ██    
//!                         ███████ ██ ██████  ██   ██ ██   ██ ██   ██    ██    
//!█████████████████████████████████████████████████████████████████████████████████████████████████
//!█████████████████████████████████████████████████████████████████████████████████████████████████
//!█████████████████████████████████████████████████████████████████████████████████████████████████
#if __has_include(<boost/algorithm/string/replace.hpp>)//just testing if Boost can be found
    #define PX_BOOST
#endif
