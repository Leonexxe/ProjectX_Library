// 
// math.cpp 
// projectXLibMacOS 
// Created by Leonexxe on 23.02.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include <stdio.h>

#include "../header/math.h"
#include "temp.cpp"

namespace px
{
	namespace math {
		bool __init__(){srand(time(0));return 0;}
		bool m_init = __init__();
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
		__int__ hC,
		//misc
		__string__ s)
	{
		return -1;
	}
	
	//
	//vector class
	//
	template<int vSize, typename dataType>
	vector::vector(){}
	template<int vSize, typename dataType>
	vector::vector(std::list<dataType> data)
		:data(data){}
	
	template<int vSize, typename dataType>
	dataType vector::get(__int__ index)
	{
		return this->data[index];
	}
	
	template<int vSize, typename dataType>
	void vector::set(__int__ index, dataType value)
	{
		this->data[index] = value;
	}
	
	//
	// random
	//
	template<typename returnType>
	returnType random()
	{
	#ifdef PX_c1
		returnType R = (returnType)(rand())*0.0000001;
		return R;
	#else
		returnType R = (returnType)rand();
		return R;
	#endif
	}
	
	/**
	 * @brief this is **NOT** realtime safe! it is important that one can cast from inputType to returnType
	 *
	 * @tparam inputType .
	 * @tparam returnType .
	 * @param min .
	 * @param max .
	 * @return returnType
	 */
	template<typename inputType,typename returnType>
	returnType random(inputType min, inputType max,std::list<inputType>* exclude)
	{
		returnType R = random<returnType>();
		while(R < min || R > max || px::tools::lists::contains(exclude,(inputType)R))
		{
			R = random<returnType>();
		#ifdef PX_DEBUG
			std::cout << R << std::endl;
		#endif
		}
		return R;
	}
	
	
	/**
	 @brief rotates pointA around pointO by alpha
	 */
	template<typename vectorType>
	vector<2,vectorType> rotate2D(__double__ alpha, vector<2,vectorType>* pointA,
		vector<2,vectorType>* pointO)
	{
		vectorType Ox = pointO->get(0);
		vectorType Oy = pointO->get(1);
		pointA = vectorBP(pointO,pointA);
		vectorType Ax = pointA->get(0);
		vectorType Ay = pointA->get(1);
		__double__ cA = cos(alpha);
		__double__ sA = sin(alpha);
		return vector<2,vectorType>({(cA*Ax-sA*Ay),(sA*Ax+cA*Ay)})+pointO;
	}
	
	/**
	 @brief calculates the distance between 2 points in an n-dimensional space (source: https://en.wikipedia.org/wiki/Distance)
	 */
	template<typename vectorType, int vSize>
	__double__ distance(
			vector<vSize,vectorType>* vA,
			vector<vSize,vectorType>* vB)
	{
		vectorType total;
		for(int I = 0;I<vSize;I++)
			total += pow((vA->get(I)-vB->get(I)),2);
		return sqrt(total);
	}
	
	
	/**
	 @brief calculates the angle between 2 vectors
	 */
	template<typename vectorType>
	__double__ angleBV(vector<2,vectorType> A,vector<2,vectorType> B)
	{
		vectorType aX = A->get(0);
		vectorType aY = A->get(1);
		vectorType bX = B->get(0);
		vectorType bY = B->get(1);
		
		return acos((aX*bX+aY*bY)/(sqrt(pow(aX,2)+pow(aY,2))*sqrt(pow(bX,2)+pow(bY,2))));
	}
	
	template<int vSize, typename pointType>
	vector<vSize,pointType> vectorBP(
			vector<vSize,pointType>* a,
			vector<vSize,pointType>* b)
	{
		return vector<vSize,pointType>({b->get(0)-a->get(0),b->get(1)-a->get(1)});
	}
}


