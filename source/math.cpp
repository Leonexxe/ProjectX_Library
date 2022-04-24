// 
// math.cpp 
// projectXLibMacOS 
// Created by Leonexxe on 23.02.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include <stdio.h>

#include "../header/math.h"

namespace px
{
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
	
	__int__ random(__int__ min, __int__ max)
	{
		return rand();
	}
	
	vector<2,vectorType> rotate2D(__double__ alpha, vector<2,vectorType>* pointA,
		vector<2,vectorType>* pointO)
	{
		__vectorType__ Ox = pointO->get(0);
		__vectorType__ Oy = pointO->get(1);
		pointA = vectorBP(pointO,pointA);
		__vectorType__ Ax = pointA->get(0);
		__vectorType__ Ay = pointA->get(1);
		__double__ cA = cos(alpha);
		__double__ sA = sin(alpha);
		return vector<2,vectorType>({(cA*Ax-sA*Ay),(sA*Ax+cA*Ay)})+pointO;
	}
	
	__double__ distance(
			vector<vSize,vectorType>* vA,
			vector<vSize,vectorType>* vB)
	{
		__vectorType__ total;
		for(int I = 0;I<vSize;I++)
			total += (vA->get(I)-vB->get(I))**2
		return sqrt(total);
	}
	
	__double__ angleBV(vector<2,vectorType> A,vector<2,vectorType>)
	{
		vectorType aX = A->get(0);
		vectorType aY = A->get(1);
		vectorType bX = B->get(0);
		vectorType bY = B->get(1);
		
		return acos((aX*bX+aY*bY)/(sqrt(aX**2+aY**2)*sqrt(bX**2+bY**2)));
	}
	
	template<int vSize, typename pointType>
	vector<vSize,pointType> vectorBP(
			vector<vSize,pointType>* a,
			vector<vSize,pointType>* b)
	{
		return vector<vSize,pointType>({b->get(0)-a->get(0),b->get(1)-a->get(1)});
	}
}


