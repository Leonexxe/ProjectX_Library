#pragma once
#include <list>
#include "path.cpp"
#include <string>
#include <projectX/tools/lists.cpp>
#include <fstream>
#include <iostream>
#include <projectX/constants/sizes.cpp>
#include "filesystem_WINDOWS.cpp"

namespace px
{
    namespace fs
    {
        class file
        {
            private:
            int getNextLineIndex()
            {
                return this->cLIndex++;
            }
            int cLIndex = 0;
            int line_c = 0;
            std::list<std::string> lines;
            std::string filename;
            public:
            file(std::string* s,std::string* fname)
                : filename(*fname) {}
            ~file(){}

            void read()
            {
                std::ifstream readfile(this->filename);
                std::string text;
                while(getline(readfile,text))
                {
                    this->lines.push_back(text);
                }
                readfile.close();
            }

            void write(std::string s)
            {
                std::ofstream writefile(this->filename);
                for(std::string I : this->lines)
                {
                    writefile << I;
                }
                writefile << s;
                writefile.close();
            }

            void clear()
            {
                this->lines.empty();
            }

            void operator<<(std::string s)
            {
                this->write(s);
            }
            
            void operator>>(std::list<std::string>* s)
            {
                for(int I = 0;I<this->lines.size();I++)
                {
                    s->push_back(px::tools::lists::getElementByIndex(&this->lines,I));
                }
            }

            void operator>>(std::string* s)
            {
                for(std::string I : this->lines)
                {
                    *s+=I+"\n";
                }
            }

            void operator>>(px::fs::file* target)
            {
                px::fs::copy(this,target);
            }
        };
    }
}