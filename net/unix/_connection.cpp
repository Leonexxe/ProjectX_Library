/*############################################################################################################
# File: c:\Users\Administrator\OneDrive\Dokumente\GitHub\ProjectX_Library\net\unix\connection.cpp            #
# Project: c:\Users\Administrator\OneDrive\Dokumente\GitHub\ProjectX_Library\net\unix                        #
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

namespace px
{
    class connection
    {
        private:
        bool abortRecvWait  = 0;
        bool running        = 1;
        bool m_switchProtocol = 0;
        std::string m_lastReceived = "";
        std::string m_send;

        public:
        px::net::netProtocol protocol = px::net::STR;
        std::string(*RecvFunction)(std::string*,connection*) = nullptr;
        std::string IN = "";
        std::string OUT = "";
        px::addr ADDR;

        connection(px::addr p_ADDR,std::string(*recvFunct)(std::string*, connection*))
            :ADDR(p_ADDR),RecvFunction(recvFunct)
        {}

        void reconnect()
        {      
        }

        unsigned char doSend()
        {  
        }

        unsigned char send(std::string s)
        {
            if(this->protocol != px::net::RSR)
                return 1;
            if(this->m_send == "")
                this->m_send = s;
            else
                return 2;
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
            while(this->IN == "" && this->abortRecvWait != 1){}
            // resetting this->abortRecvWaits since otherwise the receive function would just always be aborted immediately
            if(this->abortRecvWait){this->abortRecvWait = 0;}
            return this->IN;
        }

        int setProtocol(px::net::netProtocol protocol)
        {
            switch(protocol)
            {
                case(px::net::RTS):
                    break;
                case(px::net::STR):
                    break;
                case(px::net::RSR):
                    break;
            }
            this->protocol = protocol;
            this->m_switchProtocol = 1;
        }

        void ThreadRun(std::string STRsend = "")
        {
            do{switch(this->protocol){
            /////////////////////////////////////////////
            //*RTS
            case(px::net::RTS):
            while(this->running && !this->m_switchProtocol) {this->m_switchProtocol = 0;
                std::string msg = this->receive();
                this->RecvFunction(&msg,this);
                //send result of the above line
            }
            break;

            //*STR
            case(px::net::STR):
            //send STRsend
            while(this->running && !this->m_switchProtocol) {this->m_switchProtocol = 0;
                std::string msg = this->receive();
                this->RecvFunction(&msg,this);
                //send result of the above line
            }
            break;

            //*RSR
            case(px::net::RSR):
            while(this->running && !this->m_switchProtocol) {this->m_switchProtocol = 0;
                this->m_lastReceived = this->receive();
            }
            break;
            /////////////////////////////////////////////
            }}while(this->m_switchProtocol);
        }


        void cancelRecvWait()
        {
            this->abortRecvWait = true;
        }

        void kill()
        {
            this->running = 0;
        }
    };
}