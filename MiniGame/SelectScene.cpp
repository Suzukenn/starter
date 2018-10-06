//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SceneManager.h"
#include "SelectScene.h"
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
    //�w�i
    Back.Update();

    //---��ʑJ��---//
    if (INPUT_MANAGER::GetKey(DIK_SPACE, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_GAME);
    }
}