// 
// net.server.cpp 
// projectXLibMacOS 
// Created by Leonexxe on 05.03.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include <stdio.h>
#include "../header/net.server.cpp"
namespace px::net::server
{
	__int__ disconnectClient(IPv4 IP, __string__ msg)
	{
		__int__ result;
		for(netClientInfo I : this->clients)
			if(I.IP == IP)
				result+=this->NETdisconnectClient(I.socket,msg);
		return result;
	}
	
	__int__ disconnectAll(__string__ msg)
	{
		__int__ err;
		for(netClientInfo I : this->clients)
			err += this->NETdisconnectClient(I.socket,msg);
		return err;
	}
}
