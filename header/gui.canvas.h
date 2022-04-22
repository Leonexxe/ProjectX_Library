// 
// gui.canvas.h 
// projectXLibMacOS 
// Created by Leonexxe on 31.03.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include "gui.h"

#ifndef gui_canvas_h
#define gui_canvas_h

namespace px::gui
{
	class canvas : public element
	{
		#ifndef PX_PTP_GUI_ELEMENT
			private:
		#else
			public:
		#endif
		canvas();
		
		void setColor(__int__ R,__int__ G,__int__ B,__int__ alpha);
		void setWidth(__int__ w);
		
		void drawLine(__int__ start, __int__ end);
		
		/**
		 * @brief function: a^(x+XO)+xAxisOffset
		 */
		void drawEXP(__int__ a,__int__ XO,__int__ xAxisOffset,
					 __int__ startX,__int__ endX,__int__ stepX,
					 __int__ sX,__int__ sY,bool drawMode);
		
		void drawCircle(__int__ radius, __int__ cX, __int__ cY);
		void drawCircleSC(__int__ radius, __int__ sX, __int__ sY);
		void drawImage(__string__ absolutePath);
		void exportImage(ImageFormat format);
		void clear();
	};
}

#endif /* gui_canvas_h */
