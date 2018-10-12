//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define FILE_PATH L"Data/Game/BackGround.tga" //パス名

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
void GAME::Draw(void)
{
	Back.Draw();
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		//プレイヤーの描画処理
		Player[i].Draw();
	}
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
HRESULT GAME::Initialize(void)
{
	//---オブジェクトの初期化---//
	if (FAILED(Back.Initialize(FILE_PATH)))
	{
		return E_FAIL;
	}
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		//プレイヤーの初期化
		Player[i].Initialize(i);
	}
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
void GAME::Uninitialize(void)
{
    //---各種解放---//
	Operation.Uninitialize();
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		Player[i].Uninitialize();
	}
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
void GAME::Update(void)
{
	//---オブジェクトの更新---//
	//マウスカーソルの更新処理
	Operation.Update();
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		//プレイヤーの更新処理
		Player[i].Update(i);
	}
	Back.Update();

    //---画面遷移---//
    if (INPUT_MANAGER::GetKey(DIK_A, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_GAME_2);
    }
}