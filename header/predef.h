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

//
// constants
//
#ifndef PX_CONSTANTS_MATH_PI
	#define PX_CONSTANTS_MATH_PI 3.1415
#endif
#ifndef PX_CONSTANTS_MATH_PYTHAGORAS
	#define PX_CONSTANTS_MATH_PYTHAGORAS 1.41421
#endif
#ifndef PX_CONSTANTS_MATH_THEODORUS
	#define PX_CONSTANTS_MATH_THEODORUS 1.73205
#endif
#ifndef PX_CONSTANTS_MATH_DELIAN
	#define PX_CONSTANTS_MATH_DELIAN 1.25992
#endif
#ifndef PX_CONSTANTS_MATH_EULERS
	#define PX_CONSTANTS_MATH_EULERS 2.71828
#endif
#ifndef PX_CONSTANTS_MATH_OMEGA
	#define PX_CONSTANTS_MATH_OMEGA 0.56714
#endif

#ifndef PX_CONSTANTS_PHYSICS_G
	#define PX_CONSTANTS_PHYSICS_G 9.81
#endif
#ifndef PX_CONSTANTS_PHYSICS_speedOfLight
	#define PX_CONSTANTS_PHYSICS_speedOfLight 299792458
#endif
#ifndef PX_CONSTANTS_PHYSICS_FARADAY
	#define PX_CONSTANTS_PHYSICS_FARADAY 96485.33289
#endif

#endif /* predef_h */
