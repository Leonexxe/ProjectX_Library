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
#define PX_WIN
#include <string>
#include <list>
#include <projectX/tools/strings.cpp>
#include <projectX/sysout.h>
#include <projectX/net/addr.cpp>
#include <thread>
#include "../net.cpp"
#include "../../net.h"

namespace px
{
    bool initWinSock()
    {
        WSADATA wsa;

        std::cout << px::getCustomPrefix("INIT",px::console_colors::_8colors::cyan) << "Winsock..." << std::endl;
        if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
            printf("Failed. Error Code : %d",WSAGetLastError());
        px::sysDone();
        return 1;
    }
    bool b_initWinSock = initWinSock();
    class connection
    {
        private:
        bool running        = 1;
        bool m_switchProtocol = 0;
        bool hasStopped = 0;
        std::string m_lastReceived = "";
        std::string m_send = "NULL";

        public:
        SOCKET* socketPTR;
        px::net::netProtocol protocol = px::net::STR;
        std::string(*RecvFunction)(std::string*,connection*) = nullptr;
        std::string _IN = "";
        std::string _OUT = "";
        std::string m_STRSend;
        bool disconnectAfterReceive = 0;
        px::addr ADDR;

        connection(px::addr p_ADDR,std::string(*recvFunct)(std::string*, connection*),std::string STRsend = "")
            :ADDR(p_ADDR),RecvFunction(recvFunct),m_STRSend(STRsend)
        {}

        void _connect()
        {
            SOCKET s;
            this->socketPTR = &s;
            struct sockaddr_in server;

            //Create socket
            if((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
                printf("Could not create socket : %d" , WSAGetLastError());
            
            server.sin_addr.s_addr = inet_addr(this->ADDR.IP.c_str());
            server.sin_family = AF_INET;
            server.sin_port = htons(this->ADDR.port);

            // connect to remote
            if(connect(s,(struct sockaddr*)&server, sizeof(server)) < 0)
                px::sysError("socket connect error!");
            this->Run();
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
            if(send(*this->socketPTR,msg,strlen(msg), 0) < 0)
            {
                px::sysError("send failed");
                return 1;
            }
            else
            {
                //px::sysInfo("send success");
                return 0;
            }
        }

        unsigned char _send(std::string s)
        {
            if(this->protocol != px::net::RSR)
                return 1;
            if(this->m_send != "")
                return 2;
            this->m_send = s;
            this->doSend();
            return 0;
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
            int recv_size;
            if((recv_size = recv(*this->socketPTR, server_reply, PX_NET_BUFFER_SIZE, 0)) == SOCKET_ERROR)
                px::sysError("recv failed!");
            return std::string(server_reply);
        }

        int setProtocol(px::net::netProtocol protocol)
        {
            this->protocol = protocol;
            this->m_switchProtocol = 1;
        }

        int Run()
        {
            char rBuf[PX_NET_BUFFER_SIZE];
            //-first loop
            if(send(*this->socketPTR,this->m_STRSend.c_str(),PX_NET_BUFFER_SIZE, 0) < 0)
                return 1;
            int recv_size;
            if((recv_size = recv(*this->socketPTR,rBuf, PX_NET_BUFFER_SIZE, 0)) == SOCKET_ERROR)
                return 2;
            std::string s = rBuf;
            while(this->running)
            {
                if(send(*this->socketPTR,this->RecvFunction(&s,this).c_str(),PX_NET_BUFFER_SIZE, 0) < 0)
                    return 1;
                int recv_size;
                if((recv_size = recv(*this->socketPTR,rBuf, PX_NET_BUFFER_SIZE, 0)) == SOCKET_ERROR)
                    return 2;
                s = rBuf;
            }
            return 0;
        }

//        int Run()
//        {
//            // loop
//            do{switch(this->protocol){
//            /////////////////////////////////////////////
//            //*RTS
//            case(px::net::RTS):
//            while(this->running && !this->m_switchProtocol) {this->m_switchProtocol = 0;
//                std::string msg = this->receive();
//                this->RecvFunction(&msg,this);
//                if(this->disconnectAfterReceive){return 0;}
//                this->m_send = msg;this->doSend();
//            }
//            break;
//
//            //*STR
//            case(px::net::STR):
//            this->m_send = this->m_STRSend;
//            this->doSend();
//            while(this->running && !this->m_switchProtocol) {this->m_switchProtocol = 0;
//                std::string msg = this->receive();
//                this->RecvFunction(&msg,this);
//                if(this->disconnectAfterReceive){return 0;}
//                this->m_send = msg;this->doSend();
//            }
//            break;
//
//            //*RSR
//            case(px::net::RSR):
//            while(this->running && !this->m_switchProtocol) {this->m_switchProtocol = 0;
//                this->m_lastReceived = this->receive();
//            }
//            break;
//            /////////////////////////////////////////////
//            }}while(this->m_switchProtocol);
//            this->hasStopped = 0x0001;
//            return 0;
//        }

        void kill()
        {
            this->running = 0;
        }
    };
}