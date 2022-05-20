// 
// gui.OSX.h 
// projectXLibMacOS 
// Created by Leonexxe on 14.05.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef gui_OSX_h
#define gui_OSX_h

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace px::gui
{
	class Renderer
	{
	public:
		Renderer( MTL::Device* pDevice );
		~Renderer();
		void draw( MTK::View* pView );
		
	private:
		MTL::Device* _pDevice;
		MTL::CommandQueue* _pCommandQueue;
	};
	
	class PxMTKViewDelegate : public MTK::ViewDelegate
	{
	public:
		PxMTKViewDelegate( MTL::Device* pDevice );
		virtual ~PxMTKViewDelegate() override;
		virtual void drawInMTKView( MTK::View* pView ) override;
	
	private:
		Renderer* _pRenderer;
	};
	
	class PxAppDelegate : public NS::ApplicationDelegate
	{
	public:
		~PxAppDelegate();
		
		NS::Menu* createMenuBar();
		
		virtual void applicationWillFinishLaunching( NS::Notification* pNotification ) override;
		virtual void applicationDidFinishLaunching( NS::Notification* pNotification ) override;
		virtual bool applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender ) override;
		
	private:
		NS::Window* _pWindow;
		MTK::View* _pMtkView;
		MTL::Device* _pDevice;
		PxMTKViewDelegate* _pViewDelegate = nullptr;
	};
}



#endif /* gui_OSX_h */
