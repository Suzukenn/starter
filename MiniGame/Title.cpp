//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"
#include "Title.h"

//�������萔�E�}�N����`������//
#define FILE_PATH L"Data/Game/Title.png" //�p�X��

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�w�i�ƃ{�^���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Draw(void)
{
	Back.Draw();
	Start_B.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�w�i�ƃ{�^���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT TITLE::Initialize(void)
{
	//---�I�u�W�F�N�g�̏�����---//
	if (FAILED(Back.Initialize(FILE_PATH)))
	{
		return E_FAIL;
	}

	//�X�^�[�g�{�^���̏�����
	Start_B.Initialize();

    //---BGM�Đ�---//
    SOUND_MANAGER::Play(BGM_OPENING);

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�w�i�ƃ{�^���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Uninitialize(void)
{
    //---���---//
	Start_B.Uninitialize();
	Back.Uninitialize();

    //---BGM��~---//
    SOUND_MANAGER::Stop(BGM_OPENING);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�w�i�ƃ{�^���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Update(void)
{
	//---�I�u�W�F�N�g�̍X�V---//
	Start_B.Update();
}