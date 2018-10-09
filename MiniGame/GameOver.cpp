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
	Title_B.Draw();
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

	//���g���C�{�^���̏�����
	Retry_B.Initialize();
	//�^�C�g���{�^���̏�����
	Title_B.Initialize();

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
	Title_B.Uninitialize();
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
<<<<<<< HEAD
	//���g���C�{�^���̍X�V����
	Retry_B.Update();
	//�^�C�g���{�^���̍X�V����
	Title_B.Update();
=======
    if (INPUT_MANAGER::GetKey(DIK_SPACE, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_TITLE);
    }
>>>>>>> 7d89c597109ed6004bd3f05ead395712797e4aa4
}