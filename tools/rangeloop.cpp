#pragma once
#include <list>

namespace px
{
    template<typename type>
    std::list<type> range(type min, type max)
    {
        std::list<type> r;
        for(int i = min;i <= max;i++){r.push_back(i);}
        return r;
    }
    template<typename type>
    std::list<type> range(int max){return range<type>(0,max);}
    std::list<int> range(int max){return range<int>(0,max);}
}