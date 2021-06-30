#pragma once
#include <string>
#include <projectX/tools/strings.cpp>
#include <list>
#include <boost/filesystem.hpp>
#include <projectX/sysout/sysout.cpp>

namespace px
{
    namespace FBC
    {

        bool IS_FBC_INIT = 0;
        class FBCpair
        {
            public:
            std::string frontend = "";
            std::string backend = "";
            FBCpair(char f, std::string b)
            {
                this->frontend = std::to_string(f);
                this->backend = b;
            }
            FBCpair(){}
        };

        static FBCpair pairs[1000000]; // this array may need to be enlarged at some point (might allocate this in heap)
        static int pairCount = 0;

        static void FBC_INIT()
        {
            if(IS_FBC_INIT){return;}
            px::FBC::IS_FBC_INIT = 1;
            boost::filesystem::path p("/.projectX/convert.projectx.txt");
            boost::filesystem::fstream jsonstream(p);
            int FCC = 121305;
            char file[FCC];
            jsonstream.read(file, FCC);
            std::string FILE = "";
            int i = 0;
            for(char I : file){FILE+=I;i++;}
            pairCount = i;
            i = 0;    
            std::cout << "initiating pairs 0 - " << pairCount <<"("<< &pairs[0] << " -  " << &pairs[pairCount+1]<<")...";
            std::string lout;
            for(char I : file)
            {
                pairs[i] = FBCpair(I, "std::"+std::to_string(i)+"::");
                std::string out;
                px::cDelete(&lout);
                out = "(" + std::to_string(i) + "/" + std::to_string(pairCount) + ")";
                lout = out;
                std::cout << out;
                i++;
            }
            std::cout << "done!" << std::endl;
        }

        static std::string FTB(std::string* data)
        {
            std::cout << InfoPrefix() << "[FBC] converting " << data << " for backend...";
            if(!IS_FBC_INIT){FBC_INIT();}
            std::string ret = "";
            for(char I : *data)
            {
                int found = 0;
                for(int i = 0;i<pairCount;i++)
                {
                    if(std::to_string(I) == pairs[i].frontend)
                    {
                        ret = ret + pairs[i].backend;
                        found = 1;
                        break;
                    }
                }
                if(found == 0)
                {
                    ret = ret + I;
                }
            }
            std::cout << "done!" << std::endl;
            return ret;
        }

        static void printPairs(int max)
        {
            std::cout << "printing FBC pairs..." << std::endl;
            int i = 0;
            for(FBCpair I : px::FBC::pairs)
            {
                if(i >= max){break;}
                std::cout << "[" << i++ << "]" << I.backend << " >> " << I.frontend << "(" << &I << ")" << std::endl;
            }
        }
        static void printPairs(){px::FBC::printPairs(px::FBC::pairCount);}

        static std::string BTF(std::string* data)
        {
            std::cout << InfoPrefix() << "[FBC] converting " << data << " for frontend...";
            if(!IS_FBC_INIT){FBC_INIT();}
            std::string ret = *data;
            for(px::FBC::FBCpair I : px::FBC::pairs)
            {
                ret = strReplace(ret, I.backend, I.frontend);
            }
            std::cout << "done!" << std::endl;
            return ret;
        }

        static void deallocate(){delete[] px::FBC::pairs;}
    }
}