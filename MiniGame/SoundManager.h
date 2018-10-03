#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <xaudio2.h>
#include "Main.h"
#include "Sound_Parameter.h"
#include "Wav_Controller.h"

//�������񋓌^��`������//
typedef enum
{ 
    BGM_GAME,       //�I�[�v�j���O
    BGM_GAMEOVER,	//�Q�[��BGM
    BGM_OPENING, 	//�I�[�v�j���O
    SE_BREAK,       //���j
    SE_DAMAGE,	   	//��e
    SE_DECISION,	//����
    SE_HIT,		   	//�U��
    SE_INSTANTIATE,	//�K����
    SE_JUMP,		//�W�����v
    SE_SHOT,	  	//�U��
    SOUND_LABEL_MAX
} SOUND_LABEL;

//�������N���X�錾������//
class SOUND_MANAGER
{
    private:
        static IXAudio2* Manager;                                   //�Ǘ��I�u�W�F�N�g
        static IXAudio2MasteringVoice* MasterVoice;                 //�}�X�^�[�{�C�X
        static IXAudio2SourceVoice* SourceVoice[SOUND_LABEL_MAX];   //�\�[�X�{�C�X
        static WAV_CONTROLLER WaveSound[SOUND_LABEL_MAX];          	// WAVE ���y�f�[�^

        static HRESULT CreateSound(SOUND_PARAMETER, int);

    public:
        static HRESULT Initialize(void);
        static void Play(SOUND_LABEL);
        static void Pause(SOUND_LABEL);
        static void Stop(SOUND_LABEL);
        static void Uninitialize(void);
};

#endif