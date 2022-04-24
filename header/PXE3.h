// 
// PXE3.h 
// projectXLibMacOS 
// Created by Leonexxe on 23.02.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef PXE4_h
#define PXE4_h

#include "predef.h"
#include "../math.h"

#ifndef PXE4_SKS_UL
	#define PXE4_SKS_UL 64
#endif

namespace px
{
	class pxe4
	{
	public:
		pxe4();
		pxe4(__string__ key, __uint__ overflow, __uint__ subKeySize);
		
		__string__ encrypt(__string__ msg);
		__string__ decrypt(__string__ cypher);
		__uint__ generateKey(__uint__ subKeySize);
		__string__ getKey();
		
	#ifndef PX_PTP_PXE4
		private:
	#endif
		__string__ Key[256];// this was orginally supposed to be a 2 dimensional char array but i actually decided to use a string array instead because i think that for the average use case this is gonna be more efficient
		__string__ addition;
		__int__ subKeyLen = 0;
		__int__ additionLen = 0;
	};
}

#endif /* PXE4_h */
