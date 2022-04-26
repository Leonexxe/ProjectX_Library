// 
// gui.color.h 
// projectXLibMacOS 
// Created by Leonexxe on 26.04.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef gui_color_h
#define gui_color_h

#include "predef.h"

namespace px::gui
{
	class color
	{
	#ifndef PX_PTP_GUI_COLOR
		private:
	#else
		public:
	#endif
		
	public:
		color(__string__ hex);
		color(__int__ red, __int__ green, __int__ blue);
		
	}
}

#endif /* gui_color_h */
