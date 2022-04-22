// 
// gui.activeElement.h 
// projectXLibMacOS 
// Created by Leonexxe on 20.04.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef gui_activeElement_h
#define gui_activeElement_h

#include "gui.element.h"

namespace px::gui
{
	class activeElement : public element
	{
		void setOnHover(void(*onHover)());
		void setOnClick(void(*onClick)());
		
		virtual void onHover();
		virtual void onClick();
	}
}


#endif /* gui_activeElement_h */
