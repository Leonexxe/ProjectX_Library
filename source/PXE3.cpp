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
	#ifdef PX_DEBUG
		std::cout << "(pxe4) encrypting..." << std::endl;
	#endif
		__string__ result = "";
		for(unsigned char I : msg)
			result+=__string__(this->Key[I]);
		return result;
	}
	
	__string__ pxe4::decrypt(__string__ cypher)
	{
	#ifdef PX_DEBUG
		std::cout << "(pxe4) decrypting..." << std::endl;
	#endif
		__string__ result;
		for(__long__ I = 0;I<cypher.size();I+=this->subKeyLen)
		{
			__string__ subCypherStr;
			for(__long__ II = 0;II<this->subKeyLen;II++)
				subCypherStr.push_back(cypher[I+II]);
			for(__long__ II = 0;II<256;II++)
				if(this->Key[II] == subCypherStr)
					result.push_back(II);
		}
		return result;
	}
	
	__string__ pxe4::getKey()
	{
		__string__ result;
		for(__long__ I = 0;I<256;I++)
			result+=this->Key[I];
		return result;
	}
	
	__uint__ pxe4::generateKey(__uint__ subKeySize)
	{
	#ifdef PX_DEBUG
		std::cout << "(pxe4) generating key..." << std::endl;
	#endif
		this->subKeyLen = subKeySize;
		//this function is actually kinda slow because i decided to use a string array for the key instead of a 2 dimensional char array
		for(__int__ I = 0;I<255;I++)
			for(__short__ II = 0;II<subKeySize;II++)
				this->Key[I].push_back(px::random<__int__,__int__>(32,126));
		
		this->additionLen = random<__int__,__int__>(1,100);
		for(__int__ III = 0;III<this->additionLen;III++)
			this->addition.push_back(px::random<__int__,__int__>(32,126));
		return 0;
	}
}
