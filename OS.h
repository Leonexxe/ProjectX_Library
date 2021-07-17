/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
OS.h (c) 2021
Desc: description
Created:  2021-07-03T16:29:31.066Z
Modified: 2021-07-03T16:30:56.994Z
*/

#if defined(PX_WIN)
    #include "OS/windows.cpp"
#elif defined(PX_UNIX)
    #include "OS/UNIX.cpp"
#else
    #error OS not supported (OS.h)
#endif