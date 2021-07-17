/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
xaudio2.cpp (c) 2021
Desc: description
Created:  2021-07-02T11:47:35.220Z
Modified: 2021-07-17T23:13:37.575Z
*/

#include <xaudio2.h>
#include <vector>
#include "../sysout.h"

namespace px::audio
{
    void playsound()
    {
    }

    bool bufferListLocked = 0;
    bool sourceVoiceListLocked = 0;
  
    std::list<IXAudio2SourceVoice*> sourceVoices;
    std::list<XAUDIO2_BUFFER> buffers;
    
    IXAudio2* pXAudio2 = nullptr;
    IXAudio2MasteringVoice* pMasterVoice = nullptr;
    HRESULT hr;

    void __INIT__()
    {
        hr = CoInitializeEx(nullptr,COINIT_MULTITHREADED);
        if(FAILED(hr))
            return;  
        if(FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
            return;
        if(FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice)))
            return;
    }

    void writeToBuffer()
    {
    }

    void lockBufferList(){bufferListLocked = 1;}
    void unlockBufferList(){bufferListLocked = 0;}
    void lockSourceVoiceList(){bufferListLocked = 1;}
    void unlockSourceVoiceList(){bufferListLocked = 0;}

    void StartPlayerThread()
    {
        XAUDIO2_BUFFER* buffer;
        IXAudio2SourceVoice* sourceVoice;
        {   
            XAUDIO2_BUFFER buff;
            while(bufferListLocked){} // wait for buffer list to be unlocked
            lockBufferList();
            buffers.push_back(buff);
            buffer = &buffers.back();
            unlockBufferList();
        }
        {   
            IXAudio2SourceVoice* pSourceVoice = nullptr;
            WAVEFORMATEX wfx;
            if(FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx)))
                return;
            while(sourceVoiceListLocked){} // wait for sourceVoice list to be unlocked
            lockSourceVoiceList();
            sourceVoices.push_back(pSourceVoice);
            sourceVoice = sourceVoices.back();
            unlockSourceVoiceList();
        }
        
        if(FAILED(hr = sourceVoice->SubmitSourceBuffer(buffer)))
            return;
        if(FAILED(hr = sourceVoice->Start(0)))
            return;
    }

    bool __init__()
    {
        px::sysInfo("initiating px::audio");
        return 1;
    }
    bool a__init__ = __init__();
}
