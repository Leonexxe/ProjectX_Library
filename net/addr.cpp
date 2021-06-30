#pragma once
#include <string>

namespace px
{
    class addr
    {
        public:
        std::string IP;
        int port;
        addr(std::string IPAddress, int PORT)
        {
            this->IP = IPAddress;
            this->port = PORT;
        }
        addr()
        {
            this->IP = "127.0.0.1";
            this->port = 1;
        }
    };
}