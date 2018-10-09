//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameScene_2.h"
#include "InputManager.h"
#include "RetryButton.h"
#include "SceneManager.h"
#include "SoundManager.h"

//�������萔�E�}�N����`������//
#define FILE_PATH L"Data/Game/bg.png" //�p�X��

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�Q�[���V�[���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAME_2::Draw(void)
{
	Back.Draw();
	//�v���C���[�̕`�揈��
	Player.Draw();
	//�}�E�X�J�[�\���̕`�揈��
	Operation.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�Q�[���V�[���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT GAME_2::Initialize(void)
{
	//---�I�u�W�F�N�g�̏�����---//
	if (FAILED(Back.Initialize(FILE_PATH)))
	{
		return E_FAIL;
	}
	//�v���C���[�̏�����
	Player.Initialize();
	//�}�E�X�J�[�\���̏�����
	Operation.Initialize();

    //---BGM�Đ�---//
    SOUND_MANAGER::Play(BGM_GAME);

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�Q�[���V�[���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAME_2::Uninitialize(void)
{
    //---�e����---//
	Operation.Uninitialize();
	Player.Uninitialize();
	Back.Uninitialize();
    //---BGM��~---//
    SOUND_MANAGER::Stop(BGM_GAME);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�Q�[���V�[���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAME_2::Update(void)
{
	//---�I�u�W�F�N�g�̍X�V---//
	//�}�E�X�J�[�\���̍X�V����
	Operation.Update();
	//�v���C���[�̍X�V����
	Player.Update();
	Back.Update();

    //---��ʑJ��---//
    if (INPUT_MANAGER::GetKey(DIK_A, TRIGGER))
    {
		//���g���C��̃Z�b�g
		RETRYBUTTON::SetRetryScene(SCENE_GAME_2);
		//�V�[���ؑ�
        SCENE_MANAGER::SetScene(SCENE_GAMEOVER);
    }
}