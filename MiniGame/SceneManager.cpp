//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameClear.h"
#include "GameOver.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "GameScene3.h"
#include "Main.h"
#include "SceneManager.h"
#include "SelectScene.h"
#include "Title.h"

//＝＝＝グローバル変数＝＝＝//
BASE_SCENE* SCENE_MANAGER::Scene = new TITLE();
SCENE SCENE_MANAGER::CurrentScene = SCENE_TITLE;
SCENE SCENE_MANAGER::NextScene = SCENE_TITLE;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：シーンの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SCENE_MANAGER::Draw(void)
{
    Scene->Draw();
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：シーンの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SCENE_MANAGER::Uninitialize(void)
{
    Scene->Uninitialize();
    delete Scene;
    Scene = nullptr;
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：シーンの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SCENE_MANAGER::Initialize(void)
{
    //---シーンの初期化---//
    if (FAILED(Scene->Initialize()))
    {
        MessageBoxW(nullptr, L"シーンの初期化に失敗しました失敗", L"初期化エラー", MB_OK);
        return E_FAIL;
    }

    return S_OK;
}

/////////////////////////////////////////////
//関数名：UpdateScene
//
//機能：シーンの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SCENE_MANAGER::Update(void)
{
    //---シーン切り替え---//
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
            MessageBoxW(nullptr, L"シーンの初期化に失敗しました失敗", L"初期化エラー", MB_OK);
            exit(EXIT_FAILURE);
        }

        CurrentScene = NextScene;
    }
    else
    {
        //---シーン関数呼び出し---//
        Scene->Update();
    }
}