/*############################################################################################################
# File: c:\Users\Administrator\OneDrive\Dokumente\GitHub\ProjectX_Library\net\windows\server.cpp             #
# Project: c:\Users\Administrator\OneDrive\Dokumente\GitHub\ProjectX_Library\net\windows                     #
# Created Date: Wednesday, June 30th 2021, 9:18:58 pm                                                        #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#ifndef PX_NET_NO_SERVER
#include <string>
#include <list>
#include <thread>

#include <windows.h>
#include <WS2tcpip.h>

namespace px
{
    //
    // Server
    //
    template<int buffersize>
    class server
    {
        public:
        std::string(*Interpeter)(std::string, std::string, server*);
        server(int port,std::string(*p_Interpeter)(std::string, std::string, server*))
            :Interpeter(p_Interpeter)
        {this->port = port;}

        int run()
        {
            std::thread THR_ServMain(px::RUN_MAIN<buffersize>,this);
            this->MAIN_THR = &THR_ServMain;
            THR_ServMain.join();
            return 0;
        }
        std::list<std::string> clients;
        std::list<std::thread> CLIENT_THREADS;
        std::thread* MAIN_THR;
        int port = 0;
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
            std::cout << px::ErrorPrefix() << "Terminating " << this << std::endl;
        }
        bool running = 1;
        void closeMainWorker()
        {
            std::cout << px::WarnPrefix() << "Terminating " << this->MAIN_THR << "!" << std::endl;
            //terminate
            this->MAIN_THR->~thread();
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
    template<int buffersize>
    void RUN_CLIENT(SOCKET Socket, px::server<buffersize>* serv,sockaddr_in client)
    {
        std::cout << "started client worker for server 0x" << serv << std::endl;
        char host[NI_MAXHOST];      // clients remote name
        char host_name[NI_MAXHOST];      // clients remote name
        char service[NI_MAXSERV];   // service (i.e. port) the client is connected on
        ZeroMemory(host,   NI_MAXHOST);
        ZeroMemory(service,NI_MAXSERV);
        getnameinfo((sockaddr*)&client, sizeof(client), host_name, NI_MAXHOST, service, NI_MAXSERV, 0);
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        //std::cout <<px::InfoPrefix() << host <<"("<<host_name<<")"<< " connected on port " << ntohs(client.sin_port) << std::endl;
        char buf[buffersize];
        while(serv->running)
        {
            std::string response = "";
            ZeroMemory(buf,buffersize);//same as memset(buf,0,serv->buffersize)
            // wait for client to send data
            int bytesReceived = recv(Socket, buf, buffersize, 0);
            if(bytesReceived == SOCKET_ERROR)
            {
                std::cout << px::ErrorPrefix() << "Socket Error at " << std::this_thread::get_id() << " on server " << serv << " closing socket" << std::endl;
                break;
            }
            else if(bytesReceived == 0)
            {
                std::cout << px::WarnPrefix() << "Client disconnected" << std::endl;
                break;
            }
            else
                response = serv->Interpeter(std::string(buf),std::string(host),serv);
            // send response
            send(Socket, response.c_str(), response.size() + 1, 0);
        }
        closesocket(Socket);
    }
    template<int buffersize>
    void RUN_MAIN(px::server<buffersize>* serv)
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
        // socket for listening
        listen(listening, SOMAXCONN);
        // und wir warten und wir warten und wir warten (spongebob reference(german)(might look up which episode)) (waiting for connections)
        std::cout << px::InfoPrefix() << serv << " listening for connections" << std::endl;
        serv->OK = 1;
        while(serv->running)
        {
            std::cout << "blub 2" << std::endl;
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
                serv->CLIENT_THREADS.push_back(std::thread(px::RUN_CLIENT<buffersize>,clientSocketFTHR,serv,clientFTHR));
            }
        }
    }
}
#endif                                                                   