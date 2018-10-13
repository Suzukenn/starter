//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameScene2.h"
#include "InputManager.h"
#include "RetryButton.h"
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
void GAME_2::Draw(void)
{
    //---�e��錾---//
    int nCounter;

    //---�I�u�W�F�N�g�̕`��---//
    Back.Draw();
    for (nCounter = 0; nCounter < MAX_CAMERA; nCounter++)
    {
        Camera[nCounter].Draw();
    }
    Lift.Draw();
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
HRESULT GAME_2::Initialize(void)
{
    //---�e��錾---//
    int nCounter;

    const D3DXVECTOR2 CameraPos[MAX_CAMERA] = { {300.0F,10.0F},{600.0F,10.0F} };

	//---�I�u�W�F�N�g�̏�����---//
    if (FAILED(Back.Initialize(L"Data/Game/BackGround.png")))
    {
        return E_FAIL;
    }

    for (nCounter = 0; nCounter < MAX_CAMERA; nCounter++)
    {
        if (FAILED(Camera[nCounter].Initialize(CameraPos[nCounter])))
        {
            return E_FAIL;
        }
    }

    if (FAILED(Lift.Initialize({550.0F,300.0F})))
    {
        return E_FAIL;
    }

    if (FAILED(Operation.Initialize()))
    {
        return E_FAIL;
    }

    if (FAILED(Player.Initialize(0)))
    {
        return E_FAIL;
    }

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
void GAME_2::Uninitialize(void)
{
    //---�e��錾---//
    int nCounter;

    //---�e����---//
    Back.Uninitialize();
    for (nCounter = 0; nCounter < MAX_CAMERA; nCounter++)
    {
        Camera[nCounter].Uninitialize();
    }
    Lift.Uninitialize();
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
void GAME_2::Update(void)
{
    //---�e��錾---//
    int nCounter;

	//---�I�u�W�F�N�g�̍X�V---//
    Back.Update();
    for (nCounter = 0; nCounter < MAX_CAMERA; nCounter++)
    {
        Camera[nCounter].Update();
    }
    Lift.Update();
    Operation.Update();
    Player.Update(0, !Timer.GetCheck());
    Timer.Update();

    //---�����蔻��---//
    for (nCounter = 0; nCounter < MAX_CAMERA; nCounter++)
    {
        if (Camera[nCounter].CheckPlayer(Player.GetPos(), Player.GetSize()))
        {
            Player.SetHit(true);
            break;
        }
        else
        {
            Player.SetHit(false);
        }
    }

    //---�n�`����---//
    Player.CheckCollisionLift(Lift.GetPos(), Lift.GetSize());

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