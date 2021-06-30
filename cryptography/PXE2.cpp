/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
PXE2.cpp (c) 2021
Desc: description
Created:  2021-06-28T16:47:33.279Z
Modified: 2021-06-28T19:54:22.458Z
*/

#pragma once
#include <string>
#include <list>

namespace PXE2
{
    bool __init__()
    {
        return 1;
    }
    
    bool t_init = __init__();

    class KEY
    {
        public:
        KEY(std::list<std::string> subkeys)
        {
        }
        ~KEY()
        {
        }
    };

    std::string encrypt()
    {
        std::string ret;
        return ret;
    }

    std::string decrypt(std::string cypher,PXE2::KEY key)
    {
        std::string ret;
        return ret;
    }

    std::string getKey(int subKeyLength)
    {
        std::string ret;
        return ret;
    }
}