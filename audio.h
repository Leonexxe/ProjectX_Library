/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
audio.h (c) 2021
Desc: description
Created:  2021-06-18T21:11:45.217Z
Modified: 2021-07-02T11:33:52.236Z
*/

#if defined(PX_WIN)
    #include "audio/audio_win.h"
#elif defined(PX_UNIX)
    #include "audio/audio_unix.h"
#else
    #error OS not supported (audio.h)
#endif