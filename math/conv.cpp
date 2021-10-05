/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
conv.cpp (c) 2021
Desc: description
Created:  2021-06-26T12:23:49.023Z
Modified: 2021-08-24T18:07:17.887Z
*/

#pragma once
#include <bitset>
#include <sstream>
#include "../tools/strings.cpp"

namespace px
{
    namespace math
    {
        template<typename T>
        T HexToDec(std::string* hex)
        {
            T dec = 0;
            std::stringstream ss;
            ss << hex;
            ss >> std::hex >> dec;
            return dec;
        }

        template<int width>
        std::string HexToBinary(std::string* hex)
        {
            return std::bitset<width>(HexToDec<long long>(hex)).to_string();
        }

        template<typename T>
        std::string DecToHex(T* dec,int fixLen = 0)
        {
            std::stringstream ss;
            ss << std::hex << *dec;
            if(fixLen == 0)
                return ss.str();
            std::string ret;
            std::string num = ss.str();
            px::text::manipulation::fillFront(&ret,'0',&num,fixLen);
            return ret;
        }

        template<int width>
        std::string DecToBinary(long dec)
        {
            return std::bitset<width>(dec).to_string();
        }

        void BinaryToDec()
        {
        }

        void BinaryToHex()
        {
        }
    }
}
