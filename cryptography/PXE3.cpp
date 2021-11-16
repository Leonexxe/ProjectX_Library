/*############################################################################################################
# File: c:\Users\Administrator\OneDrive\Dokumente\GitHub\ProjectX_Library\cryptography\PXE3.cpp              #
# Project: c:\Users\Administrator\OneDrive\Dokumente\GitHub\ProjectX_Library\cryptography                    #
# Created Date: Wednesday, June 30th 2021, 9:18:57 pm                                                        #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/

#pragma once
#include <string>
#include <list>
#include <sstream>
#include "../sysout.h"
#include "../tools/lists.cpp"

#define PXE3_OFFSET 0 // 0
#define PXE3_SUPPORTED_CHAR_COUNT 255 // 128
#ifndef PXE3_COVERFLOW_MAX
    #define PXE3_COVERFLOW_MAX 0x0064
#endif
#ifndef PXE3_COVERFLOW_MIN
    #define PXE3_COVERFLOW_MIN 0x000A
#endif

namespace PXE3
{
    std::list<int> illegalChars = {0x0022,0x003B,0x002A};
//    class subKey
//    {
//        public:
//        subKey(){}
//        subKey(std::string p_chars)
//        {
//            for(char I : p_chars)
//                this->m_chars.push_back(I);
//        }
//        subKey(std::list<char> p_chars)
//            :m_chars(p_chars){}
//
//        std::list<char> m_chars;
//    };
    class PXE3
    {
        public:
        PXE3(std::string p_key,int p_length)
        {
            char counter = 0;
            for(int I = p_length;I<p_length*PXE3_SUPPORTED_CHAR_COUNT;I+=p_length+1)
            {
                this->m_subKeys[counter] = p_key.substr(0,p_length);
                std::cout << "CRYPTO << " << (int)counter << " << " << this->m_subKeys[counter] << std::endl;
                p_key.erase(0,p_length); 
                counter++;
            }   
            for(char II : p_key)
                this->m_COverflowChars.push_back(II);
            this->m_COverflow = this->m_COverflowChars.size();
            this->m_length = p_length;
        }
        PXE3(){}

        std::string m_subKeys[PXE3_SUPPORTED_CHAR_COUNT];
        int m_COverflow,m_length;
        std::list<char> m_COverflowChars;

        void encrypt(std::string* p_target, std::string* p_msg)
        {
            #ifdef PXE3_DEBUG
                std::cout << px::InfoPrefix() << "encrypt function invoked - 0x" << this << std::endl;
            #endif
            std::string subKeyStr[PXE3_SUPPORTED_CHAR_COUNT];
            int counter = 0;
            for(std::string SK : this->m_subKeys)
            {
                subKeyStr[counter] = SK;
                #ifdef PXE3_DEBUG
                    std::cout << px::InfoPrefix() << subKeyStr[counter] << std::endl;
                #endif
                counter++;
            }
            for(char I : *p_msg)
            {
                if((int)I-PXE3_OFFSET-1 < PXE3_SUPPORTED_CHAR_COUNT)
                    p_target->append(subKeyStr[I-PXE3_OFFSET-1]);
                else
                    std::cout << px::getCustomPrefix("PXE3 ERROR",px::console_colors::_8colors::red) << " encryption failed, index out of bounds" << "err: tried to access array element "<< (int)I-PXE3_OFFSET-1 << " but the array has only 95 (0-94) elements." << std::endl;
            }
        }

        void decrypt(std::string* p_target, std::string* p_cypher)
        {
            #ifdef PXE3_DEBUG
                std::cout << px::InfoPrefix() << "decrypt function invoked - 0x" << this << std::endl;
            #endif
            for(unsigned long long I = 0; I < p_cypher->size(); I+=this->m_length){
                int II = 1;
                for(std::string SK : this->m_subKeys){
                    if(SK == p_cypher->substr(I,this->m_length)){
                        p_target->push_back((char)(II+(PXE3_OFFSET)));
                        std::cout << "[DECRYPT] added " << (int)(II+(PXE3_OFFSET)) << std::endl;
                        break;
                    }
                    else
                    {
                        #ifdef PXE3_DEBUG
                            std::cout <<"[DECRYPT] "<< p_cypher->substr(I,this->m_length) << " =/= " << SK << std::endl;
                        #endif
                        II++;
                    }
                }
            }
        }

        std::string getTable()
        {
            std::cout << "Key - 0x" << this << std::endl;
            int III = PXE3_OFFSET;
            std::list<std::list<std::string>> data;
            std::list<std::string> col1;
            std::list<std::string> col2;
            std::list<std::string> col3;
            col1.push_back("ID");
            col2.push_back("char");
            col3.push_back("key");
            for(std::string I : this->m_subKeys)
            {
                //std::cout << "" << char(III) <<":"<<III<< "|  ";
                std::string dataPoint;
                std::string dataPoint2;
                dataPoint2.push_back(char(III));
                dataPoint = I;
                col3.push_back(dataPoint);
                col2.push_back(dataPoint2);
                col1.push_back(px::intToString(III));
                III++;
            }
            data.push_back(col1);
            data.push_back(col2);
            data.push_back(col3);
            return px::getTable(&data,0);
        }

        void genKey(int p_keyLength)
        {
            this->m_length = p_keyLength;
            for(int CTE = PXE3_OFFSET+1;CTE<PXE3_SUPPORTED_CHAR_COUNT;CTE++)
            {
                std::string SK;
                for(int SCP = 0;SCP<p_keyLength;SCP++)
                {
                    char II = px::math::random<int,int>(32,126,&illegalChars);
                    SK.push_back(II);
                    #ifdef PXE3_DEBUG
                        std::cout << " crypto <== " << II << std::endl;
                    #endif
                }
                this->m_subKeys[CTE] = SK;
            }
            this->m_COverflow = px::math::random<int,int>(PXE3_COVERFLOW_MIN,PXE3_COVERFLOW_MAX);
            for(int I = 0;I<this->m_COverflow;I++)
            {
                char II = px::math::random<int,int>(32,126,&illegalChars);
                #ifdef PXE3_DEBUG
                    std::cout << " crypto_overflow <== " << II << std::endl;
                #endif
                this->m_COverflowChars.push_back(II);
            }

            #ifndef PXE3_GENKEY_NT
                //FIXME: PXE3 GENKEY TEST
                std::string cypherMSG = "";
                std::string msg = "";
                std::string msg2 = "";
                for(int CTE = PXE3_OFFSET+1;CTE<PXE3_SUPPORTED_CHAR_COUNT;CTE++)
                    msg.push_back(CTE);
                this->encrypt(&cypherMSG,&msg);
                this->decrypt(&msg2,&cypherMSG);
                if(msg2 != msg)
                {
                    px::sysError("[PXE3] The generated key is invalid, generating new key!");
                    std::cout << px::ErrorPrefix() << msg << std::endl;
                    std::cout << px::ErrorPrefix() << msg2 << std::endl;
                    exit(-1);
                    this->genKey(p_keyLength); // invalid key, generate new key (the odds of this ever happening are astronomically small but just in case)
                }
            #endif
        }

        std::string getKey()
        {
            std::string ret;
            ret+=px::math::int_to_hex<int>(this->m_length);
            ret+=";";
            for(std::string I : this->m_subKeys)
                ret.append(I);
            for(char I : this->m_COverflowChars)
                ret.push_back(I);
            return ret;
        }
    };
}

//* L = Subkey length
//* possibilities
//* 96 possible chars
//* 128 chars
//* formula: n!/(r!(n-r)!)

//? possibilities for each subkey
//? n = 96
//? r = L
//? 96!/(L!(96-L)!)
//? 96!/L!((96-L)!)
//? if we set L to 10 we get...
//? 40.932.597.125.913.292.800 (20 decimal digits)
//? or 4.09325971259132928 × 10^19
//? or 40 quintillion ...
//? or 2^12×3^5×5^2×7×11×13×19×23×29×31×47×89
//? or 100011100000001101110011000011011101000000001111001011000000000000_2
//? for reference "100011100000001101110011000011011101000000001111001011000000000000_2"
//? would be a 66 bit integer to represent this, one would use a 128 bit integer, for reference,
//? the largest integer type supported by c++ is Long Long as a 64 bit integer 
//? https://www.wolframalpha.com/input/?i=40932597125913292800)

//! now lets move on to the possibilities for the entire Key
//! (for the sake of simplicity i cut n from 4.09325971259132928×10^19 to 4.093×10^19)
//! n = 4.093×10^19
//! r = 128
//! (4.093×10^19)!/(128!×(4.093×10^19 - 128)!)
//! https://www.wolframalpha.com/input/?i=%284.093%C3%9710%5E19%29%21%2F%28128%21%C3%97%284.093%C3%9710%5E19+-+128%29%21%29
//! as you can see in the above link, wolframalpha just says undefined

//~ final words
//~ ...while in theory you could go ahead and bruteforce the shit out of the Key, 
//~ it would not be finished by the time your great grandchildren die.
//~ lets just say the possibilities for the entire Key would be in the same ratio to n×r
//~ as with the possibilities for each subkey in which case the ratio would be ~42 quadrillion [1] to 1
//~ the possibilities would come out at 5 sextillion [2] possibilities. (which is probably a HUGE underestimation but well, i can't check)
//~ lets be optimistic and say you can try 10 Million keys a second, you would still need 
//~ ~524 trillion seconds, [3]
//~ or ~8.731.733.333.333 minutes
//~ or ~145.528.888.888 Hours
//~ or ~6.063.703.703 Days
//~ or ~866.243.386 Weeks
//~ or ~16.601.515 Years
//~ just for reference, Dinosaurs have gone extinct about 65 Million years ago.
//~ so the time you would have to spend to go through all possible combinations
//~ would be relevant on a geological and maybe even astronomical level.
//~ and again please keep in mind that the number of possibilities i assumed here is probably not even close.

//- And just to get this out of the way, just increasing the length L of each subkey from 10 to lets say 20
//- would raise the number of possibilities for each subkey by 1.2335 septillion percent [6]
//- from 40 quintillion [1] to 525 undecillion [5].
//- since 525 undecillion would be a 129 bit Integer
//- binary: 110001011101011100111110101000110101011001011010010100110110000001011000110100101110110100010010110000000011000000000000000000000
//- but a 129 bit Integer would be total nonsense and harmful to my mental health, 
//- one would use a 256 bit integer which is literally 4 times the size of the largest Integer type supported by c++
//- I'm just gonna leave any further calculations to you.



//references
//[1]        42.638.122.006.159.680
//[2] 5.239.040.000.000.000.000.000
//[3]           523.904.000.000.000 (https://www.wolframalpha.com/input/?i=5239040000000000000000+%2F+10000000)
//[4]             8.731.733.333.333 (windows calculator)
//[5] 525.951.058.889.048.478.065.888.601.082.429.440.000 (https://www.calculatorsoup.com/calculators/discretemathematics/permutations.php)
//[6] 1.233.520.000.000.000.000.000.000% https://www.calculatorsoup.com/calculators/algebra/percentage-increase-calculator.php

//formula: https://sciencing.com/calculate-number-combinations-5142125.html
//calculations: https://www.wolframalpha.com/