// 
// text.h 
// projectXLibMacOS 
// Created by Leonexxe on 26.04.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef text_h
#define text_h

#include <vector>ç

namespace px
{
	/**
	 * @brief splits a string using a delimiter, the delimiter isn't included in the results
	 *
	 * @param String
	 * @param delimiter
	 * @return std::list<std::string>
	 */
	std::vector<std::string> strSplit(std::string s, std::string delimiter);
}

#endif /* text_h */
