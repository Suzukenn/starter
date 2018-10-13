//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "Manual.h"
#include "SceneManager.h"
#include "SoundManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�}�j���A���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void MANUAL::Draw(void)
{
    Back.Draw();
    Title_B.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�}�j���A���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT MANUAL::Initialize(void)
{
    //---�I�u�W�F�N�g�̏�����---//
    if (FAILED(Back.Initialize(L"Data/Game/Manual.png")))
    {
        return E_FAIL;
    }

    //�X�^�[�g�{�^���̏�����
    Title_B.Initialize();
    Title_B.SetPos({ 100.0F,560.0F });

    //---BGM�Đ�---//
    SOUND_MANAGER::Play(BGM_OPENING);

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�}�j���A���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void MANUAL::Uninitialize(void)
{
    //---���---//
    Title_B.Uninitialize();
    Back.Uninitialize();

    //---BGM��~---//
    SOUND_MANAGER::Stop(BGM_OPENING);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�}�j���A���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void MANUAL::Update(void)
{
    //---�I�u�W�F�N�g�̍X�V---//
    Back.Update();
    Title_B.Update();
}