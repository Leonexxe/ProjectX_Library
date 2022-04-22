// 
// base.h 
// projectXLibMacOS 
// Created by Leonexxe on 23.02.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include "predef.h"

#ifndef base_h
#define base_h

namespace px::base
{
    struct threadInfo
    {
        __string__ name;
        __uint__ ID;
        threadInfo(__string__ name, __uint__ ID);
    };
}

#endif /* base_h */
