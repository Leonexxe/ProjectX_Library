#include "../math.h"

#if defined(PX_AUDIO_XAUDIO2)
    #include "xaudio2.cpp"
    #pragma message("(PX::AUDIO) using xaudio2")
    #pragma message("(PX::audio) using xaudio2 might impact performance")
#elif defined(PX_AUDIO_WASAPI)
    #include "WASAPI.cpp"
    #pragma message("(PX::AUDIO) using WASAPI")
#else
    #error "(PX::AUDIO)(audio_win.cpp)" no audio API defined define "PX_AUDIO_WASAPI" to use WASAPI or "PX_AUDIO_XAUDIO2" to use XAUDIO2
#endif

namespace px::audio
{
    struct sound
    {
        sound(unsigned int fr, unsigned short amp)
        {
            this->frequency = fr;
            this->amplitude = amp;
        }
        unsigned int frequency;
        unsigned short amplitude;
    };

    class audio_out
    {
        public:
        audio_out()
        {
        }
        ~audio_out()
        {
        }
        unsigned int maxfrequenzy = 22000;
        unsigned int minfrequenzy = 1;
        unsigned int SampleBufferSize = 128;
        unsigned int samplerate(){return px::math::percent<int>(this->maxfrequenzy, 205);}
        unsigned int samp_rate = this->samplerate();
        /**
         * @brief set to 0 for mute, set to -1 to disable the limiter, (can be changed at any time, applies instantly)
         * please note that if this is 0 the sound still goes through but if played it won't actually produce sound
         */
        short limitDB = -1;

        void playsound(px::audio::sound* s)
        {
            if(this->limitDB == -1){}
            else if(s->amplitude > this->limitDB)
            {
                s->amplitude = this->limitDB;
            }
        }

        void setPlayBackDevice()
        {
        }
    };
}