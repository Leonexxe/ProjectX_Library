#pragma once
#include <string>
#include <list>
#include <sstream>
#include "textmanipulation.cpp"
#include <iostream>
#ifdef PX_BOOST
#include <boost/algorithm/string/replace.hpp>
/**
 * @brief replaces every occurrence of a substring in a string with another string (uses boost/algorithm/string/replace.hpp)
 * 
 * @param mainstring
 * @param target 
 * @param replacement 
 * @return std::string 
 */
static std::string strReplace(std::string mainstring, std::string target, std::string replacement)
{
    std::string ret = mainstring;
    boost::replace_all(ret, target, replacement);
    return ret;
}
#else 
/**
 * @brief this does not work without boost, just returns mainstring
 * 
 * @param mainstring 
 * @param target 
 * @param replacement 
 * @return std::string 
 */
static std::string strReplace(std::string mainstring, std::string target, std::string replacement){return mainstring;}
#endif
/**
 * @brief splits a string using a delimiter, the delimiter isn't included in the results
 * 
 * @param String 
 * @param delimiter 
 * @return std::list<std::string> 
 */
std::list<std::string> strSplit(std::string s, std::string delimiter)
{
    std::list<std::string> res;
    /*
    * code taken from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c 
    * Vincenzo Pii
    */
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        #ifdef PX_DEBUG
            std::cout << token << std::endl;
        #endif
        res.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    res.push_back(s);
    #ifdef PX_DEBUG
        std::cout << s << std::endl;
    #endif
    return res;
}
//* old split algorithm
//std::list<std::string> strSplit(std::string String, std::string delimiter)
//{
//    std::list<std::string> segments;
//    int offset = 0;
//    int lastpos = 0;
//    std::list<int> positions;
//    while(1)
//    {
//        int pos = String.find_first_of(delimiter, offset);
//        if(pos > -1)
//        {
//            offset += delimiter.length();
//            if(lastpos == 0){positions.push_back(pos);}
//            else if(lastpos != pos){positions.push_back(pos);}
//            lastpos = pos;
//            #ifdef PX_DEBUG
//                std::cout << "found segment at " << pos << "!" << std::endl;
//            #endif
//        }else{break;}
//    }
//    int Lastpos = 0;
//    int round = 0;
//    for (int i : positions){
//        if(++round == 1){}else
//        {
//            int len = i-(Lastpos+1);
//            #ifdef PX_DEBUG
//                std::cout << "adding " << lastpos+1 << ":" <<  lastpos+1+len 
//                    << " - " << String.substr(Lastpos+1, len) << "to segments" << std::endl;
//            #endif
//            segments.push_back(String.substr(Lastpos+1, len));
//        }
//        Lastpos = i;
//    }
//    return segments;
//}
//! char array to string
/**
 * @brief does what the name says
 * 
 * @param array 
 * @return std::string 
 */
template<size_t S>
static std::string charArrayToString(int start, int end, char (*array)[S])
{
    std::string ret = "";
    for(int i = start;i<=end;i++)
    {
        ret+=*array[i];
        std::cout << i << " : " << *array[i] << " => " << ret << std::endl;
    }
    return ret;
}

namespace px
{
    std::string strToUpper(std::string str)
    {
        std::string res;
        for (auto & c: str)
        {
            c = toupper(c);
            res+=c;
        }
        return res;
    }

    bool strContains(std::string* pool,std::string target)
    {
        if (pool->find(target) != std::string::npos) {
            return 1;
        }
        return 0;
    }

    bool strEndsWith(std::string* str, std::string target)
    {
        std::string reverse = px::text::manipulation::reverse(str);
        std::string r_target = px::text::manipulation::reverse(&target);
        const char* PCR = reverse.c_str();
        const char* TCR = r_target.c_str();
        for(int I = 0;I<r_target.size();I++)
        {
            if(PCR[I] != TCR[I])
            {
                return 0;
            }
        }
        return 1;
    }

    bool strEndsWithNewLine(std::string* str,bool addIfNot = 0)
    {
        if(str->back() != 0)
        {
            if(addIfNot)
            {
                *str+="\n";
                return 0;
            }
        }
        return 1;
    }

    const char* strToConstChar(std::string* str)
    {
        const char* CC;
        CC = str->c_str();
        return CC;
    }

    template<typename t>
    std::string pointerToString(t* address)
    {
        std::stringstream ss;
        ss << address;
        return ss.str();
    }
}