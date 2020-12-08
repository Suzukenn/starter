//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameOver.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�Q�[���I�[�o�[�ƃ{�^���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMEOVER::Draw(void)
{
	Back.Draw();
	Retry_B.Draw();
    Select_B.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�Q�[���I�[�o�[�ƃ{�^���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT GAMEOVER::Initialize(void)
{
    //---�I�u�W�F�N�g�̏�����---//
	if (FAILED(Back.Initialize(L"Data/Game/GameOver.png")))
	{
		return E_FAIL;
	}

    if (FAILED(Retry_B.Initialize()))
    {
        return E_FAIL;
    }

    if (FAILED(Select_B.Initialize()))
    {
        return E_FAIL;
    }

    //---BGM�Đ�---//
    SOUND_MANAGER::Play(BGM_GAMEOVER);

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�Q�[���I�[�o�[�ƃ{�^���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMEOVER::Uninitialize(void)
{
    //---���---//
    Select_B.Uninitialize();
	Retry_B.Uninitialize();
    Back.Uninitialize();
   
    //---BGM��~---//
    SOUND_MANAGER::Stop(BGM_GAMEOVER);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�Q�[���I�[�o�[�ƃ{�^���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMEOVER::Update(void)
{
	//---�I�u�W�F�N�g�̍X�V---//
	Back.Update();
    //---��ʑJ��---//
	//���g���C�{�^���̍X�V����
	Retry_B.Update();
	//�^�C�g���{�^���̍X�V����
    Select_B.Update();
}