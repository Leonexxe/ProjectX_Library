#include <string>
#include <list>
#include <projectX/OS_AUTOCONFIG.h>
#include <PXC>
#include <thread>

#include "server.h"

namespace px
{
    namespace net
    {
        //
        // Server
        //
        class server
        {
            public:
            server(int port,int bufferSize){this->port = port;this->bufferSize = bufferSize;}

            int run()
            {
                std::thread THR_ServMain(px::net::RUN_MAIN,this);
                this->MAIN_THR = &THR_ServMain;
                THR_ServMain.join();
            }

            std::list<std::string> clients;
            std::list<std::thread*> CLIENT_THREADS;
            std::thread* MAIN_THR;
            int port = 0;
            int bufferSize = 0;
            bool OK = 0;

            void Kick(std::string IP)
            {
                this->clients.remove(IP);
            }

            void KickAll() 
            {
                for(std::string IP : this->clients)
                {
                    this->Kick(IP);
                }
                this->closeAllClientThreads();
                this->clients.empty();
            }

            void close()
            {
                this->running = 0;
            }

            void terminate()
            {
                std::cout << px::ErrorPrefix() << "terminate function called on " << this << std::endl;
                this->closeAllClientThreads();
                std::cout << px::ErrorPrefix() << "Terminating " << this << std::endl;
                exit(-1);
            }

            bool running = 1;

            void closeMainWorker()
            {
                std::cout << px::WarnPrefix() << "Terminating " << this->MAIN_THR << "!" << std::endl;
                //terminate
                this->MAIN_THR->~thread();
            }

            void closeAllClientThreads()
            {
                for(std::thread* THR : this->CLIENT_THREADS)
                {
                    std::cout << px::WarnPrefix() << "Terminating " << THR << "!" << std::endl;
                    //terminate
                    THR->~thread();
                }
            }

            void reset()
            {
                this->running = 1;
                this->KickAll();
            }
        };

        //
        // multithreading
        //
        void RUN_CLIENT(SOCKET Socket, px::net::server* serv,sockaddr_in client)
        {
            std::cout << "started client worker for server " << serv << " at " << std::this_thread::get_id() << std::endl;

            char host[NI_MAXHOST];      // clients remote name
            char host_name[NI_MAXHOST];      // clients remote name
            char service[NI_MAXSERV];   // service (i.e. port) the client is connected on
            ZeroMemory(host,   NI_MAXHOST);
            ZeroMemory(service,NI_MAXSERV);

            getnameinfo((sockaddr*)&client, sizeof(client), host_name, NI_MAXHOST, service, NI_MAXSERV, 0);
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            std::cout <<px::InfoPrefix() << host <<"("<<host_name<<")"<< " connected on port " << ntohs(client.sin_port) << std::endl;
            char buf[serv->bufferSize];
            while(serv->running)
            {
                ZeroMemory(buf,serv->bufferSize);//same as memset(buf,0,serv->buffersize)

                // wait for client to send data
                int bytesReceived = recv(Socket, buf, serv->bufferSize, 0);
                std::cout << px::InfoPrefix() << "received " << buf << " from " << host << std::endl;
                if(bytesReceived == SOCKET_ERROR)
                {
                    std::cout << px::ErrorPrefix() << "Socket Error at " << std::this_thread::get_id() << " on server " << serv << " closing socket" << std::endl;
                    break;
                }
                if(bytesReceived == 0)
                {
                    std::cout << px::WarnPrefix() << "Client disconnected" << std::endl;
                    break;
                }

                // send response
                send(Socket, buf, bytesReceived + 1, 0);
            }
            closesocket(Socket);
        }

        void RUN_MAIN(px::net::server* serv)
        {
            std::cout << "started Main worker of " << serv << " at "<< std::this_thread::get_id() << std::endl;

            //create socket
            SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
            if(listening == INVALID_SOCKET)
            {
                px::sysError("Cant create socket!");
                serv->terminate();
                return;
            }
            
            // Bind the socket to ip and port
            sockaddr_in hint;
            hint.sin_family = AF_INET;
            hint.sin_port = htons(serv->port);
            hint.sin_addr.S_un.S_addr = INADDR_ANY;

            bind(listening, (sockaddr*)&hint, sizeof(hint));

            // tell socket for listening
            listen(listening, SOMAXCONN);

            // und wir warten und wir warten und wir warten (spongebob reference(german)(might look up which episode)) (waiting for connections)
            serv->OK = 1;
            std::cout << px::InfoPrefix() << serv << " listening for connections" << std::endl;
            while(serv->running)
            {
                int i = 0;
                sockaddr_in client;
                int clientSize = sizeof(client);

                SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
                if(clientSocket == INVALID_SOCKET)
                {
                    std::cout << px::ErrorPrefix() << " Invalid socket " << &clientSocket << " dropping client" << std::endl;
                }
                else
                {
                    // opening handler thread
                    sockaddr_in clientFTHR = client;
                    SOCKET clientSocketFTHR = clientSocket;
                    std::thread CLT_THR(px::net::RUN_CLIENT,clientSocketFTHR,serv,clientFTHR);
                    serv->CLIENT_THREADS.push_back(&CLT_THR);
                    return;
                }
            }
        }
    }
}
                                                                    