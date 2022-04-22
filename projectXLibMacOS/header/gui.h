// 
// gui.h 
// projectXLibMacOS 
// Created by Leonexxe on 14.03.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef gui_h
#define gui_h

#include "predef.h"
#include "gui.object.h"
#include "gui.element.h"
#include "gui.window.h"
#include "math.h"

namespace px::gui
{
	class Bounds
	{
	#ifndef PX_PTP_GUI_BOUNDS
		private:
	#else
		public:
	#endif
		
		__int__ x = 0;
		__int__ y = 0;
		__int__ width = 0;
		__int__ height = 0;
		
	public:
		Bounds();
		Bounds(__int__ x, __int__ y, __int__ width, __int__ height);
	};
	
	
	__int__ frameRateLimit = 0;
	__int__ STATIONARY_UPDATE_RATE = 60;
	
	//STATIC objects are only updated when element::update() is manually fired on them
	//SEMI_STATIC objects are only updated every STATIONARY_UPDATE_RATE frames
	//CHANGING objects are updated every frame
	enum elementState
	{
		STATIC,SEMI_STATIC,CHANGING
	};
}

#endif /* gui_h */
