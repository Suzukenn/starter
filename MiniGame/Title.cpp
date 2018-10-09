//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Title.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
<<<<<<< HEAD
//�@�\�F�w�i�ƃ{�^���̕`��
=======
//�@�\�F�^�C�g���̕`��
>>>>>>> 7d89c597109ed6004bd3f05ead395712797e4aa4
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
<<<<<<< HEAD
//�@�\�F�w�i�ƃ{�^���̏�����
=======
//�@�\�F�^�C�g���̏�����
>>>>>>> 7d89c597109ed6004bd3f05ead395712797e4aa4
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

	//�X�^�[�g�{�^���̏�����
	Start_B.Initialize();

    //---BGM�Đ�---//
    SOUND_MANAGER::Play(BGM_OPENING);

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
<<<<<<< HEAD
//�@�\�F�w�i�ƃ{�^���̏I��
=======
//�@�\�F�^�C�g���̏I��
>>>>>>> 7d89c597109ed6004bd3f05ead395712797e4aa4
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
<<<<<<< HEAD
//�@�\�F�w�i�ƃ{�^���̍X�V
=======
//�@�\�F�^�C�g���̍X�V
>>>>>>> 7d89c597109ed6004bd3f05ead395712797e4aa4
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Update(void)
{
	//---�I�u�W�F�N�g�̍X�V---//
<<<<<<< HEAD
	Start_B.Update();
=======
    //�w�i
    Back.Update();

    //---��ʑJ��---//
    if (INPUT_MANAGER::GetKey(DIK_SPACE, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_SELECT);
    }
>>>>>>> 7d89c597109ed6004bd3f05ead395712797e4aa4
}