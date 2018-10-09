//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"

//�������萔�E�}�N����`������//
#define FILE_PATH L"Data/Game/BackGround.tga" //�p�X��

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
void GAME::Draw(void)
{
	Back.Draw();
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		//�v���C���[�̕`�揈��
		Player[i].Draw();
	}
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
HRESULT GAME::Initialize(void)
{
	//---�I�u�W�F�N�g�̏�����---//
	if (FAILED(Back.Initialize(FILE_PATH)))
	{
		return E_FAIL;
	}
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		//�v���C���[�̏�����
		Player[i].Initialize();
	}
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
void GAME::Uninitialize(void)
{
    //---�e����---//
	Operation.Uninitialize();
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		Player[i].Uninitialize();
	}
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
void GAME::Update(void)
{
	//---�I�u�W�F�N�g�̍X�V---//
	//�}�E�X�J�[�\���̍X�V����
	Operation.Update();
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		//�v���C���[�̍X�V����
		Player[i].Update();
	}
	Back.Update();

    //---��ʑJ��---//
    if (INPUT_MANAGER::GetKey(DIK_A, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_GAME_2);
    }
}