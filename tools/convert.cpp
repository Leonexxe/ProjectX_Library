/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
convert.cpp (c) 2021
Desc: description
Created:  2021-07-03T17:13:56.443Z
Modified: 2021-07-03T18:02:36.433Z
*/

#ifdef PX_WIN
    //windows includes
    #include <windows.h>
#endif
#include <string>

namespace px
{
    #ifdef PX_WIN
        // windows converters
        std::string convert(LPTSTR c)
        {
            std::string ret;
            for(int I = 0;I<sizeof(c)/sizeof(c[0]);I++)
            {
                ret+=c[I];
            }
            return ret;
        }

        LPCTSTR convert(std::string c)
        {
            LPCTSTR ret;
            const char* str = c.c_str();
            for(int I = 0;I<sizeof(str)/sizeof(str[0]);I++)
            {
                ret+=str[I];
            }
            return ret;
        }

        LPCWSTR convert_LPCWSTR(std::string c)
        {
            LPCWSTR ret;
            const char* str = c.c_str();
            for(int I = 0;I<sizeof(str)/sizeof(str[0]);I++)
            {
                ret+=str[I];
            }
            return ret;
        }
    #endif
}

