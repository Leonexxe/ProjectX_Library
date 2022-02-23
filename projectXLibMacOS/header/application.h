// 
// application.h 
// projectXLibMacOS 
// Created by Leonexxe on 23.02.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#ifndef application_h
#define application_h

#include "predef.h"
#include "base.h"
#include <string>
#include <thread>

namespace px
{
    #define PX_APP_threadEntryArgs application*
    #define PX_APP_threadExitHandlerArgs application*
    #define PX_APP_sigHandlerArgs application*, int signum
    #ifndef PX_APP_REDEFINE_threadInfo
        typedef base::threadInfo threadInfo;
    #endif
	
    class application
    {
	#ifndef PX_PTP_APP
		private:
	#else
		public:
	#endif
	//private members
		__uint__ runningThreads = 0;
		
    public:
		__string__ appName, execName, fsRoot;
		__uint__ thLimit;
		__int__(*entryPoint)(PX_APP_threadEntryArgs); // entry point for the application (execute via this.run())
		void(*defaultThreadExitHandler)(PX_APP_threadExitHandlerArgs); // pointer to the function executed when a subthread of the application exits
		
		application();
		application(
					__int__(*entryPoint)(PX_APP_threadEntryArgs),
					__string__ appName,
					__string__ execName,
					__string__ fsRoot,
					__uint__ thLimit,
					void(*defaultThreadExitHandler)(PX_APP_threadExitHandlerArgs)
					);
		
		~application();
		
		//misc
		__int__ run();
		
		//multithreading
		__uint__ openThread(__int__(*threadEntry)(PX_APP_threadEntryArgs), __string__ name, void(*exitHandler)(PX_APP_threadExitHandlerArgs) = nullptr);
		void terminateThread(__uint__ threadID);
		
		//logging
		void log(__string__ lName, __string__ msg, bool sysout);
		void clearLogs(__string__ lName = "");
		
		//signal handling
		void installSignalHanlder(void(*sigHanlder)(PX_APP_sigHandlerArgs));
		void removeSignalHanlder();
    };
}

#endif /* application_h */
