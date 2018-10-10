//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Camera.h"
#include "GameScene.h"
#include "InputManager.h"
#include "Lift.h"
#include "SceneManager.h"
#include "SoundManager.h"

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
    Camera.Draw();
    Lift.Draw();
    Operation.Draw();
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        //�v���C���[�̕`�揈��
        Player[i].Draw();
    }
    Timer.Draw();
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

    //�v���C���[�̏�����
	for (int i = 0; i < MAX_PLAYER; i++)
	{
        if (FAILED(Player[i].Initialize()))
        {
            return E_FAIL;
        }
    }
	//�}�E�X�J�[�\���̏�����
	Operation.Initialize();

	//�}�E�X�J�[�\��
    if (FAILED(Operation.Initialize()))
    {
        return E_FAIL;
    }

    //�J����
    if (FAILED(Camera.Initialize({ 400.0F, 10.0F }, 45.0F)))
    {
        return E_FAIL;
    }

    //���t�g
    if (FAILED(Lift.Initialize({ 600.0F, 300.0F }, { 150.0F, 30.0F })))
    {
        return E_FAIL;
    }

    //�^�C�}�[
    if (FAILED(Timer.Initialize()))
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
    Camera.Uninitialize();
    Lift.Uninitialize();
	Operation.Uninitialize();
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		Player[i].Uninitialize();
	}
	Back.Uninitialize();
    Timer.Uninitialize();

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
    Camera.Update();
    Lift.Update();
    Timer.Update();

    //Player.SetHit(Camera.CheckPlayer(Player.GetPos(), Player.GetSize()));

    //---��ʑJ��---//
    if (!Timer.GetTime())
    {
        SCENE_MANAGER::SetScene(SCENE_GAME_2);
    }
}