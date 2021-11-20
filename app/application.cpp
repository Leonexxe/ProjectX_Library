/*############################################################################################################
# File: c:\Users\Administrator\OneDrive\Dokumente\GitHub\ProjectX_Library\app\application.cpp                #
# Project: c:\Users\Administrator\OneDrive\Dokumente\GitHub\ProjectX_Library\app                             #
# Created Date: Wednesday, August 11th 2021, 7:37:10 am                                                      #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#ifdef PX_APP_NO_USE_NET_SERVER
    #define PX_NET_NO_SERVER
#endif
#include "../net.h"
#include <list>
#include <string>
#include "../sysout.h"
#include <thread>
#include "../tools/converters.cpp"
#include "../tools/convert.cpp"
#include "../tools/strings.cpp"
#include "../tools/arrays.cpp"
#include "../logging/log.cpp"
#include "../math/conv.cpp"
#include <streambuf>
#ifdef PX_WIN
    #include <windows.h>
    #include <process.h>
#endif
#include <chrono>
#include <csignal>
#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include "../threading.h"
#define PX_APP_MONITOR_OFFSET 9
#ifdef PX_APP_ENABLE_PXE3_FILE_ENCRYPTION
    #include "../PXE.h"
#endif

namespace px
{
    template<int threadslots>
    class application
    {
        private:
        #if defined(PX_APP_DYNAMIC_RUNTIME_BIND)
            int RUNTIMEBINDTHREADSLOT = 0;
        #endif
        int RAMLimit = 0;
        int UIThreadSlot = 0;
        int threadLimit = 0;
        bool Running = 0;
        std::list<px::connection> MEM_NET_CONNECTIONS;

        //multithreading
        bool usedThreadSlots[threadslots] = {0};
        std::thread m_threadslots[threadslots];
        bool endChildThreadsOnMainEnd = 0;
        
        void(*entryFunction)(application*);
        
        public:
        bool hasAppMonitor = 0;
        char** argv;
        const int argc;
        mutable std::list<std::string> OUT_BUFFER;
        void(*callOnLog)(std::string*) = nullptr;
        const std::string m_Pname = "";
        #ifdef PX_APP_ENABLE_PXE3_FILE_ENCRYPTION
            PXE3::PXE3 m_pxe3;
        #endif
        std::string m_AppName = "";
        #ifdef PX_APP_EXTENSION_CSUI
            std::string CS_EXE = "";
        #endif

        //?
        //? constructor
        //?
        /**
         * @brief Construct a new application object
         * 
         * @param entryFunction 
         * @param argc 
         * @param argv 
         * @param installPath 
         * @param processName the name of the executable example: "MyApplication.exe"
         * @param appName the name of the application, don't confuse this with processName
         */
        application(
            //parameters
            void(*entryFunction)(application*), 
            int argc, char** argv,
            std::string processName,
            #ifdef PX_APP_ENABLE_PXE3_FILE_ENCRYPTION
                PXE3::PXE3 pxe,
            #endif
            std::string installPath="",
            std::string appName = "MyApp")
            //initializer list
            :entryFunction(entryFunction),
            argc(argc),argv(argv),
            m_InstallPath(installPath),
            m_Pname(processName),
            #ifdef PX_APP_ENABLE_PXE3_FILE_ENCRYPTION
                m_pxe3(pxe),
            #endif
            m_AppName(appName)
        {
            for(int I = 0;I<argc;I++)
            {
                if(argv[I] == "-ramlimit")
                {
                    int limit = 0;
                    std::string strLimit;
                    px::converters::CharArrayToStr(argv[++I],&strLimit);
                    px::converters::strToInt(&limit,&strLimit);
                    this->setRAMLimit(limit);
                    this->LOG(px::InfoPrefix() + "set ram limit to " + strLimit + " bytes" + "\n",1);
                }
                else if(argv[I] == "-maxthreads")
                {
                    int limit = 0;
                    std::string strLimit;
                    px::converters::CharArrayToStr(argv[++I],&strLimit);
                    px::converters::strToInt(&limit,&strLimit);
                    this->setThreadLimit(limit);
                    this->LOG(px::InfoPrefix()+"set thread limit to "+strLimit+" threads" + "\n",1);
                }
                #ifdef PX_APP_ENABLE_CLI_L_INI
                else if(argv[0] == "-C")
                    if(argv[1] == "--ini")
                    {
                        std::cout << this->getINI(argv[2], argv[3]) << std::endl;
                        this->taskkill();
                    }
                #endif
            }
            this->openLog();
            std::string bar   = "################################################################################";
            std::string barEMP= "                                                                                ";
            this->LOG(bar);
            this->LOG(barEMP);
            this->LOG(px::getCenterText("session "+px::now(),bar.length()));
            this->LOG(barEMP);
            this->LOG(bar);
        }

        //?
        //? config
        //?
        mutable std::list<std::list<std::string>> iniData;
        mutable std::list<std::string> iniSections;
        std::string iniFile;
        void saveINI(std::string p_iniFile = "this->iniFile")
        {
            if(p_iniFile == "this->iniFile")
                p_iniFile = this->iniFile;
            std::ofstream outfile;
            outfile.open(p_iniFile);
            outfile << "";
            outfile.close();
            std::list<std::string> writeData;
            int II = 0;
            std::string tempString;
            for(std::string section : this->iniSections){
                writeData.push_back("["+section+"]\n");
            for(std::list<std::string> iniD : this->iniData){
                std::string iniDSection;II=0;for(std::string I : iniD){iniDSection=I;if(II==0){break;}II++;}
                if(iniDSection == section)
                {
                    tempString;II=0;for(std::string I : iniD){tempString=I;if(II==1){break;}II++;}
                    std::string blub = tempString;
                    tempString;II=0;for(std::string I : iniD){tempString=I;if(II==2){break;}II++;}
                    writeData.push_back(blub+"="+tempString+"\n");
                }
            }}
            outfile.open(p_iniFile, std::ios_base::app);
            for(std::string II : writeData)
            {
                std::string WRT = "";
                #ifdef PX_APP_ENABLE_PXE3_FILE_ENCRYPTION
                    this->m_pxe3.encrypt(&WRT,&II);
                #else
                    WRT = II;
                #endif
                outfile << WRT;
            }
            outfile.close();
        }
        void addINISection(std::string SECTION)
        {
            bool ex = 0;
            for(std::string section : this->iniSections)
            {
                if(section == SECTION)
                    ex = 1;
            }
            if(!ex)
                this->iniSections.push_back(SECTION);
        }
        void writeINI(std::string section,std::string name, std::string value)
        {
            this->delINI(section,name);//delete old entry
            this->iniData.push_back({section,name,value});
        }
        void delINI(std::string section,std::string name)
        {
            std::list<std::list<std::string>> newINI;
            int delEntries = 0;
            for(std::list<std::string> I : this->iniData)
                if(!(px::tools::lists::getElementByIndex(&I,-1) == section&&px::tools::lists::getElementByIndex(&I,0) == name))
                    newINI.push_back(I);
                else
                    delEntries++;
            this->iniData.clear();
            for(std::list<std::string> II : newINI)
                this->iniData.push_back(II);
            this->LOG("Deleted "+std::to_string(delEntries)+" Entries from the INI\n");
        }
        std::string getINI(std::string section,std::string name)
        {
            iniData.reverse();
            for(std::list<std::string> I : iniData)
            {
                if(
                    px::tools::lists::getElementByIndex(&I,-1) == section
                    && px::tools::lists::getElementByIndex(&I,0) == name
                    ){return px::tools::lists::getElementByIndex(&I,2);}
//                else
//                    this->LOG("! "+px::tools::lists::getElementByIndex(&I,-1)+"->"+px::tools::lists::getElementByIndex(&I,0)+"\n");
            }
            this->LOG(px::ErrorPrefix()+"-3 : INI entry ["+section+"]->"+name+" not found\n",0);
            std::cout << px::ErrorPrefix() << "-3 : INI entry [" << section << "]->" << name << " not found" << std::endl;
            this->taskkill();
        }
        void loadINI(std::string filename = ".ini")
        {   
            std::string filepath = this->m_InstallPath+"/config/"+filename;
            this->iniFile = filepath;
            this->LOG(px::InfoPrefix() +"loading config from "+filepath+"\n");
            std::ifstream infile(filepath);
            std::string cypherFileContent((std::istreambuf_iterator<char>(infile)),
                 std::istreambuf_iterator<char>());
            std::string decryptedFileContent;
            #ifdef PX_APP_ENABLE_PXE3_FILE_ENCRYPTION
                this->m_pxe3.decrypt(&decryptedFileContent,&cypherFileContent);
            #else
                decryptedFileContent = cypherFileContent;
            #endif
            std::stringstream ss;
            ss << decryptedFileContent;
            
            std::string line = "";
            std::string section = "";
            
            while(std::getline(ss,line))
            {
                std::string name = "";
                std::string value = "";
                if(line[0] == '[')
                    section = line.substr(1,line.size()-2);
                else
                {
                    std::list<std::string> segments = strSplit(strReplace(line," ",""),"=");
                    if(segments.size() < 1)
                    {
                        px::sysError("error while loading ini - error: -2");
                        this->taskkill();
                    }
                    int I = 0;
                    for(std::string II : segments)
                    {
                        if(I == 0)
                            name = II;
                        else if(I == 1)
                            value = II;
                        else
                            break;
                        I++;
                    }
                    std::cout << "{";
                    for(std::string III : segments){std::cout << III << ",";}
                    std::cout << "}" << std::endl;
                    #ifdef PX_APP_INI_DISPLAY_PASSWORD
                        this->LOG(px::getCustomPrefix("CONFIG",px::console_colors::_8colors::green)+"["+section+"]"+name+"="+value+"\n");
                    #else
                        if(px::strToUpper(name)=="PASSWORD")
                            this->LOG(px::getCustomPrefix("CONFIG",px::console_colors::_8colors::green)+"["+section+"]"+name+"=********\n");
                        else
                            this->LOG(px::getCustomPrefix("CONFIG",px::console_colors::_8colors::green)+"["+section+"]"+name+"="+value+"\n");
                    #endif
                    this->addINISection(section);
                    this->iniData.push_back({section,name,value});
                }
            }
        }

        //?
        //? RUN
        //?
        void RUN()
        {
            this->sysout(px::InfoPrefix() + "running application" + "\n");
            this->openThread(this->m_AppName+"_MAIN",this->entryFunction);
        }

        /**
         * @brief ************* execute at the end of "int main" *************
         */
        void EXECUTE_WHEN_OUT_OF_CODE_IN_MAIN()
        {   
            int oldruntimebind = 0;
            #if defined(PX_APP_BIND_RUNTIME_TO_UI)
                this->m_threadslots[this->UIThreadSlot].join();
                oldruntimebind = this->UIThreadSlot;
            #elif defined(PX_APP_DYNAMIC_RUNTIME_BIND)
                do
                {
                    this->m_threadslots[this->RUNTIMEBINDTHREADSLOT].join();
                    oldruntimebind = this->RUNTIMEBINDTHREADSLOT;
                }while(oldruntimebind != this->RUNTIMEBINDTHREADSLOT)
            #else
                this->m_threadslots[0].join();
            #endif
            //exit
            this->taskkill();
        }

        //?
        //? multithreading
        //?
        int openThread(std::string name,void(*entryFunction)(application*))
        {
            int ThreadSlot = -1;
            for(int I = 0;I<threadslots;I++)
            {
                if(this->usedThreadSlots[I] == 0)
                {
                    ThreadSlot = I;
                    break;
                }
            }
            if(ThreadSlot == -1)
            {
                this->LOG(px::ErrorPrefix() + "can't open thread because the threadlimit is already reached");
                return -1;
            }
            this->m_threadslots[ThreadSlot] = std::thread(entryFunction,this);
            this->usedThreadSlots[ThreadSlot] = 1;
            if(name == this->m_AppName+"_UI")
                this->UIThreadSlot = ThreadSlot;
            this->LOG(px::InfoPrefix() + "started thread " + px::intToString(ThreadSlot) + " as " + name + "\n");
            return ThreadSlot;
        }

        void closeThread(std::string name)
        {
        }

        //?
        //? NET
        //?
        connection* getServerConnection(
            std::string HOST,int PORT, //addr
            std::string(*recvFunct)(std::string*, connection*), //interpreter
            px::net::netProtocol protocol = net::STR, //protocol
            std::string STRsend = ""
        )
        {
            px::addr ADDR(HOST,PORT);
            this->MEM_NET_CONNECTIONS.push_back(connection(ADDR,recvFunct,STRsend));
            return &this->MEM_NET_CONNECTIONS.back();
        }

        #ifndef PX_APP_NO_USE_NET_SERVER
            template<int bufferSize>
            server<bufferSize> getServer(int port,std::string(*Interpeter)(std::string, std::string, server<bufferSize>*))
            {
                return px::server<bufferSize>(port,Interpeter);
            }
        #endif
        

        //?
        //? System Information
        //? TODO: own ram ussage, total ram ussage, total CPU ussage, own CPU ussage
        //?
        int getRamUssage() const
        {
            //!TODO: finish
            return 0;
        }
        int getCPUUssage() const
        {
            //!TODO: finish
            return 0;
        }

        //?
        //? FILESYSTEM
        //?
        std::string m_InstallPath = "";
        std::string m_LogPath = this->m_InstallPath + "/LOG";

        //?
        //? SYSOUT
        //?
        void sysout(std::string s) const
        {
            if(this->hasAppMonitor)
            {
                std::string str = s;
                #ifndef PX_APP_SYSOUT_DONT_CHECK_FORM
                    if(str.front() != '[')
                    {
                        str = px::InfoPrefix() + s;
                    }
                    px::strEndsWithNewLine(&str,1);
                #endif
                this->OUT_BUFFER.push_back(str);
            }
            else
                std::cout << s;
        }

        //?
        //? LOGGING
        //?
        void LOG(std::string s,bool doSysout = 1, std::string logName = "main")
        {
            if(this->callOnLog != nullptr)
                this->callOnLog(&s);
            std::string str = s;
            #ifndef PX_APP_SYSOUT_DONT_CHECK_FORM
                if(str.front() != '[')
                {
                    str = px::InfoPrefix() + s;
                }
                px::strEndsWithNewLine(&str,1);
            #endif
            this->sysout(s);
            #ifdef PX_APP_ENABLE_PXE3_FILE_ENCRYPTION
                std::string eStr = str;
                this->m_pxe3.encrypt(&eStr,&str);
                quickLog(logName,eStr);
            #else
                //quickLog(logName,px::erasePXPrefixColors(&str));
                quickLog(logName,str);
            #endif
        }

        void openLog(std::string name = "main") const
        {
            createlogger(this->m_LogPath+"/"+name+".log",name);
        }

        //?
        //? File IO
        //?
        std::string getFile(std::string fName)
        {
            std::string RET;
            std::ifstream t(fName);
            t.seekg(0, std::ios::end);
            size_t size = t.tellg();
            std::string buffer(size, ' ');
            t.seekg(0);
            t.read(&buffer[0], size); 
            #ifdef PX_APP_ENABLE_PXE3_FILE_ENCRYPTION
                this->m_pxe3.decrypt(&RET,&buffer);
            #else
                RET = buffer;
            #endif
        }

        #ifdef PX_APP_ENABLE_PXE3_FILE_ENCRYPTION
            void decryptFile(std::string fName)
            {
                std::ifstream t(fName);
                t.seekg(0, std::ios::end);
                size_t size = t.tellg();
                std::string buffer(size, ' ');
                t.seekg(0);
                t.read(&buffer[0], size); 
                
                std::string O = "";
                this->m_pxe3.decrypt(&O,&buffer);

                std::ofstream out(fName);
                out << O;
                out.close();
            }

            void encryptFile(std::string fName)
            {
                std::ifstream t(fName);
                t.seekg(0, std::ios::end);
                size_t size = t.tellg();
                std::string buffer(size, ' ');
                t.seekg(0);
                t.read(&buffer[0], size); 

                std::string O = "";
                this->m_pxe3.encrypt(&O,&buffer);

                std::ofstream out(fName);
                out << O;
                out.close();
            }
        #endif


        //?
        //? get&set
        //?
        void setRAMLimit(int NL){this->RAMLimit = NL;}
        int getRAMLimit() const{return this->RAMLimit;}
        void setThreadLimit(int NL){this->threadLimit = NL;}
        int getThreadLimit() const{return this->threadLimit;}
        bool getThreadSlotStatus(int slot) const{return this->usedThreadSlots[slot];}

        //?
        //? operators
        //?
        void operator<<(const std::string& s)
        {
            this->sysout(s);
        }

        //?
        //? exit
        //?
        void taskkill()
        {
            this->LOG(px::ErrorPrefix() + "taskkill...\n");
            #if defined(PX_APP_EXTENSION_CSUI)  && defined(PX_WIN)
                {
                    std::list<std::string> segs = strSplit(this->CS_EXE,"\\");
                    std::string cmd = "taskkill /IM " + segs.back() + " /F";
                    system(px::strToConstChar(&cmd));
                }
            #endif

            //! the main process is to be terminated last
            #ifdef PX_WIN
                std::string cmd = "taskkill /IM " + this->m_Pname + " /F";
                system(px::strToConstChar(&cmd));
            else
                std::string cmd = "pkill " + this->m_Pname;
                system(px::strToConstChar(&cmd));
            #endif
        }
        void _exit(int exitCode = -1)
        {
            for(int I = 0;I < threadslots;I++)
                this->m_threadslots[I].~thread();
            exit(exitCode);
        }
        void _abort()
        {
            for(int I = 0;I < threadslots;I++)
                this->m_threadslots[I].~thread();
            raise(SIGABRT);
        }
    };

    namespace globals
    {
        bool APP_BINARY_MONITOR;
    }
    template<int threadslots>
    void RUNAPPMONITOR(application<threadslots>* app)
    {
        std::cout << "app monitor started" << "\n";
        double sum = 0;
        double add = 1;
        // Start measuring time
        #ifdef PX_ARM64
            #warning (px) app monitor might not work on arm64
        #endif
        while(1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            for(std::string I : app->OUT_BUFFER)
                std::cout << I;
        }
        if(globals::APP_BINARY_MONITOR)
        {
            while(1){
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                for(std::string I : app->OUT_BUFFER)
                    for(char II : I)
                        std::cout << px::math::DecToBinary<8>(II);
            }
        }else{
        auto begin = std::chrono::high_resolution_clock::now();
        while(1)
        {
            //px::cDelete(&ss.str());
            std::stringstream ss;
            // Stop measuring time and calculate the elapsed time
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            std::string execTime = px::formattime24H(elapsed.count() / 1000000);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            #ifdef PX_WIN
                system("cls");
            #else
                system("clear");
            #endif
            //sleep -> clear -> print

            
            ss << getCenterText("APP MONITOR") << "\n";
            //monitor
            int barLength = px::getConsoleWidth() - 22;
            std::string emptyBar = "";
            for(int I = 0;I<barLength;I++)
                emptyBar+=" ";
            ss << "RAM ussage: " << app->getRamUssage() << "B [" <<emptyBar<< "]" << "\n";
            ss << "CPU ussage: " << app->getCPUUssage() << "% [" <<emptyBar<< "]" << "\n";
            ss << "Time elapsed: " << execTime << "\n";
            int threads = 0;
            for(int I = 0;I<threadslots;I++)
            {
                if(app->getThreadSlotStatus(I) == 1)
                    threads++;
            }
            ss << getCenterText("Threads - ") <<threads<< "\n";
            for(int I = 0;I<threadslots;I++)
            {
                if(app->getThreadSlotStatus(I) == 0)
                    ss << px::console_colors::_8colors::getColoredText("0",px::console_colors::_8colors::black);
                else
                    ss << px::console_colors::_8colors::getColoredText("1",px::console_colors::_8colors::green);
            }
            ss << "\n";
            ss << getCenterText("CONSOLE") << "\n";
            //sysout
            int skipTo = 0;
            int round = 0;
            int conHeight = px::getConsoleHeight();
            int conWidth = px::getConsoleWidth();
            if(app->OUT_BUFFER.size() > conHeight - PX_APP_MONITOR_OFFSET)
                skipTo = app->OUT_BUFFER.size() - (conHeight - PX_APP_MONITOR_OFFSET);
            if(skipTo > 1)
                ss << skipTo-1 << " log messages not shown...\n";
            else if(skipTo > 0)
                ss << skipTo-1 << " log message not shown...\n";
            for(std::string I : app->OUT_BUFFER)
            {
                if(round++ < skipTo)
                    continue;
                else
                {
                    if(I.size() < conWidth)
                        ss << I;
                    else
                        ss << I.substr(0,conWidth-4) <<"..."<<"\n";
                }
            }

            //print
            std::cout << ss.str();
        }}
    }

    template<int threadslots>
    void RUNRAMLIMIT(application<threadslots>* app)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if(app->getRamUssage() > app->getRAMLimit())
        {
            //! ram limit exceeded
        }
    }

    template<int threadslots>
    void startAPPMonitor(application<threadslots>* app)
    {
        app->openThread(app->m_AppName+"_MONITOR",&RUNAPPMONITOR);
        app->hasAppMonitor = 1;
    }

    void signalHandler(int signum)
    {
        switch(signum)
        {
            case(SIGABRT):
                std::cout << px::ErrorPrefix() << "SIGABRT was raised!" << "\n";
                break;
            default:
                std::cout << px::ErrorPrefix() << "signal " << signum << " raised!" << "\n";
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
