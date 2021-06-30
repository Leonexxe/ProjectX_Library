/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
PXE3.cpp (c) 2021
Desc: description
Created:  2021-06-28T19:51:40.068Z
Modified: 2021-06-30T13:12:16.830Z
*/

#pragma once
#include <string>
#include <list>
#include "../sysout.h"

namespace PXE3
{
    template<short length>
    struct subkey
    {
        char subK[length];
    };
    
    template<short length>
    struct key
    {
        short subKeyLen = length;
        subkey<length> subkeys[127];
    };

    template<short length>
    std::string decrypt(std::string* cypher, key<length>* Key)
    {
    }

    template<short length>
    std::string encrypt(std::string* msg, key<length>* Key)
    {
        #ifdef PXE3_DEBUG
            std::cout << " encrypting " << msg << " with key " << key << std::endl;
        #endif
    }

    template<short length>
    key<length> genKey()
    {
        key<length> Key;
        for(int I = 0;I < 128;I++)
        {
            #ifdef PXE3_DEBUG
                std::cout << &Key.subkeys << "[" << &I << ":" << I << "]" << std::endl;
            #endif
            for(int II = 0;II<length;II++)
            {
                #ifdef PXE3_DEBUG
                    std::cout << &Key.subkeys << "[" << &I << ":" << I << "]" << &Key.subkeys[I].subK << "[" << &II << ":" << II << "]" << std::endl;
                #endif
                Key.subkeys[I].subK[II] = px::math::random<int,int>(1,127);
            }
        }
    }
}