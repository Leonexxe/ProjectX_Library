/*############################################################################################################
# File: c:\Users\Administrator\OneDrive\Dokumente\GitHub\ProjectX_Library\net\windows\connection.cpp         #
# Project: c:\Users\Administrator\OneDrive\Dokumente\GitHub\ProjectX_Library\net\windows                     #
# Created Date: Wednesday, June 30th 2021, 9:18:58 pm                                                        #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#include <string>
#include <list>
#include <projectX/tools/strings.cpp>
#include <projectX/sysout.h>
#include <projectX/net/addr.cpp>
#include <thread>
#include "../net.cpp"
#include "../../net.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

namespace px
{
    class connection
    {
        private:
        bool running = 1;
        bool m_switchProtocol = 0;
        bool hasStopped = 0;
        std::string m_lastReceived = "";
        std::string m_send = "NULL";

        public:
        px::net::netProtocol protocol = px::net::STR;
        std::string(*RecvFunction)(std::string*,connection*) = nullptr;
        std::string _IN = "";
        std::string _OUT = "";
        std::string m_STRSend;
        bool disconnectAfterReceive = 0;
        int sockfd;
        px::addr ADDR;

        connection(px::addr p_ADDR,std::string(*recvFunct)(std::string*, connection*),std::string STRsend = "")
            :ADDR(p_ADDR),RecvFunction(recvFunct),m_STRSend(STRsend)
        {}

        int _connect()
        {
            //connect
            struct sockaddr_in serv_addr;
            struct hostent *server;

            /* create socket point*/
            this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

            if(sockfd < 0) {
                std::cout << px::ErrorPrefix() << "Error while opening socket!" << std::endl;
                return -1;
            }

            server = gethostbyname(this->ADDR.IP.c_str());

            if(server == NULL) {
                std::cout << px::ErrorPrefix() << "host not found!" << std::endl;
                return -2;
            }

            bzero((char*) &serv_addr, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
            serv_addr.sin_port = htons(this->ADDR.port);

            /* now connect to the server */
            if(connect(this->sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
                std::cout << px::ErrorPrefix() << "Error while connecting to server!" << std::endl;

            //RUN
            this->Run();
            return 0;
        }

        void reconnect()
        {
            this->running = 0;
            while(!this->hasStopped){}
            this->_connect();
        }

        unsigned char doSend()
        {
            const char* msg = this->m_send.c_str();
            int n;
            if(this->running)
                n = write(this->sockfd, msg, strlen(msg));
            else
                return -1;
            std::cout << "sent " << msg << " to server!" << std::endl;
            if(n < 0)
                std::cout << px::ErrorPrefix() << "Error while sending data to server!" << std::endl;
            return 0;
        }

        unsigned char _send(std::string s)
        {
            this->m_send = s;
            return this->doSend();
        }

        std::string getLastReceived(bool clear = 1)
        {
            while(this->m_lastReceived == ""){}
            if(clear)
            {
                std::string ret = this->m_lastReceived;
                this->m_lastReceived = "";
                return ret;
            }
            else
                return this->m_lastReceived;
        }

        std::string receive()
        {
            char server_reply[PX_NET_BUFFER_SIZE];
            bzero(server_reply, PX_NET_BUFFER_SIZE);
            int n = read(sockfd, server_reply, PX_NET_BUFFER_SIZE);
            if(n < 0)
                return "";
            this->m_lastReceived = std::string(server_reply);
            return std::string(server_reply);
        }

        int setProtocol(px::net::netProtocol protocol)
        {
            this->protocol = protocol;
            this->m_switchProtocol = 1;
        }

        int Run()
        {
            this->_send(this->m_STRSend);
            while(this->running){
                std::string resp = this->receive();
                if(this->_send(this->RecvFunction(&resp,this)) == -1)
                    return -1;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));}
            return 0;
        }

        void kill()
        {
            this->running = 0;
        }
    };
}