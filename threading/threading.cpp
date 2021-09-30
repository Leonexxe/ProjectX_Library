/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
threading.cpp (c) 2021
Desc: description
Created:  2021-08-22T14:03:37.057Z
Modified: 2021-08-22T15:02:58.238Z
*/

namespace px::threading {
#ifdef PX_WIN
    #include <windows.h>
    #include <processthreadsapi.h>

    HRESULT setThreadName(std::string n)
    {
        HRESULT r;
        r = SetThreadDescription(
            GetCurrentThread(),
            L"thread_name"
        );
        return r;
    }
#endif
}

