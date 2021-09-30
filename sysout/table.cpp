#pragma once
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include "../tools/lists.cpp"
#include <projectX/tools/textmanipulation.cpp>
#include <projectX/common.h>

namespace px
{
    bool testForPrintTable(std::list<std::list<std::string>>* list)
    {
        int size = 0;
        for(std::list<std::string> I : *list)
        {
            if(I.size() == size && size != 0)
                size = I.size();
            else
                return 0;
        }
    }
    std::string getTable(std::list<std::list<std::string>>* data, bool testData)
    {
        std::stringstream ss;
        if(!testForPrintTable(data) && testData)
        {
            px::sysError("INVALID DATA!");
            return std::string("");
        }
        std::list<int> maxsizes;
        int maxrows = 0;
        for(std::list<std::string> I : *data)
        {
            int maxsize = 0;
            int locmaxrows = 0;
            for(std::string II : I)
            {
                int innermaxsize = 0;
                for(char III : II)
                {
                    innermaxsize++;
                }
                px::math::useHighest<int>(&maxsize, &innermaxsize);
                locmaxrows++;
            }
            maxsizes.push_back(maxsize);
            px::math::useHighest<int>(&maxrows, &locmaxrows);
        }
        for(int I : px::range(maxrows-1))
        {
            if(I == 0){for(int II : maxsizes){for(auto III : px::range(II)){std::cout << "-";}std::cout << "-";}std::cout <<"-"<< "\n";}
            for(int II : px::range(px::tools::lists::getSize(data)-1))
            {
                std::list<std::string> items;
                items = px::tools::lists::getElementByIndex(data, II);
                #ifdef _MSC_VER
                    std::string s = px::tools::lists::getElementByIndex(&items, I);
                #endif
                std::cout << "|" << px::text::manipulation::fill(
                    #ifdef _MSC_VER
                        &s,
                    #else
                        &px::tools::lists::getElementByIndex(&items, I),
                    #endif
                    px::tools::lists::getElementByIndex(&maxsizes, II), ' ');
            }
            ss <<"|"<< "\n";
            if(I == 0){for(int II : maxsizes){for(auto III : px::range(II)){ss << "-";}ss << "-";}ss <<"-"<< "\n";}
        }
        for(int II : maxsizes){for(auto III : px::range(II)){ss << "-";}ss << "-";}ss <<"-"<< "\n";
        return ss.str();
    }
    void printTable(std::list<std::list<std::string>>* data, bool testData=1)
    {
        std::cout << getTable(data,testData);
    }
}
