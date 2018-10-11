//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SceneManager.h"
#include "SelectScene.h"
#include "Stage_EasyButton.h"
#include "Stage_HardButton.h"
#include "Stage_NormalButton.h"
#include "SoundManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：タイトルの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SELECTSCENE::Draw(void)
{
    Back.Draw();
    Easy.Draw();
    Hard.Draw();
    Normal.Draw();
    Title.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：タイトルの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SELECTSCENE::Initialize(void)
{
    //---オブジェクトの初期化---//
    if (FAILED(Back.Initialize(L"Data/Game/Select.png")))
    {
        return E_FAIL;
    }

    if (FAILED(Easy.Initialize()))
    {
        return E_FAIL;
    }

    if (FAILED(Hard.Initialize()))
    {
        return E_FAIL;
    }

    if (FAILED(Normal.Initialize()))
    {
        return E_FAIL;
    }

    if (FAILED(Title.Initialize()))
    {
        return E_FAIL;
    }

    //---BGM再生---//
    SOUND_MANAGER::Play(BGM_SELECT);

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：タイトルの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SELECTSCENE::Uninitialize(void)
{
    //---解放---//
    Back.Uninitialize();
    Easy.Uninitialize();
    Hard.Uninitialize();
    Normal.Uninitialize();
    Title.Initialize();

    //---BGM停止---//
    SOUND_MANAGER::Stop(BGM_SELECT);
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：タイトルの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SELECTSCENE::Update(void)
{
    //---オブジェクトの更新---//
    Back.Update();
    Easy.Update();
    Hard.Update();
    Normal.Update();
    Title.Update();
}