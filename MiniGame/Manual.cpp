//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "Manual.h"
#include "SceneManager.h"
#include "SoundManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：マニュアルの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void MANUAL::Draw(void)
{
    Back.Draw();
    Title_B.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：マニュアルの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT MANUAL::Initialize(void)
{
    //---オブジェクトの初期化---//
    if (FAILED(Back.Initialize(L"Data/Game/Manual.png")))
    {
        return E_FAIL;
    }

    //スタートボタンの初期化
    Title_B.Initialize();
    Title_B.SetPos({ 100.0F,560.0F });

    //---BGM再生---//
    SOUND_MANAGER::Play(BGM_OPENING);

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：マニュアルの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void MANUAL::Uninitialize(void)
{
    //---解放---//
    Title_B.Uninitialize();
    Back.Uninitialize();

    //---BGM停止---//
    SOUND_MANAGER::Stop(BGM_OPENING);
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：マニュアルの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void MANUAL::Update(void)
{
    //---オブジェクトの更新---//
    Back.Update();
    Title_B.Update();
}