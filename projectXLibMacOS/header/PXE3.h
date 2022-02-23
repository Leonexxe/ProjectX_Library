// 
// PXE3.h 
// projectXLibMacOS 
// Created by Leonexxe on 23.02.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include "predef.h"
#include "math.h"

#ifndef PXE4_h
#define PXE4_h

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
		
	#ifndef PX_PTP_PXE4
		private:
	#endif
		char Key[256][PXE4_SKS_UL];//this shit is fucking stupid, because of the absence of VLA's i litterally need to allocate 131072 (256x64x8) bytes of memory for no fucking reason at all whatsoever
		__string__ addition;
		__int__ subKeyLen = 0;
	};
}

#endif /* PXE4_h */
