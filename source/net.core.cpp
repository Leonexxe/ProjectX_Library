// 
// net.core.cpp 
// projectXLibMacOS 
// Created by Leonexxe on 05.03.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include <stdio.h>

namespace px
{
	netErrorInfo::netErrorInfo(){}
	netErrorInfo::netErrorInfo(__int__ port, __string__ IP)
		:port(port),IP(IP){}
	
	IPv4::IPv4();
	IPv4::IPv4(__string__ IP)
	{
		__ushort__ counter = 0;
		__string__ block = "";
		for(char I : IP)
			if(I == '.')
			{
				counter++;
				switch(counter)
				{
					case(1):
						this->block0 = block;
						break;
					case(2):
						this->block1 = block;
						break;
					case(3):
						this->block2 = block;
						break;
					case(4):
						this->block3 = block;
						break;
				}
				block = "";
			}
			else
				block.push_back(I);
	}
	
	IPv4::IPv4(__ushort__ block0,__ushort__ block1,__ushort__ block2, __ushort__ block3)
		:block0(block0),block1(block1),block2(block2),block3(block3){}
}
