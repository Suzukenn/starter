//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"
#include "Title.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define FILE_PATH L"Data/Game/Title.png" //パス名

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：背景とボタンの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TITLE::Draw(void)
{
	Back.Draw();
	Start_B.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：背景とボタンの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT TITLE::Initialize(void)
{
	//---オブジェクトの初期化---//
	if (FAILED(Back.Initialize(FILE_PATH)))
	{
		return E_FAIL;
	}

	//スタートボタンの初期化
	Start_B.Initialize();

    //---BGM再生---//
    SOUND_MANAGER::Play(BGM_OPENING);

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：背景とボタンの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TITLE::Uninitialize(void)
{
    //---解放---//
	Start_B.Uninitialize();
	Back.Uninitialize();

    //---BGM停止---//
    SOUND_MANAGER::Stop(BGM_OPENING);
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：背景とボタンの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TITLE::Update(void)
{
	//---オブジェクトの更新---//
	Start_B.Update();
}