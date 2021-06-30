#pragma once
#include <ctime>
#include <string>
#include <projectX/tools/strings.cpp>

namespace px
{
    /**
     * @brief time difference from UTC in hours
     */
    short fromUTC = 0;
    std::string formattime24H(long millieseconds)
    {
        int seconds = 0;
        int mins = 0;
        int hours = 0;
        for(long i = 0;i < millieseconds / 1000;i++)
        {
            seconds++;
            if(seconds > 60)
            {
                seconds = 0;
                mins++;
                if(mins > 60)
                {
                    mins = 0;
                    hours++;
                }
            }
        }
        return std::to_string(hours) + ":" + std::to_string(mins) + ":" + std::to_string(seconds);
    }

    #ifdef PX_TIME
        /**
         * @brief returns system time as string (24h format) (uses datetimeNow function)
         * 
         * @return std::string 
         */
        std::string now() {
            return datetimeNow().substr(11);
        }
    #else
        #error projectX/time/time.cpp : OS not supported
    #endif
}