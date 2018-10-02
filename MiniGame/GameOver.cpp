//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameOver.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"

//�������萔�E�}�N����`������//
#define FILE_PATH L"Data/Game/GameOver.png" //�p�X��

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�Q�[���I�[�o�[�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMEOVER::Draw(void)
{
	Back.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�Q�[���I�[�o�[�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT GAMEOVER::Initialize(void)
{
    //---�I�u�W�F�N�g�̏�����---//
	if (FAILED(Back.Initialize(FILE_PATH)))
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
//�@�\�F�Q�[���I�[�o�[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMEOVER::Uninitialize(void)
{
    //---���---//
    Back.Uninitialize();
   
    //---BGM��~---//
    SOUND_MANAGER::Stop(BGM_GAMEOVER);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�Q�[���I�[�o�[�̍X�V
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
    if (INPUT_MANAGER::GetKey(DIK_A, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_TITLE);
    }
}