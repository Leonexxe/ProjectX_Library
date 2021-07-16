#pragma once
#include <list>
#include <string>
#include <iostream>
#include "../tools/lists.cpp"
#include <projectX/tools/textmanipulation.cpp>
#include <PXC>

namespace px
{
    void printTable(std::list<std::list<std::string>>* data)
    {
        if(!testForPrintTable(data))
        {
            px::sysError("INVALID DATA!");
            return;
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
            if(I == 0){for(int II : maxsizes){for(auto III : px::range(II)){std::cout << "-";}std::cout << "-";}std::cout <<"-"<< std::endl;}
            for(int II : px::range(px::tools::lists::getSize(data)-1))
            {
                std::list<std::string> items;
                items = px::tools::lists::getElementByIndex(data, II);
                std::cout << "|" << px::text::manipulation::fill(
                    &px::tools::lists::getElementByIndex(&items, I),
                    px::tools::lists::getElementByIndex(&maxsizes, II), ' ');
            }
            std::cout <<"|"<< std::endl;
            if(I == 0){for(int II : maxsizes){for(auto III : px::range(II)){std::cout << "-";}std::cout << "-";}std::cout <<"-"<< std::endl;}
        }
        for(int II : maxsizes){for(auto III : px::range(II)){std::cout << "-";}std::cout << "-";}std::cout <<"-"<< std::endl;
    }
    
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
}
