#pragma once
#include <string>
#include <list>
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
static std::list<std::string> split(std::string String, std::string delimiter)
{
    std::list<std::string> segments;
    int offset = 0;
    int lastpos = 0;
    std::list<int> positions;
    while(1)
    {
        int pos = String.find_first_of(delimiter, offset);
        if(pos > -1)
        {
            offset += delimiter.length();
            if(lastpos == 0){positions.push_back(pos);}
            else if(lastpos != pos){positions.push_back(pos);}
            lastpos = pos;
        }else{break;}
    }
    int Lastpos = 0;
    int round = 0;
    for (int i : positions){
        if(++round == 1){}else
        {
            int len = i-(Lastpos+1);
            segments.push_back(String.substr(Lastpos+1, len));
        }
        Lastpos = i;
    }
    return segments;
}
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