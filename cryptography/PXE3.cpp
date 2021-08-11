/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
PXE3.cpp (c) 2021
Desc: description
Created:  2021-06-28T19:51:40.068Z
Modified: 2021-07-17T23:30:04.167Z
*/

#pragma once
#include <string>
#include <list>
#include "../sysout.h"
#include "../tools/lists.cpp"

namespace PXE3
{
    template<short length>
    struct subkey
    {
        char subK[length];
    };
    
    template<short length>
    class key
    {
        public:
        short subKeyLen = length;
        subkey<length> subkeys[128];
    };

    template<short length,int BUF_SIZE>
    std::string decrypt(char cypher[BUF_SIZE], key<length>* Key)
    {
        //! cypher.size() needs to return a multiple of length else this wont work
        std::string ret;
        unsigned long size = sizeof(cypher)/length;
        for(unsigned long I = 0;I<size;I++)
        {
            std::string set;
            for(int II = 0;II<length;II++)
            {
                set+=cypher[I+II];
            }
            for(short II = 0;II<128;II++)
            {
                //II = subkey
                if(std::string(Key->subkeys[II].subK) == set)
                {
                    ret+=II;
                    std::cout << II << " =/= " << "("<<I*5<<"-"<<I*5+5<<")" <<std::endl;
                    break;
                }
                else
                {
                    std::cout << II << " =/= " << "("<<I*5<<"-"<<I*5+5<<")" <<std::endl;
                }
            }
        }
        return ret;
    }

    template<short length,int size>
    char encrypt(std::string* msg, key<length>* Key)
    {
        #ifdef PXE3_DEBUG
            std::cout << " encrypting " << msg << " with key " << Key <<"..."<< std::endl;
        #endif
        char cypher[msg->size()*length];
        int II = 0;
        for(char I : *msg)
        {
            for(short III = 0;III<length;III++)
            {
                cypher[II++] = Key->subkeys[(int)I].subK[III];
            }
        }
        #ifdef PXE3_DEBUG
            std::cout << "done!" << std::endl;
        #endif
        return cypher;
    }

    template<short length>
    void genSubKey(int I, key<length>* Key)
    {
        for(int II = 0;II<length;II++)
        {
            int rand = px::math::random<int,int>(1,126);
            #ifdef PXE3_DEBUG
                std::cout << "("<<I<<") <== ("<<II<<") <== " << rand << std::endl;
            #endif
            Key->subkeys[I].subK[II] = (char)rand;
        }
        for(int III = 0;III < I;III++)
        {
            #ifdef PXE3_DEBUG
                std::cout << III << " |==| " << I << std::endl;
            #endif
            if(std::string(Key->subkeys[I].subK) == std::string(Key->subkeys[III].subK))
            {
                genSubKey<length>(I,Key);
            }
        }
    }
    
    template<short length>
    key<length> genKey()
    {
        key<length> Key;
        for(int I = 0;I < 128;I++)
        {
            genSubKey<length>(I,&Key);
        }
        return Key;
    }
}