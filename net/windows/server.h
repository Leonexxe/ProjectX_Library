#pragma once
#include <OSIND/OS_AUTOCONFIG.h>
#include <OSIND/net.h>
namespace px
{
    namespace net
    {
        class server;
        void RUN_MAIN(px::net::server* serv);
        void RUN_CLIENT(SOCKET Socket, px::net::server* serv,sockaddr_in);
    }
}