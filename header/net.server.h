// 
// net.server.h 
// projectXLibMacOS 
// Created by Leonexxe on 05.03.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include "predef.h"
#include "net.core.h"

#ifndef net_server_h
#define net_server_h

namespace px::net
{
	class server
	{
	#ifndef PX_PTP_NET_SERVER
		private:
	#else
		public:
	#endif
		std::list<__string__> blockedIPs;
		std::list<netClientInfo> clients;
		void NETsend(__string__ msg);
		__string__ NETrecv();
		__int__ NETopenSocket(__int__ port);
		__int__ NETdisconnectClient(IPv4 IP,__string__ msg);
		__int__ NETdisconnectClient(__int__ socket,__string__ msg);
	
	public:
		server();
		server(__int__ port,
			   __string__(*response)(__string__ clientIP,__string__ msg)
			   __string__ accessDeniedResponse = "");
		
		void send(__string__ msg);
		__string__ recv();
		
		__int__ disconnectClient(IPv4 IP,__string__ msg);
		__int__ disconnectAll(__string__ msg);
		
		__int__ openSocket(__int__ port);
	};
}

//
//get implementation
//
#if PX_CONFIG_OS == 0
	//macOS is a unix system, therefore we just pull the unix implementation (might be changed later on)
	#include "../source/net.server.UNIX.cpp"
#else if PX_CONFIG_OS == 2
	#include "../source/net.server.WIN32.cpp"
#else
	#error projectX/net.server.h ==> OS not supported
#endif

#endif /* net_server_h */
