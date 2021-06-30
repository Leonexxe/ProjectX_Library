#pragma once
#include <list>
#include <string>
#include <projectX/tools/strings.cpp>

namespace px
{
    namespace fs
    {
        class path
        {
            public:
            path(std::string *s) {
                this->_path = split(*s+"/","/");
            }
            path(){}
            std::list<std::string> _path;
            bool isAbsolute = 0;
            std::string getPath()
            {
                std::string p;
                if(this->isAbsolute){p += "/";}
                bool isFirst = 1;
                for(std::string I : this->_path)
                {
                    if(isFirst == 0){isFirst = 0;p+="/";}else{isFirst = 0;}
                    p += I;
                }
                return p;
            }
        };
    }
}
