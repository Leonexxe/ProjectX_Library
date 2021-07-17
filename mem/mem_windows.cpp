/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
mem_windows.cpp (c) 2021
Desc: description
Created:  2021-07-12T12:12:20.839Z
Modified: 2021-07-12T12:15:53.434Z
*/

#include "windows.h"
#include "psapi.h"

namespace px::mem
{
    SIZE_T getCurrentRamUsage()
    {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
        return virtualMemUsedByMe;
    }
}