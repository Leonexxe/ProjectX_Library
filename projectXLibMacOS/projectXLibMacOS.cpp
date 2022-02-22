//
//  projectXLibMacOS.cpp
//  projectXLibMacOS
//
//  Created by Leonexxe on 22.02.22.
//

#include <iostream>
#include "projectXLibMacOS.hpp"
#include "projectXLibMacOSPriv.hpp"

void projectXLibMacOS::HelloWorld(const char * s)
{
    projectXLibMacOSPriv *theObj = new projectXLibMacOSPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void projectXLibMacOSPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

