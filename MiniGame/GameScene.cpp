//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"

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
    //---�I�u�W�F�N�g�̕`��---//
	Back.Draw();
	Player.Draw();	    //�v���C���[
    Operation.Draw();	//�}�E�X�J�[�\��
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
    //�w�i
	if (FAILED(Back.Initialize(L"Data/Game/BackGround.tga")))
	{
		return E_FAIL;
	}
	//�v���C���[
    if (FAILED(Player.Initialize()))
    {
        return E_FAIL;
    }

	//�}�E�X�J�[�\��
    if (FAILED(Operation.Initialize()))
    {
        return E_FAIL;
    }

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
    Back.Uninitialize();
	Operation.Uninitialize();
	Player.Uninitialize();

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
    //�w�i
    Back.Update();
	Operation.Update(); 	//�}�E�X�J�[�\��
	Player.Update();	//�v���C���[

    //---��ʑJ��---//
    if (INPUT_MANAGER::GetKey(DIK_A, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_GAMEOVER);
    }
}