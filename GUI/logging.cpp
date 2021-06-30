#pragma once
#include "../sysout.h"
namespace pxg
{
    namespace log
    {
        enum LogLevel : unsigned short
        {
            LogLevelError, LogLevelWarning, LogLevelAll
        };

        static LogLevel logLevel = LogLevelAll;

        static void Error(std::string *out)
        {
            if(logLevel >= LogLevelError)
            {
                px::sysError(out);
            }
        }

        static void Warning(std::string *out)
        {
            if(logLevel >= LogLevelWarning)
            {
                px::sysWarn(out);
            }
        }

        static void Info(std::string *out)
        {
            if(logLevel >= LogLevelAll)
            {
                px::sysInfo(out);
            }
        }
    }
}