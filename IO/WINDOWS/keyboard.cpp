/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
keyboard.cpp (c) 2021
Desc: description
Created:  2021-08-09T17:12:51.678Z
Modified: 2021-08-09T18:19:34.399Z
*/
#pragma once
#include <list>
#include <thread>

namespace px::IO::keyboard {
    namespace key {
        enum keys {
            a=10,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,leftShift,rightShift,leftCtrl,rightCtrl,
            leftAlt,rightAlt,leftMeta,rightMeta,FN
        };
    }

    struct registeredFunction {  
        void(*m_function)();
        int m_keyNum;
        
        registeredFunction(void(*p_function)(),int p_keyNum) 
            :m_function(p_function),m_keyNum(p_keyNum){}
    };

    std::list<registeredFunction> registeredFunctions;

    void registerKeyPressedEvent(void(*p_function)(),int p_keynum)
    {
        registeredFunctions.push_back(registeredFunction(p_function,p_keynum));
    }

    void FireKeyEvent(int p_keyNum, bool executeAsync)
    {
        for(registeredFunction I : registeredFunctions) {
            if(I.m_keyNum == p_keyNum) {
                if(executeAsync)   
                {
                    std::thread exThr(I.m_function);
                }
                else
                {
                    I.m_function();
                }
            }
        }
    }
    
    void getKeyState(int p_key)
    {
    }
    void getKeyState(key::keys p_key)
    {
    }

    /**
     * @brief #define __PX_IO_AUTO_START_KEYBOARD_LISTENER__ to auto start
     * 
     * @return true 
     * @return false 
     */
    bool startListener()
    {
    }

    #ifdef __PX_IO_AUTO_START_KEYBOARD_LISTENER__
        //autostart
        bool AUTOSTART_LISTENER_THIS_IS_NOT_A_REAL_VARIABLE = startListener();
    #endif
}