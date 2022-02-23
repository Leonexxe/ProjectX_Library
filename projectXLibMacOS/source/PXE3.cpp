// 
// PXE3.cpp 
// projectXLibMacOS 
// Created by Leonexxe on 23.02.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include <stdio.h>

#include "../header/PXE3.h"

namespace px
{
	pxe4::pxe4(){}
	
	pxe4::pxe4(__string__ key, __uint__ overflow, __uint__ subKeySize)
	{
		this->subKeyLen = subKeySize;
	}
	
	__string__ pxe4::encrypt(__string__ msg)
	{
		__string__ result = "";
		for(unsigned char I : msg)
			result+=__string__(this->Key[I]);
		return result;
	}
	
	__string__ pxe4::decrypt(__string__ cypher)
	{
		return "";
	}
	
	__uint__ pxe4::generateKey(__uint__ subKeySize)
	{
		for(__short__ I = 0;I<255;I++)
			for(__short__ II = 0;II<subKeySize;II++)
				this->Key[I][II] = px::random(32,126);
		
		__int__ additionLen = random(1,100);
		for(__short__ III = 0;III<additionLen;III++)
			this->addition.push_back(px::random(32,126));
		return 0;
	}
}
