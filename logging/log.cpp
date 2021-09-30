#pragma once
#include <string>
#include <projectX/sysout.h>
#include <fstream>
#include "../tools/lists.cpp"
#ifndef PX_LOGGING_MAIN_LOGGER_NAME
    #define PX_LOGGING_MAIN_LOGGER_NAME "main"
#endif

class logger
{
public:
    std::string logFile;
    std::string NAME;
    logger(std::string logfile, std::string name)
    {
        this->logFile = logfile;
        this->NAME = name;
    }
    logger(){}

    void append(std::string msg)
    {
        std::ofstream outfile;
        outfile.open(this->logFile, std::ios_base::app);
        outfile << msg;
        outfile.close();
    }
};

std::list<logger> loggers;

/**
 * @brief 
 * 
 * @param logfile path to the log file
 * @param name obvious i guess
 * @return logger 
 */
logger* createlogger(std::string logfile, std::string name)
{
    loggers.push_back(logger(logfile, name));
    return &loggers.back();
}

logger getLogger(std::string name)
{
    for(logger I : loggers)
    {
        if(I.NAME == name)
            return I;
    }
    px::tools::lists::getElementByIndex(&loggers,0).append(px::ErrorPrefixFDT() + "logger \"" + name + "\" cant be found!");
}

void quickLog(std::string name, std::string data)
{
    if(getLogger(name).NAME != PX_LOGGING_MAIN_LOGGER_NAME)
    {
        px::tools::lists::getElementByIndex(&loggers,0).append(data);
    }
    getLogger(name).append(data);
}
