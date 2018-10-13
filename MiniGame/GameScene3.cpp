//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Camera.h"
#include "GameScene3.h"
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
void GAME_3::Draw(void)
{
    //---�I�u�W�F�N�g�̕`��---//
    Back.Draw();
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        Camera[i].Draw();
    }
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
HRESULT GAME_3::Initialize(void)
{
    //---�e��錾---//
    const D3DXVECTOR2 CameraPos[MAX_CAMERA] = { { 200.0F,10.0F },{ 600.0F,10.0F } };

    //---�I�u�W�F�N�g�̏�����---//
    //�w�i
    if (FAILED(Back.Initialize(L"Data/Game/BackGround3.jpg")))
    {
        return E_FAIL;
    }

    //�v���C���[�̏�����
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        if (FAILED(Player[i].Initialize(i)))
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
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        if (FAILED(Camera[i].Initialize(CameraPos[i])))
        {
            return E_FAIL;
        }
    }

    //���t�g
    if (FAILED(Lift.Initialize({ 600.0F, 300.0F })))
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
void GAME_3::Uninitialize(void)
{
    //---�e����---//
    Back.Uninitialize();
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        Camera[i].Uninitialize();
    }
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
void GAME_3::Update(void)
{
    //---�I�u�W�F�N�g�̍X�V---//
    Operation.Update();
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        Player[i].Update(i);
    }
    Back.Update();
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        Camera[i].Update();
    }
    Lift.Update();
    Timer.Update();

    for (int i = 0; i < MAX_PLAYER; i++)
    {
        for (int j = 0; j < MAX_CAMERA; j++)
        {
            Player[i].SetHit(Camera[j].CheckPlayer(Player[i].GetPos(), Player[i].GetSize()));
        }
    }

    //---��ʑJ��---//
    if (!Timer.GetTime())
    {
        for (int i = 0; i < MAX_PLAYER; i++)
        {
            if (Player[i].GetHit())
            {
                SCENE_MANAGER::SetScene(SCENE_GAMEOVER);
                return;
            }
        }
        SCENE_MANAGER::SetScene(SCENE_GAMECLEAR);
    }
}