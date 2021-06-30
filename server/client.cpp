#pragma once
#include <string>
#include <list>
#include <projectX/tools/strings.cpp>
#include <projectX/sysout/sysout.cpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
class client
{
public:
    std::string IPv4;
    bool connected = 0;
    bool running = true;
    int buffersize = 0;
    int port = 0;
    void (*newclient)();
    std::string (*interpreter)(client*,std::string*);

    void drop()
    {
        sysInfo("dropping client, " + this->IPv4);
    }
};