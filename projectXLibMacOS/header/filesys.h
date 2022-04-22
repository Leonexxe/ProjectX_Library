// 
// filesys.h 
// projectXLibMacOS 
// Created by Leonexxe on 23.02.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include "predef.h"
#include "../pxe.h"

#ifndef filesys_h
#define filesys_h

namespace px
{
	__string__ getFileContent(__string__ fname);
	std::list<__string__> getFilesInFolder(__string__ fname);
	
	__string__ fsERROR = {0x0};
	
	class filesys
	{
	public:
		filesys();
		filesys(__string__ root);
		
		//misc
		bool exists(__string__ fname);
		
		//cryptography
		bool enablePXE4FilesystemEncryption();
		void setPXE4Key(pxe4 pxe);
		__uint__ generatePXE4Key(__uint__ subKeySize);
		
		//read
		__string__ readFile(__string__ fname);
		
		//write
		__uint__ writeFile(__string__ fname, __string__ content);
		__uint__ append(__string__ fname, __string__ content);
		
	#ifndef PX_PTP_FSYS
		private:
	#endif
		__string__ root;
		pxe4 pxe;
		bool encryption = 0;
		std::list<__string__> fileIndex;
	};
}

#endif /* filesys_h */
