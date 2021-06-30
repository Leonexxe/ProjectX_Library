#pragma once
#include <list>
#include "path.cpp"
#include <string>
#include <projectX/tools/lists.cpp>
#include <fstream>
#include <iostream>

namespace px
{
    namespace fs
    {
        static unsigned long MAX_FILE_SIZE = 0;
        class file
        {
            private:
            int line_c = 0;
            public:
            file(std::string *s)
            {
                this->path = s;
                this->read();
            }
            px::fs::path path;
            std::fstream File;

            std::list<std::string> lines;
            void append(std::string *s) {
                this->lines.push_back(*s);
            }

            void save() {
                std::ofstream fout;
                fout.open(this->path.getPath());
                for(std::string I : this->lines)
                {
                    fout << I << std::endl;
                }
                fout.close();
            }

            void read() {
                std::ifstream fin;
                fin.open(this->path.getPath());
                char data[px::fs::MAX_FILE_SIZE];
                fin >> data;
                std::cout << data << std::endl;
                for(std::string I : split(data, "\n"))
                {
                    this->lines.push_back(I);
                }
                this->File.close();
            }

            std::string getContent() {
                std::string ret = "";
                for(std::string I : this->lines)
                {
                    ret+="\n"+I;
                }
                return ret;
            }

            std::string nextline() {
                this->line_c++;
                return px::tools::lists::getElementByIndex<std::string>(&this->lines,this->line_c);
            }

            void clear(){this->lines.clear();}
            void operator<<(std::string *s){this->append(s);}
            void operator<<(std::string s){this->append(&s);}
            void operator>>(std::string *s){*s = this->nextline();}
            void operator=(std::string *s)
            {
                this->clear();
                this->append(s);
            }
        };
    }
}