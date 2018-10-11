//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SceneManager.h"
#include "SelectScene.h"
#include "Stage_EasyButton.h"
#include "Stage_HardButton.h"
#include "Stage_NormalButton.h"
#include "SoundManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�^�C�g���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SELECTSCENE::Draw(void)
{
    Back.Draw();
    Easy.Draw();
    Hard.Draw();
    Normal.Draw();
    Title.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�^�C�g���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SELECTSCENE::Initialize(void)
{
    //---�I�u�W�F�N�g�̏�����---//
    if (FAILED(Back.Initialize(L"Data/Game/Select.png")))
    {
        return E_FAIL;
    }

    if (FAILED(Easy.Initialize()))
    {
        return E_FAIL;
    }

    if (FAILED(Hard.Initialize()))
    {
        return E_FAIL;
    }

    if (FAILED(Normal.Initialize()))
    {
        return E_FAIL;
    }

    if (FAILED(Title.Initialize()))
    {
        return E_FAIL;
    }

    //---BGM�Đ�---//
    SOUND_MANAGER::Play(BGM_SELECT);

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�^�C�g���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SELECTSCENE::Uninitialize(void)
{
    //---���---//
    Back.Uninitialize();
    Easy.Uninitialize();
    Hard.Uninitialize();
    Normal.Uninitialize();
    Title.Initialize();

    //---BGM��~---//
    SOUND_MANAGER::Stop(BGM_SELECT);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�^�C�g���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SELECTSCENE::Update(void)
{
    //---�I�u�W�F�N�g�̍X�V---//
    Back.Update();
    Easy.Update();
    Hard.Update();
    Normal.Update();
    Title.Update();
}