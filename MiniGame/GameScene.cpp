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
    Operation.Draw();
    Player.Draw();
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
    if (FAILED(Player.Initialize(0)))
    {
        return E_FAIL;
    }

	//�}�E�X�J�[�\��
    if (FAILED(Operation.Initialize()))
    {
        return E_FAIL;
    }

    //�J����
    if (FAILED(Camera.Initialize({ 400.0F, 10.0F })))
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
	Operation.Uninitialize();
    Player.Uninitialize();
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
	Back.Update();
    Camera.Update();
    Operation.Update();
    Player.Update(0, !Timer.GetCheck());
    Timer.Update();

    //---�����蔻��---//
    Player.SetHit(Camera.CheckPlayer(Player.GetPos(), Player.GetSize()));

    //---��ʑJ��---//
    if (!Timer.GetTime())
    {
        if (!Timer.GetCheck())
        {
            Timer.SetTime(CHECK_TIME);
            Timer.SetCheck(true);
        }
        else
        {
            if (Player.GetHit())
            {
                SCENE_MANAGER::SetScene(SCENE_GAMEOVER);
            }
            else
            {
                SCENE_MANAGER::SetScene(SCENE_GAMECLEAR);
            }
        }
    }
}