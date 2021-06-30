#pragma once
#include <ctime>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <projectX/tools/strings.cpp>

namespace px
{
    #pragma message("PX_TIME : WINDOWS")
    /**
     * @brief returns date time as string
     * 
     * @return std::string
     */
    std::string datetimeNow()
    {
        // get current time
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        // get duration in milliseconds
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        msec %= 1000;

        // get printable result:
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::gmtime(&now_time_t), "%d-%m-%Y %X:") << msec;
        return ss.str();
    }
//    std::string datetimeNow() {
//        return "0000-00-00 00:00:00";
//    }
    #define PX_TIME
}