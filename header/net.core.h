// 
// net.core.h 
// projectXLibMacOS 
// Created by Leonexxe on 05.03.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include "predef.h"

#ifndef net_core_h
#define net_core_h

namespace px
{
	struct netErrorInfo
	{
		//net activity
		//send: 0
		//recv: 1
		bool activity = 0;
		int size = 0;
		
		//client info
		__string__ IP;
		__int__ port;
		netErrorInfo();
		netErrorInfo(__int__ port, __string__ IP);
	};
	
	struct IPv4
	{
		__ushort__ block0,block1,block2,block3;
		IPv4();
		IPv4(__string__ IP);
		IPv4(__ushort__ block0,__ushort__ block1,__ushort__ block2,__ushort__ block3);
	};
	
	struct netClientInfo
	{
		__string__ connectTime;
		__string__ IPS;
		IPv4 IP;
		__int__ socket;
		
		netClientInfo();
		netClientInfo(__string__ CT,IPv4 IP);
	};
}

#endif /* net_core_h */
