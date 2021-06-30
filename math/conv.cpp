/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
conv.cpp (c) 2021
Desc: description
Created:  2021-06-26T12:23:49.023Z
Modified: 2021-06-27T17:11:48.358Z
*/

#include <bitset>
#include <sstream>

namespace px
{
    namespace math
    {
        long HexToDec(std::string* hex)
        {
            long dec = 0;
            std::stringstream ss;
            ss << hex;
            ss >> std::hex >> dec;
            return dec;
        }

        template<int width>
        std::string HexToBinary(std::string* hex)
        {
            return std::bitset<width>(HexToDec(hex)).to_string();
        }

        std::string DecToHex(long* dec)
        {
            std::stringstream ss;
            ss << std::hex << *dec;
            return ss.str();
        }

        template<int width>
        std::string DecToBinary(long* dec)
        {
            std::bitset<width>(dec).to_string();
        }

        void BinaryToDec()
        {
        }

        void BinaryToHex()
        {
        }
    }
}
