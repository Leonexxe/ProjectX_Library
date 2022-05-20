// 
// math.h 
// projectXLibMacOS 
// Created by Leonexxe on 23.02.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include "predef.h"
#include <cmath>
#include <vector>

#ifndef math_h
#define math_h

namespace px
{
	namespace math
	{
		const __double__ PI = PX_CONSTANTS_MATH_PI; // PI constant
		const __double__ PythagorasConstant = PX_CONSTANTS_MATH_PYTHAGORAS; //Pythagoras constant
		const __double__ TheodorusConstant = PX_CONSTANTS_MATH_THEODORUS; //Theodorus' Constant
		const __double__ DelianConstant = PX_CONSTANTS_MATH_DELIAN; //Delian constant = cube root of 2 ==> 3√2
		const __double__ EulersNumber = PX_CONSTANTS_MATH_EULERS;
		const __double__ OmegaConstant = PX_CONSTANTS_MATH_OMEGA;
		
		//might add more if happen to be bored at some point
		//see https://en.wikipedia.org/wiki/List_of_mathematical_constants for a list of mathematical constants
	}
	namespace physics
	{
		const __double__ G = PX_CONSTANTS_PHYSICS_G; // 1G (accelaration due to gravitiy on earth = 9.81m/s^2)
		const __long__ speedOfLigth = PX_CONSTANTS_PHYSICS_speedOfLight; // 299792458 m/s ==> speed of light in a vacuum
		const __double__ FaradayConstant = PX_CONSTANTS_PHYSICS_FARADAY; //Faraday constant F ==> coulombs per mole
	}
	
	template<typename returnType>
	returnType random();
	
	template<typename inputType,typename returnType>
	returnType random(inputType min, inputType max,std::list<inputType>* exclude = nullptr);
	
	template<int vSize, typename dataType>
	class vector
	{
	#ifndef PX_PTP_VECTOR
		private:
	#else
		public:
	#endif
		std::vector<dataType> data;
		
	public:
		
		vector();
		vector(std::vector<dataType> data);
		dataType get(__int__ index);
		void set(__int__ index,dataType value);
	};
	typedef vector<2,__int__> point2D;
	typedef vector<3,__int__> point3D;
	
	template<typename vectorType>
	vector<2,vectorType> rotate2D(__double__ alpha,
		vector<2,vectorType> pointA,
		vector<2,vectorType> pointO);
	
	/**
	 * @brief returns the distance between 2 points in an n-dimensional space
	 */
	template<typename vectorType, int vSize>
	__double__ distance(
			vector<vSize,vectorType> vA,
			vector<vSize,vectorType> vB);
	
	/**
	 * @brief returns the angle between 2 vectors
	 */
	template<typename vectorType>
	__double__ angleBV(vector<2,vectorType> A,vector<2,vectorType>);
	
	/**
	 * @brief stores information on a range of numbers
	 */
	template<typename numType>
	class range
	{
	#ifndef PX_PTP_RANGE
		private:
	#else
		public:
	#endif
		numType min;
		numType max;
		
	public:
		range();
		range(numType min, numType max);
		
		bool isInRange(numType n);
		bool isInRange(range<numType> r);
	};
}
#endif /* math_h */
