//
//  predef.h
//  projectXLibMacOS
//
//  Created by Leonexxe on 22.02.22.
//

#ifndef predef_h
#define predef_h

#include <string>
#include <list>

namespace px
{
    //global big int type
    #ifndef PX_LONG
        #define PX_LONG long long
    #endif
    typedef PX_LONG __long__;
    typedef unsigned PX_LONG __ulong__;

    //globl int type
    #ifndef PX_INT
        #define PX_INT int
    #endif
    typedef PX_INT __int__;
    typedef unsigned PX_INT __uint__;

    //global small int type
    #ifndef PX_INT_SMALL
        #define PX_INT_SMALL char
    #endif
    typedef PX_INT_SMALL __short__;
    typedef unsigned PX_INT_SMALL __ushort__;

    //global string type
    #ifndef PX_STRING
        #define PX_STRING std::string
    #endif
    typedef PX_STRING __string__;
	
	//global float type
	#ifndef PX_FLOAT
		#define PX_FLOAT float
	#endif
	typedef PX_FLOAT __float__;
	
	//global double type
	#ifndef PX_DOUBLE
		#define PX_DOUBLE double
	#endif
	typedef PX_DOUBLE __double__;

    //common data types
    typedef __ushort__ batteryLevel;
	
	//empty function
	void none();
	
	//
	//enums
	//
	enum ImageFormat
	{
		JPG,PNG,HEIC,PDF,SVG,ICO
	};
	enum VideoFormat
	{
		mp4,MOV
	};
	enum programmingLanguage
	{
		C,CPP,ASMx86,JAVA,JAVASCRIPT,PHP,PYTHON,GO,RUST,CSS,HTML,SWIFT,ASM_ARM
	};
	enum DataFormat
	{
		JSON,XML
	};
	enum formatMisc
	{
		txt,docx,rtf,csv,xlsx,pptx
	};
}

#endif /* predef_h */
