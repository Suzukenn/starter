//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameScene_2.h"
#include "InputManager.h"
#include "RetryButton.h"
#include "SceneManager.h"
#include "SoundManager.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define FILE_PATH L"Data/Game/bg.png" //パス名

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：ゲームシーンの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAME_2::Draw(void)
{
	Back.Draw();
	//プレイヤーの描画処理
	Player.Draw();
	//マウスカーソルの描画処理
	Operation.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ゲームシーンの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT GAME_2::Initialize(void)
{
	//---オブジェクトの初期化---//
	if (FAILED(Back.Initialize(FILE_PATH)))
	{
		return E_FAIL;
	}
	//プレイヤーの初期化
	Player.Initialize();
	//マウスカーソルの初期化
	Operation.Initialize();

    //---BGM再生---//
    SOUND_MANAGER::Play(BGM_GAME);

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ゲームシーンの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAME_2::Uninitialize(void)
{
    //---各種解放---//
	Operation.Uninitialize();
	Player.Uninitialize();
	Back.Uninitialize();
    //---BGM停止---//
    SOUND_MANAGER::Stop(BGM_GAME);
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ゲームシーンの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAME_2::Update(void)
{
	//---オブジェクトの更新---//
	//マウスカーソルの更新処理
	Operation.Update();
	//プレイヤーの更新処理
	Player.Update();
	Back.Update();

    //---画面遷移---//
    if (INPUT_MANAGER::GetKey(DIK_A, TRIGGER))
    {
		//リトライ先のセット
		RETRYBUTTON::SetRetryScene(SCENE_GAME_2);
		//シーン切替
        SCENE_MANAGER::SetScene(SCENE_GAMEOVER);
    }
}