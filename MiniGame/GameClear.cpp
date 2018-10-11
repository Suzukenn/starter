//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameClear.h"
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
void GAMECLEAR::Draw(void)
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
HRESULT GAMECLEAR::Initialize(void)
{
    //---�I�u�W�F�N�g�̏�����---//
    if (FAILED(Back.Initialize(L"Data/Game/GameClear.png")))
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
    SOUND_MANAGER::Play(BGM_GAMECLEAR);

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
void GAMECLEAR::Uninitialize(void)
{
    //---���---//
    Select_B.Uninitialize();
    Retry_B.Uninitialize();
    Back.Uninitialize();

    //---BGM��~---//
    SOUND_MANAGER::Stop(BGM_GAMECLEAR);
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
void GAMECLEAR::Update(void)
{
    //---�I�u�W�F�N�g�̍X�V---//
    Back.Update();
    Retry_B.Update();
    Select_B.Update();
}