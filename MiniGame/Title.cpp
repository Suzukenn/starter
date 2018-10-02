//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"
#include "Title.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�w�i�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Draw(void)
{
	Back.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�w�i�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT TITLE::Initialize(void)
{
	//---�I�u�W�F�N�g�̏�����---//
	if (FAILED(Back.Initialize(L"Data/Game/Title.png")))
	{
		return E_FAIL;
	}

    //---BGM�Đ�---//
    SOUND_MANAGER::Play(BGM_OPENING);

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�w�i�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Uninitialize(void)
{
    //---���---//
	Back.Uninitialize();

    //---BGM��~---//
    SOUND_MANAGER::Stop(BGM_OPENING);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�w�i�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Update(void)
{
	//---�I�u�W�F�N�g�̍X�V---//
    //�w�i
    Back.Update();

    //---��ʑJ��---//
    if (INPUT_MANAGER::GetKey(DIK_A, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_GAME);
    }
}