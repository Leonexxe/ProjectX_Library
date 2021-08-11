/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
application.cpp (c) 2021
Desc: description
Created:  2021-07-25T04:33:23.171Z
Modified: 2021-07-26T03:25:15.779Z
*/

#include <list>
#include <string>
#include "../sysout.h"
#include <thread>
#include "../tools/converters.cpp"
#include <csignal>

namespace px
{
    template<int threadslots>
    class application
    {
        private:
        int RAMLimit = 0;
        int threadLimit = 0;
        bool Running = 0;

        //multithreading
        bool usedThreadSlots[threadslots];
        std::thread threadslots[threadslots];
        bool endChildThreadsOnMainEnd = 0;
        
        void(*entryFunction)(application*);
        char** argv;
        int argc;
        
        public:
        std::list<std::string> OUT_BUFFER;

        //?
        //? constructor
        //?
        application(void(*entryFunction)(application*), int argc, char** argv)
            :entryFunction(entryFunction),argc(argc),argv(argv)
        {
            std::cout << px::InfoPrefix() << " application constructor invoked" << std::endl;
            for(int I = 0;I<argc;I++)
            {
                if(argv[I] == "-ramlimit")
                {
                    int limit = 0;
                    std::string strLimit;
                    px::converters::CharArrayToStr(argv[++I],&strLimit);
                    px::converters::strToInt(&limit,&strLimit);
                    this->setRAMLimit(limit);
                    std::cout << px::InfoPrefix() << "set ram limit to " << strLimit << " bytes" << std::endl;
                }
                else if(argv[I] == "-maxthreads")
                {
                    int limit = 0;
                    std::string strLimit;
                    px::converters::CharArrayToStr(argv[++I],&strLimit);
                    px::converters::strToInt(&limit,&strLimit);
                    this->setThreadLimit(limit);
                    std::cout << px::InfoPrefix() << "set thread limit to " << strLimit << " threads" << std::endl;
                }
            }
            std::cout << px::InfoPrefix() << " application constructor finished" << std::endl;
        }

        //?
        //? RUN
        //?
        void RUN()
        {
            std::cout << px::InfoPrefix() << " running application" << std::endl;
            std::cout << 0;
            this->openThread("APP_MAIN",this->entryFunction);
            std::cout << 4;
        }

        void EXECUTE_WHEN_OUT_OF_CODE_IN_MAIN()
        {   
            for(std::thread I : this->Threads){I.join();break;} // for some f*cking reason list.front() doesn't work cause 
                                                                // "error: no member named '__init__' in 'std::list" dont f*cking ask me
            //close threads
            for(std::thread I : this->Threads)
            {
                I.~thread();
            }
        }

        //?
        //? multithreading
        //?
        void openThread(std::string name,void(*entryFunction)(application*))
        {
            std::cout << 2;
            int ThreadSlot;
            for(int I = 0;I<threadslots;I++)
            {
                if(this->usedThreadSlots[I] == 0)
                {
                    ThreadSlot = I;
                    break;
                }
            }
            this->threadslots[ThreadSlot] = std::thread(entryFunction,this);
            std::cout << 3;
        }

        void closeThread(std::string name)
        {
        }

        //?
        //? System Information
        //? TODO: own ram ussage, total ram ussage, total CPU ussage, own CPU ussage
        //?
        int getRamUssage()
        {
            //!TODO: finish
            return 0;
        }
        int getCPUUssage()
        {
            //!TODO: finish
            return 0;
        }

        //?
        //? SYSOUT
        //?
        void sysout(std::string s)
        {
            this->OUT_BUFFER.push_back(s);
        }


        //?
        //? get&set
        //?
        void setRAMLimit(int NL){this->RAMLimit = NL;}
        int getRAMLimit() const{return this->RAMLimit;}
        void setThreadLimit(int NL){this->threadLimit = NL;}
        int getThreadLimit() const{return this->threadLimit;}

        //?
        //? operators
        //?
        void operator<<(std::string s)
        {
            this->sysout(s);
        }
    };

    void RUNAPPMONITOR(application* app)
    {
        std::cout << "app monitor started" << std::endl;
        bool first = 1;
        std::stringstream ss;
        while(1)
        {
            if(!first)
                px::cDelete(&ss.str());
            else
                first = 0;
                
            ss.clear();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            ss << getCenterText("APP MONITOR") << "\n";
            //monitor
            ss << "RAM ussage: " << app->getRamUssage() << "B [" <<"                        "<< "]" << "\n";
            ss << "CPU ussage: " << app->getCPUUssage() << "% [" <<"                        "<< "]" << "\n";
            ss << getCenterText("CONSOLE") << "\n";
            //sysout
            int skipTo = 0;
            int round = 0;
            if(app->OUT_BUFFER.size() > px::getConsoleHeight() - 4)
                skipTo = app->OUT_BUFFER.size() - (px::getConsoleHeight() - 4);
            if(skipTo > 0)
                ss << skipTo-1 << " log message(s) not shown...\n";
            for(std::string I : app->OUT_BUFFER)
            {
                if(round++ < skipTo)
                    continue;
                else
                    ss << I;
            }

            //print
            std::cout << ss.str();
        }
    }
    void RUNRAMLIMIT(application* app)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if(app->getRamUssage() > app->getRAMLimit())
        {
            //! ram limit exceeded
        }
    }

    void startAPPMonitor(application* app)
    {
        app->openThread("APP_MONITOR",&RUNAPPMONITOR);
    }

    void signalHandler(int signum)
    {
        switch(signum)
        {
            case(SIGABRT):
                std::cout << px::ErrorPrefix() << "abort() called!" << std::endl;
                break;
            default:
                std::cout << px::ErrorPrefix() << "signal " << signum << " raised!" << std::endl;
                exit(signum);
        }
    }

    void placeSignalHandlers()
    {
        signal(SIGABRT,signalHandler);
        signal(SIGFPE,signalHandler);
        signal(SIGILL,signalHandler);
        signal(SIGINT,signalHandler);
        signal(SIGSEGV,signalHandler);
        signal(SIGTERM,signalHandler);
    }
}
