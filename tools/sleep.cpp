#pragma once

#if defined(PX_UNIX)
    #include <unistd.h>
    namespace px
    {
        static void sleep(int milliseconds)
        {
            usleep(milliseconds * 1000);
        }
    }
#elif defined(PX_WIN)
    namespace px
    {
        /**
         * @brief does nothing, not supported on windows
         * 
         * @param milliseconds 
         * @attention not supported on windows
         * @warning not supported on windowss
         */
        static void sleep(int milliseconds){}
    }
#endif