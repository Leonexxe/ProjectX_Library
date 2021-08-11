/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
thread.cpp (c) 2021
Desc: description
Created:  2021-07-25T04:33:29.176Z
Modified: 2021-07-26T00:10:01.161Z
*/

#pragma once
#include <string>
#include <list>
#include <thread>

namespace px
{
    class application;
    class thread
    {
        private:
        std::string name;
        std::thread* THR;
        application* app;
        void(*entryFunction)(application*);
        
        public:
        thread(std::string name,void(*entryFunction)(application*),application* app)
            :name(name),entryFunction(entryFunction),app(app){}

        void RUN()
        {
            std::thread THR(entryFunction,this->app);
            this->THR = &THR;
            //! abort gets called here on return
        }

        void close()
        {
        }

        std::thread* getThread(){return this->THR;}
    };
}