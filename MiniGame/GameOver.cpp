//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameOver.h"
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
void GAMEOVER::Draw(void)
{
	Back.Draw();
	Retry_B.Draw();
    Select_B.Draw();
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
HRESULT GAMEOVER::Initialize(void)
{
    //---オブジェクトの初期化---//
	if (FAILED(Back.Initialize(L"Data/Game/GameOver.png")))
	{
		return E_FAIL;
	}

    if (FAILED(Retry_B.Initialize()))
    {
        return E_FAIL;
    }

    if (FAILED(Select_B.Initialize()))
    {
        return E_FAIL;
    }

    //---BGM再生---//
    SOUND_MANAGER::Play(BGM_GAMEOVER);

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
void GAMEOVER::Uninitialize(void)
{
    //---解放---//
    Select_B.Uninitialize();
	Retry_B.Uninitialize();
    Back.Uninitialize();
   
    //---BGM停止---//
    SOUND_MANAGER::Stop(BGM_GAMEOVER);
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
void GAMEOVER::Update(void)
{
	//---オブジェクトの更新---//
	Back.Update();
    //---画面遷移---//
	//リトライボタンの更新処理
	Retry_B.Update();
	//タイトルボタンの更新処理
    Select_B.Update();
}