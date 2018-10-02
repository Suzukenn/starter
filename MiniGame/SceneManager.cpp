//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameOver.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Title.h"

//＝＝＝グローバル変数＝＝＝//
BASE_SCENE* SCENE_MANAGER::Scene = new TITLE();
SCENE SCENE_MANAGER::CurrentScene;
SCENE SCENE_MANAGER::NextScene;

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
    //---各種宣言---//
    HRESULT hResult;
    
    //---初期化処理---//
    hResult = E_FAIL;

    //---シーンの切り替え---//
    hResult = Scene->Initialize();
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"シーンの初期化に失敗しました失敗", L"初期化エラー", MB_OK);
        return hResult;
    }

    return hResult;
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