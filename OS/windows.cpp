/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
windows.cpp (c) 2021
Desc: description
Created:  2021-07-03T16:30:31.462Z
Modified: 2021-07-03T18:06:25.418Z
*/

#include "../sysout.h"
#include <windows.h>

#ifndef PX_WIN
    #define PX_WIN
    #include "../tools/convert.cpp"
    #undef PX_WIN
#else
    #include "../tools/convert.cpp"
#endif

namespace px::OS
{
    std::string getEnvVar(LPCTSTR name)
    {
        LPCTSTR lpName;
        LPTSTR lpBuffer;
        DWORD nSize;
        GetEnvironmentVariable(lpName,lpBuffer,nSize);
        return px::convert(lpBuffer);
    }

    void setEnvVar(LPCTSTR lpName,LPCTSTR lpValue)
    {
        SetEnvironmentVariable(lpName,lpValue);
    }
}