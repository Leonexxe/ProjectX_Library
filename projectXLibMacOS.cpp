//
//  projectXLibMacOS.cpp
//  projectXLibMacOS
//
//  Created by Leonexxe on 22.02.22.
//

#include <iostream>
#include "projectXLibMacOS.hpp"
#include "projectXLibMacOSPriv.hpp"

#include "pxe.h"

int main()
{
	px::pxe4 pxe;
	pxe.generateKey(10);
	std::cout << "cypher: " << pxe.encrypt("das pferd frisst keinen kartoffelsalat") << std::endl;
}
