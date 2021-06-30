#pragma once
#include <string>
#include <list>
#include <projectX/tools/strings.cpp>
#include <projectX/sysout.h>
#include <projectX/net/addr.cpp>
#include <thread>

namespace px
{
    class connection
    {
        private:
        bool abortRecvWait  = 0;
        bool running        = 1;

        public:
        std::string IN = "";
        std::string OUT = "";
        px::addr ADDR;

        connection(px::addr)
        {
        }

        void disconnect()
        {
        }

        void send()
        {
        }

        std::string receive()
        {
            //waiting for the recv thread to write to this->IN
            while(this->IN == "" && this->abortRecvWait != 1){/*sleep*/}
            // resetting this->abortRecvWaits since otherwise the receive function would just always be aborted immediately
            if(this->abortRecvWait){this->abortRecvWait = 0;}
            return this->IN;
        }

        void(*RecvFunction)(std::string*) = nullptr;

        void recvThreadWork()
        {
            #ifndef PX_NET_SILENCE
                std::cout << "started recvThread serverIP: " << this->ADDR.IP <<":"<<this->ADDR.port<< " at "<<this<< std::endl;
            #endif
            while(this->running)
            {
                std::string msg = "";
                //do recv
                this->IN = msg;
                if(this->RecvFunction != nullptr)
                {
                    this->RecvFunction(&msg);
                }
            }
            #ifndef PX_NET_SILENCE
                std::cout << "ended recvThread serverIP: " << this->ADDR.IP <<":"<<this->ADDR.port<< " at "<<this<< std::endl;
            #endif
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