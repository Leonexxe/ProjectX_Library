// 
// gui.draw.h 
// projectXLibMacOS 
// Created by Leonexxe on 26.04.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef gui_draw_h
#define gui_draw_h

#include "predef.h"
#include "../math.h"

namespace px::gui
{
	void drawLine(point2D start, point2D end);
	void drawRect(point2D upperLeft, point2D lowerRight);
	void drawCircle(point2D center, __int__ radius);
	void drawPoly(std::list<point2D> corners)
	void drawTriangle(point2D A, point2D B, point2D C);
	
	void setColor(__string__ hex);
}

#endif /* gui_draw_h */
