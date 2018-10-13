//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameClear.h"
#include "GameOver.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "GameScene3.h"
#include "Main.h"
#include "SceneManager.h"
#include "SelectScene.h"
#include "Title.h"

//�������O���[�o���ϐ�������//
BASE_SCENE* SCENE_MANAGER::Scene = new TITLE();
SCENE SCENE_MANAGER::CurrentScene = SCENE_TITLE;
SCENE SCENE_MANAGER::NextScene = SCENE_TITLE;

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
    delete Scene;
    Scene = nullptr;
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
    //---�V�[���̏�����---//
    if (FAILED(Scene->Initialize()))
    {
        MessageBoxW(nullptr, L"�V�[���̏������Ɏ��s���܂������s", L"�������G���[", MB_OK);
        return E_FAIL;
    }

    return S_OK;
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
        switch (NextScene)
        {
            case SCENE_TITLE:
                Scene = new TITLE();
                break;

            case SCENE_SELECT:
                Scene = new SELECTSCENE();
                break;

            case SCENE_GAME:
                Scene = new GAME();
                RETRYBUTTON::SetRetryScene(SCENE_GAME);
                break;

            case SCENE_GAME_2:
                Scene = new GAME_2();
                RETRYBUTTON::SetRetryScene(SCENE_GAME_2);
                break;

            case SCENE_GAME_3:
                Scene = new GAME_3();
                RETRYBUTTON::SetRetryScene(SCENE_GAME_3);
                break;

            case SCENE_GAMECLEAR:
                Scene = new GAMECLEAR();
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