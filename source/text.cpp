// 
// text.cpp 
// projectXLibMacOS 
// Created by Leonexxe on 26.04.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include <stdio.h>

namespace px
{
	std::vector<std::string> strSplit(std::string s, std::string delimiter)
	{
		std::vector<std::string> res;
		/*
		 * code taken from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
		 * Vincenzo Pii
		 */
		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
#ifdef PX_DEBUG
			std::cout << token << std::endl;
#endif
			res.push_back(token);
			s.erase(0, pos + delimiter.length());
		}
		res.push_back(s);
#ifdef PX_DEBUG
		std::cout << s << std::endl;
#endif
		return res;
	}
}
