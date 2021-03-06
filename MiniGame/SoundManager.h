#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

//wb_t@CÇÝÝ//
#include <xaudio2.h>
#include "Main.h"
#include "SoundParameter.h"
#include "WavController.h"

//ñ^è`//
typedef enum
{ 
    BGM_GAME,       //Q[BGM
    BGM_GAMECLEAR,	//Q[NA
    BGM_GAMEOVER,	//Q[I[o[
    BGM_OPENING, 	//I[vjO
    BGM_SELECT,     //ZNgæÊ
    SE_DECISION,	//è
    SOUND_LABEL_MAX
} SOUND_LABEL;

//NXé¾//
class SOUND_MANAGER
{
    private:
        static IXAudio2* Manager;                                   //ÇIuWFNg
        static IXAudio2MasteringVoice* MasterVoice;                 //}X^[{CX
        static IXAudio2SourceVoice* SourceVoice[SOUND_LABEL_MAX];   //\[X{CX
        static WAVCONTROLLER WaveSound[SOUND_LABEL_MAX];          	// WAVE ¹yf[^

        static HRESULT CreateSound(SOUND_PARAMETER, int);

    public:
        static HRESULT Initialize(void);
        static void Play(SOUND_LABEL);
        static void Pause(SOUND_LABEL);
        static void Stop(SOUND_LABEL);
        static void Uninitialize(void);
};

#endif