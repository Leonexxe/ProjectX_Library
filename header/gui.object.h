// 
// gui.object.h 
// projectXLibMacOS 
// Created by Leonexxe on 21.04.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef gui_object_h
#define gui_object_h

namespace px::gui
{
	typedef __ulong__ classID;
	namespace classes
	{
		const classID OBJ_GENERIC = 0;
		const classID window = 1;
		const classID element = 2;
	}
	
	class object
	{
	#ifndef PX_PTP_GUI_OBJECT
		private:
	#else
		public:
	#endif
		classID ClassID = classes::OBJ_GENERIC;
		__ulong__ ID = 0;
		
	public:
		virtual __ulong__ getID();
		virtual __ulong__ getClassID();
	};
}

#endif /* gui_object_h */
