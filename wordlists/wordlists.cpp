#pragma once
#include <list>
#include <string>
#include <projectX/sysout.h>
namespace px
{
    namespace wordlists
    {
        class wordlist
        {
            public:
            wordlist(){}

            std::list<std::string> words;

            void remove(std::string* src)
            {
            }

            void censor(std::string* src)
            {
                std::cout << px::InfoPrefix() << " censoring " << src << " with wordlist " << this << "..." << std::endl;
                for(std::string I : this->words)
                {
                    std::cout << px::InfoPrefix() << px::indention(1) << "censoring \"" << I << "\"...";
                    //replace
                    std::cout << px::sysDone() << std::endl;
                }
            }
            
            void operator-(std::string* src){this->remove(src);}
            void operator*(std::string* src){this->censor(src);}

            void add(std::string w)
            {
                this->words.push_back(w);
            }
        };
        namespace bad
        {
            px::wordlists::wordlist all;
            px::wordlists::wordlist racist;
            px::wordlists::wordlist homophobe;
            px::wordlists::wordlist swearing;
        }
    }
}