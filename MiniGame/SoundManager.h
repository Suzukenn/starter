#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <xaudio2.h>
#include "Main.h"
#include "Sound_Parameter.h"
#include "Wav_Controller.h"

//＝＝＝列挙型定義＝＝＝//
typedef enum
{ 
    BGM_GAME,       //オープニング
    BGM_GAMEOVER,	//ゲームBGM
    BGM_OPENING, 	//オープニング
    SE_BREAK,       //撃破
    SE_DAMAGE,	   	//被弾
    SE_DECISION,	//決定
    SE_HIT,		   	//攻撃
    SE_INSTANTIATE,	//適生成
    SE_JUMP,		//ジャンプ
    SE_SHOT,	  	//攻撃
    SOUND_LABEL_MAX
} SOUND_LABEL;

//＝＝＝クラス宣言＝＝＝//
class SOUND_MANAGER
{
    private:
        static IXAudio2* Manager;                                   //管理オブジェクト
        static IXAudio2MasteringVoice* MasterVoice;                 //マスターボイス
        static IXAudio2SourceVoice* SourceVoice[SOUND_LABEL_MAX];   //ソースボイス
        static WAV_CONTROLLER WaveSound[SOUND_LABEL_MAX];          	// WAVE 音楽データ

        static HRESULT CreateSound(SOUND_PARAMETER, int);

    public:
        static HRESULT Initialize(void);
        static void Play(SOUND_LABEL);
        static void Pause(SOUND_LABEL);
        static void Stop(SOUND_LABEL);
        static void Uninitialize(void);
};

#endif