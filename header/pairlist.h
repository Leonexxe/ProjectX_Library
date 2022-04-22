// 
// pairlist.h 
// projectXLibMacOS 
// Created by Leonexxe on 21.04.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef pairlist_h
#define pairlist_h

#include "predef.h"
#include <list>

namespace px
{
	template<typename typeA,typename typeB>
	class pairList
	{
	#ifndef PX_PTP_PAIRLIST
		private:
	#else
		public:
	#endif
		
		
	public:
		pairList();
		pairList(std::list<typeA> listA,std::list<typeB> listB);
		
		pair<typeA,typeB> getPair(__ulong__ index);
	};
	
	template<typename typeA,typename typeB>
	class pair
	{
		typeA objA;
		typeB objB;
	public:
		pair();
		pair(typeA objA,typeB objB);
	};
}

#endif /* pairlist_h */
