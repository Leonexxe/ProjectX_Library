#pragma once
#include <ctime>
#include <string>
#include <projectX/tools/strings.cpp>

namespace px
{
    #ifdef PX_UNIX
        #pragma message("PX_TIME : UNIX")
        #include <sys/time.h>
        #define PX_TIME
        /**
         * @brief returns date time as string
         * 
         * @return std::string
         */ 
        std::string datetimeNow()
        {
            timeval curTime;
            gettimeofday(&curTime, NULL);
            int milli = curTime.tv_usec / 1000;

            char buffer [80];
            strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));

            char currentTime[84] = "";
            sprintf(currentTime, "%s:%03d", buffer, milli);
            std::string currtime = "";
            for(char I : currentTime)
            {
                currtime = currtime + I;
            }
            return currtime;
        }
    #endif
}