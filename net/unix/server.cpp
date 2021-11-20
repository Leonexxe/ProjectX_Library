/*############################################################################################################
# File: /Users/leonexxe/Documents/Github/ProjectX_Library/net/unix/server.cpp                                #
# Project: /Users/leonexxe/Documents/Github/ProjectX_Library/net/unix                                        #
# Created Date: Saturday, October 23rd 2021, 7:19:26 pm                                                      #
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
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
namespace px
{
    template<int buffersize>
    class server;
    template<int buffersize>
    void RUN_MAIN(px::server<buffersize>*);
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
    void RUN_CLIENT(int sockfd, px::server<buffersize>* serv,std::string client_IP)
    {
        std::cout << "started client worker for server 0x" << serv << std::endl;
        char buf[buffersize];
        while(serv->running)
        {
            std::string response = "";
            bzero(buf,buffersize);
            // wait for client to send data
            int bytesReceived = read(sockfd,buf,buffersize);
            if(bytesReceived < 0)
            {
                std::cout << px::ErrorPrefix() << "Socket Error at " << std::this_thread::get_id() << " on server " << serv << " closing socket" << std::endl;
                break;
            }
            else if(bytesReceived == 0)
            {
                std::cout << px::WarnPrefix() << "Client disconnected" << std::endl;
                break;
            }
            response = serv->Interpeter(std::string(buf),client_IP,serv);
            #ifdef PX_DEBUG
                std::cout << client_IP << ": " << buf << std::endl;
            #endif
            // send response
            bytesReceived = write(sockfd, response.c_str(), response.size());
            #ifdef PX_DEBUG
                std::cout <<"server->"<<client_IP<<": " << response.c_str() << std::endl;
            #endif
            if(bytesReceived < 0)
            {
                std::cout << px::ErrorPrefix() << "Socket Error at " << std::this_thread::get_id() << " on server " << serv << " closing socket" << std::endl;
                break;
            }
        }
    }
    template<int buffersize>
    void RUN_MAIN(px::server<buffersize>* serv)
    {
        std::cout << "started Main worker of " << serv << " at "<< std::this_thread::get_id() << std::endl;
        //create socket
        int sockfd, newsockfd;
        socklen_t clilen;
        struct sockaddr_in serv_addr, cli_addr;
        int n;

        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd < 0){
            std::cout << px::ErrorPrefix() << "Failed to open socket!" << std::endl;exit(-1);}

        // Bind the socket to ip and port
        bzero((char*)&serv_addr,sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(serv->port);
        if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
            std::cout << px::ErrorPrefix() << "Failed to bind socket!" << std::endl;exit(-2);}

        std::cout << px::InfoPrefix() << serv << " listening for connections" << std::endl;
        serv->OK = 1;
        while(serv->running)
        {
            listen(sockfd,5);
            // und wir warten und wir warten und wir warten (spongebob reference(german)(might look up which episode)) (waiting for connections)
            clilen = sizeof(cli_addr);
            newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr,&clilen);
            if(newsockfd < 0){
                std::cout << px::ErrorPrefix() << "Failed to accept connection from client!" << std::endl;exit(-3);}
            // open handler thread
            std::string IP = "";
            char cIP[15];
            inet_ntop(AF_INET, &(cli_addr.sin_addr), cIP, 15);
            IP = cIP;
            serv->CLIENT_THREADS.push_back(std::thread(px::RUN_CLIENT<buffersize>,newsockfd,serv,IP));
        }
    }
}
#endif