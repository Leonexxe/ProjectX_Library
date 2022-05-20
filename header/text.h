// 
// text.h 
// projectXLibMacOS 
// Created by Leonexxe on 26.04.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef text_h
#define text_h

#include <vector>
#inclue "predef.h"

namespace px
{
	/**
	 * @brief splits a string using a delimiter, the delimiter isn't included in the results
	 *
	 * @param String
	 * @param delimiter
	 * @return std::list<std::string>
	 */
	std::vector<__string__> strSplit(__string__ s, __string__ delimiter);
	
	__string__ strReplace(__string__ s, __string__ tbr, __string__ replacement);
	__string__ strReplace(__string__ s, char c, char replacement);
}

#endif /* text_h */
