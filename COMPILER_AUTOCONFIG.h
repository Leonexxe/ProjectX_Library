/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
COMPILER_AUTOCONFIG.h (c) 2021
Desc: description
Created:  2021-07-02T15:32:50.124Z
Modified: 2021-07-02T17:11:13.426Z
*/

#if defined(__clang__)
    #pragma message("(PX) using clang compiler config")
#endif

#if defined(__GNUC__)
    #pragma message("(PX) using GNU compiler config")
#endif

#if defined(_MSC_VER)
    #pragma message("(PX) using MSVC compiler config")
#endif