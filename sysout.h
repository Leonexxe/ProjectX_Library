#pragma once
#define PX_CODE_KEEP_ALIVE {/*KEEP ALIVE*/while(1){std::this_thread::sleep_for(std::chrono::milliseconds(10000));std::cout << ".";}}
#include "sysout/sysout.cpp"
#include "sysout/table.cpp"