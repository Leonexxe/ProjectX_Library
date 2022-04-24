// 
// gui.element.h 
// projectXLibMacOS 
// Created by Leonexxe on 30.03.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef gui_element_h
#define gui_element_h

#include "gui.h"

namespace px::gui
{
	class element : public object
	{
	#ifndef PX_PTP_GUI_ELEMENT
		private:
	#else
		public:
	#endif
		bool visible = 0;
		element* parent;
		
		px::vector<2,__int__> origin;
		
		//position
		__int__ x = 0;
		__int__ y = 0;
		//rect
		__int__ rect_width = 0;
		__int__ rect_height = 0;
		//circle
		__int__ radius = 0;
		px::vector<2,__int__> center;
		
		
	public:
		element();
		element(element* parent);
		
		void setState();
		
		virtual void setSize(__int__ x,__int__ y);
		virtual void setPosition(__int__ x, __int__ y);
		virtual void setRotation(__int__ alpha);
		
		virtual void hide();
		virtual void show();
		virtual void toggleVisibility();
		
		virtual void update();
		
		virtual void remove();
		virtual void scale(__double__ scaleFactor);
	};
}

#endif /* gui_element_h */
