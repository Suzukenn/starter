//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Title.h"

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
void TITLE::Draw(void)
{
	Back.Draw();
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
HRESULT TITLE::Initialize(void)
{
	//---オブジェクトの初期化---//
	if (FAILED(Back.Initialize(L"Data/Game/Title.png")))
	{
		return E_FAIL;
	}

    //---BGM再生---//
    SOUND_MANAGER::Play(BGM_OPENING);

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
void TITLE::Uninitialize(void)
{
    //---解放---//
	Back.Uninitialize();

    //---BGM停止---//
    SOUND_MANAGER::Stop(BGM_OPENING);
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
void TITLE::Update(void)
{
	//---オブジェクトの更新---//
    //背景
    Back.Update();

    //---画面遷移---//
    if (INPUT_MANAGER::GetKey(DIK_SPACE, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_GAME);
    }
}