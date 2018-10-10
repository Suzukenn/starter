//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameClear.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：ゲームオーバーとボタンの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAMECLEAR::Draw(void)
{
    Back.Draw();
    Retry_B.Draw();
    Title_B.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ゲームオーバーとボタンの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT GAMECLEAR::Initialize(void)
{
    //---オブジェクトの初期化---//
    if (FAILED(Back.Initialize(L"Data/Game/GameClear.png")))
    {
        return E_FAIL;
    }

    //リトライボタンの初期化
    Retry_B.Initialize();
    //タイトルボタンの初期化
    Title_B.Initialize();

    //---BGM再生---//
    SOUND_MANAGER::Play(BGM_GAMECLEAR);

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ゲームオーバーとボタンの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAMECLEAR::Uninitialize(void)
{
    //---解放---//
    Title_B.Uninitialize();
    Retry_B.Uninitialize();
    Back.Uninitialize();

    //---BGM停止---//
    SOUND_MANAGER::Stop(BGM_GAMECLEAR);
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ゲームオーバーとボタンの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAMECLEAR::Update(void)
{
    //---オブジェクトの更新---//
    Back.Update();
    //---画面遷移---//
    //リトライボタンの更新処理
    Retry_B.Update();
    //タイトルボタンの更新処理
    Title_B.Update();
}