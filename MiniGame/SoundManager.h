#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <xaudio2.h>
#include "Main.h"
#include "SoundParameter.h"
#include "WavController.h"

//�������񋓌^��`������//
typedef enum
{ 
    BGM_GAME,       //�Q�[��BGM
    BGM_GAMECLEAR,	//�Q�[���N���A
    BGM_GAMEOVER,	//�Q�[���I�[�o�[
    BGM_OPENING, 	//�I�[�v�j���O
    BGM_SELECT,     //�Z���N�g���
    SE_DECISION,	//����
    SOUND_LABEL_MAX
} SOUND_LABEL;

//�������N���X�錾������//
class SOUND_MANAGER
{
    private:
        static IXAudio2* Manager;                                   //�Ǘ��I�u�W�F�N�g
        static IXAudio2MasteringVoice* MasterVoice;                 //�}�X�^�[�{�C�X
        static IXAudio2SourceVoice* SourceVoice[SOUND_LABEL_MAX];   //�\�[�X�{�C�X
        static WAVCONTROLLER WaveSound[SOUND_LABEL_MAX];          	// WAVE ���y�f�[�^

        static HRESULT CreateSound(SOUND_PARAMETER, int);

    public:
        static HRESULT Initialize(void);
        static void Play(SOUND_LABEL);
        static void Pause(SOUND_LABEL);
        static void Stop(SOUND_LABEL);
        static void Uninitialize(void);
};

#endif