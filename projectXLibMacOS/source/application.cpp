// 
// application.cpp 
// projectXLibMacOS 
// Created by Leonexxe on 23.02.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#include "../header/application.h"

namespace px
{
	void appDefaultSigHandler(PX_APP_sigHandlerArgs)
	{
	}
	
	application::application(){}
	
	application::application(
		__int__(*entryPoint)(PX_APP_threadEntryArgs),
		__string__ appName,
		__string__ execName,
		__string__ fsRoot,
		__uint__ thLimit,
		void(*defaultThreadExitHandler)(PX_APP_threadExitHandlerArgs)
	)
		:entryPoint(entryPoint),
		appName(appName),
		execName(execName),
		fsRoot(fsRoot),
		thLimit(thLimit),
		defaultThreadExitHandler(defaultThreadExitHandler)
	{
	}
	
	//misc
	__int__ application::run()
	{
		return this->entryPoint(this);
	}
	
	//multithreading
	__uint__ openThread(__int__(*threadEntry)(PX_APP_threadEntryArgs),__string__ name, void(*exitHandler)(PX_APP_threadExitHandlerArgs) = nullptr)
	{
		return 1;
	}
	
	void terminateThread()
	{
	}
	
	//signal handling
	void installSignalHandler(void(*sigHandler)(PX_APP_sigHandlerArgs))
	{
		if(sigHandler == nullptr)
			sigHandler = appDefaultSigHandler;
	}
	
	void removeSignalHandler()
	{
	}
}
