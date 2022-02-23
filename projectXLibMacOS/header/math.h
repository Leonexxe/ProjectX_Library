// 
// math.h 
// projectXLibMacOS 
// Created by Leonexxe on 23.02.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef math_h
#define math_h

#include "predef.h"
#include <cmath>

namespace px
{
	namespace math
	{
		const __double__ PI = 3.1415; // PI constant
		const __double__ PythagorasConstant = 1.41421; //Pythagoras constant
		const __double__ TheodorusConstant = 1.73205; //Theodorus' Constant
		const __double__ DelianConstant = 1.25992; //Delian constant = cube root of 2 ==> 3√2
		const __double__ EulersNumber = 2.71828;
		const __double__ OmegaConstant = 0.56714;
		
		//might add more if happen to be bored at some point
		//see https://en.wikipedia.org/wiki/List_of_mathematical_constants for a list of mathematical constants
	}
	namespace physics
	{
		const __double__ G = 9.81; // 1G (accelaration due to gravitiy on earth = 9.81m/s^2)
		const __long__ speedOfLigth = 299792458; // 299792458 m/s ==> speed of light in a vacuum
		const __double__ FaradayConstant = 96485.33289; //Faraday constant F ==> coulombs per mole
	}
	
	__double__ getMissingValueTriangle(
			//sides
			__int__ sideA,
			__int__ sideB,
			__int__ sideC,
			//angles
			__int__ alpha,
			__int__ beta,
			__int__ gamma,
			//heights
			__int__ hA,
			__int__ hB,
			__int__ hC);
	
	__int__ random(__int__ min, __int__ max);
}



#endif /* math_h */
