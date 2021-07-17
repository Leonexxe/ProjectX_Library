/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
PXE.cpp (c) 2021
Desc: description
Created:  2021-06-30T13:12:49.866Z
Modified: 2021-06-30T23:56:41.994Z
*/

#include "PXE3.cpp"

namespace PXE
{
    template<short length>
    class PXE3
    {
        public:
        PXE3(PXE3::key<length> Key)
            : Key(Key) {} 

        ~PXE3(){}

        PXE3::key<length> Key();

        std::string decrypt(std::string* cypher)
        {
            return PXE3::decrypt<length>(cypher,&this->key);
        }

        std::string encrypt(std::string* msg)
        {
            return PXE3::encrypt<length>(msg,&this->key);
        }
    };
}