#pragma once
#include <string>
#include <projectX/sysout/sysout.cpp>
#include <projectX/IO/filehandler.cpp>

class logger
{
public:
    filehandler FH;
    std::string NAME;
    logger(std::string logfile, std::string name)
    {
        this->FH = filehandler(logfile);
        this->NAME = name;
    }
    logger(){}

    void append(std::string msg)
    {
        px::sysInfo(msg);
        this->FH.append(px::sysInfoFDT(&msg));
    }
};

static logger loggers[10];

/**
 * @brief 
 * 
 * @param logfile path to the log file
 * @param name obvious i guess
 * @param position position in the loggers array at which the logger should be (starting at 0)
 * @return logger 
 */
static logger createlogger(std::string logfile, std::string name, int position)
{
    logger LOG = logger(logfile, name);
    loggers[position] = LOG;
    return LOG;
}

static logger getLogger(int i){return loggers[i];}

static void quickLog(int logger, std::string data)
{
    if(logger>0)
    {
        getLogger(0).append(data);
    }
    getLogger(logger).append(data);
}