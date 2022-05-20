// 
// config.h 
// projectXLibMacOS 
// Created by Leonexxe on 20.05.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef config_h
#define config_h

#include "predef.h"
namespace px
{
	class config
	{
	#ifndef PX_PTP_CONFIG
		private:
	#else
		public:
	#endif
		
	public:
		config();
		config(__string__ file);
		~config();
		
		template<typename T>
		T get(__string__ name);
		
		__string__ get(__string__ name);

		void erase(__string__ name);
		
		void load(__string__ name);
		
		template<typename T>
		void write(T value);
	};
}

#endif /* config_h */
