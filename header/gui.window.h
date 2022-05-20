// 
// gui.window.h 
// projectXLibMacOS 
// Created by Leonexxe on 30.03.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef gui_window_h
#define gui_window_h

#include "gui.h"
#include "gui.element.h"
#include "gui.object.h"

namespace px::gui
{
	class window : public object
	{
	#ifndef PX_PTP_GUI_WINDOW
		private:
	#else
		public:
	#endif
		classID ClassID = classes::window;
		
		void(*funcOnFullScreen)();
		/**
		 @brief the default function executed when the window is set to full screen, can be overridden by subclasses
		 */
		virtual void onFullScreen();
		
		//update lists
		std::list<element> UPDATE_CHANGING;
		std::list<element> UPDATE_SEMI_STATIC;
		std::list<element> UPDATE_STATIC;
		
	public:
		window(Bounds bounds);
		int close();
		bool isForeground();
		bool hasFocus();
		
		/**
		 @brief lets you set a function to be executet when the window is set to full screen
		 by default or when set to nullptr, window::onFullScreen will be executed. please note that instead of setting this to the same value for multiple window instances you can make a subclass of window and override window::onFullScreen since it is a virtual function
		 */
		void setOnFullScreen(void(*onFullScreen)());
	};
}
#endif /* gui_window_h */
