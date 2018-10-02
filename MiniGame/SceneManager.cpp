//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameOver.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Title.h"

//�������O���[�o���ϐ�������//
BASE_SCENE* SCENE_MANAGER::Scene = new TITLE();
SCENE SCENE_MANAGER::CurrentScene;
SCENE SCENE_MANAGER::NextScene;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�V�[���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SCENE_MANAGER::Draw(void)
{
    Scene->Draw();
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�V�[���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SCENE_MANAGER::Uninitialize(void)
{
    Scene->Uninitialize();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�V�[���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SCENE_MANAGER::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;
    
    //---����������---//
    hResult = E_FAIL;

    //---�V�[���̐؂�ւ�---//
    hResult = Scene->Initialize();
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"�V�[���̏������Ɏ��s���܂������s", L"�������G���[", MB_OK);
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUpdateScene
//
//�@�\�F�V�[���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SCENE_MANAGER::Update(void)
{
    //---�V�[���؂�ւ�---//
    if (CurrentScene != NextScene)
    {
        Scene->Uninitialize();
        delete Scene;
        switch (NextScene)
        {
            case SCENE_TITLE:
                Scene = new TITLE();
                break;

            case SCENE_GAME:
                Scene = new GAME();
                break;

            case SCENE_GAMEOVER:
                Scene = new GAMEOVER();
                break;
        }

        if (FAILED(Scene->Initialize()))
        {
            MessageBoxW(nullptr, L"�V�[���̏������Ɏ��s���܂������s", L"�������G���[", MB_OK);
            exit(EXIT_FAILURE);
        }

        CurrentScene = NextScene;
    }
    else
    {
        //---�V�[���֐��Ăяo��---//
        Scene->Update();
    }
}