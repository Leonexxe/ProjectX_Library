#pragma once
#include <string>

/**
 * @brief the API header tells the API what to do with the data
 * @param IPv4_DEST redirect destination, set to -1 for API. 
 * if the destination is the API, this could cause trouble.
 * @param APIrequest API request, just put the return value of API_REQUEST() in here
 * @return std::string returns API header
 */
static std::string HEADER_API(std::string IPv4_DEST, std::string APIrequest)
{
    return "[<"+IPv4_DEST+">]:["+APIrequest+"]";
}

static std::string API_REQUEST(int REQUEST_TYPE, std::string parameters[])
{
    switch(REQUEST_TYPE)
    {
    }
}