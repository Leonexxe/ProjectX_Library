// 
// filesys.cpp 
// projectXLibMacOS 
// Created by Leonexxe on 23.02.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include <stdio.h>

#include "../header/filesys.h"

namespace px
{
	
	//
	//filesys class
	//
	filesys::filesys(){};
	
	filesys::filesys(__string__ root)
		:root(root)
	{
	}
	
	//cryptography
	bool filesys::enablePXE4FilesystemEncryption()
	{
		this->encryption = 1;
		return 1;
	}
	
	void filesys::setPXE4Key(pxe4 pxe)
	{
		this->pxe = pxe;
	}
	
	__uint__ filesys::generatePXE4Key(__uint__ subKeySize)
	{
		return this->pxe.generateKey(subKeySize);
	}
	
	//read
	__string__ filesys::readFile(__string__ fname)
	{
		if(!this->exists(fname))
			return fsERROR;
		__string__ fcont = getFileContent(this->root + fname);
		if(fcont == fsERROR)
			return fsERROR;//something went wrong (file doesen't exist, etc.)
		if(this->encryption)
			return this->pxe.decrypt(fcont);//decrypt and return
		else
			return fcont;//encryption disabled
	}
	
	//writes
	
	
	//misc
}
