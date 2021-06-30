#pragma once
#include <list>
#include "../common.h"

namespace px
{
    namespace misc
    {
        std::list<char> getASCIIchars()
        {
            std::list<char> res;
            for(auto I : px::range<_int8>(px::ranges::min::CHAR,px::ranges::max::CHAR))
            {
                res.push_back(I);
            }
            return res;
        }
    }
}