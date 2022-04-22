// 
// gui.cpp 
// projectXLibMacOS 
// Created by Leonexxe on 14.03.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include <stdio.h>

#include "../header/gui.h"
//
// Bounds Class Implementation
//
//default constructor, init to 0
namespace px::gui
{
	Bounds::Bounds()
		:x(0),y(0),width(0),height(0){}
	
	Bounds::Bounds(__int__ x, __int__ y, __int__ width, __int__ height)
		:x(x),y(y),width(width),height(height){}
}
