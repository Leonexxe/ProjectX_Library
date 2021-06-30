#pragma once
#include <string>
#include <list>

namespace px
{
    class initcontroller;
    std::list<px::initcontroller*> initcontrollers;
    class initcontroller
    {
        public:
        initcontroller(void(*funct)(), std::string name)
        {
            this->name = name;
            this->funct = funct;
            px::initcontrollers.push_back(this);
        }
        std::string name;
        bool valid = 0;
        void (*funct)();
    };

    void getNewInitController(void(*funct)(),std::string name)
    {
        initcontroller(funct,name);
    }

    void checkInitControl(std::string controllerName)
    {
        for(auto I : initcontrollers)
        {
            if(I->name == controllerName)
            {
                if(!I->valid)
                {
                    I->funct();
                    I->valid = 1;
                }
            }
        }
    }
}