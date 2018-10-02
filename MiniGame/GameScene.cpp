//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"

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
    //---オブジェクトの描画---//
	Back.Draw();
	Player.Draw();	    //プレイヤー
    Operation.Draw();	//マウスカーソル
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
    //背景
	if (FAILED(Back.Initialize(L"Data/Game/BackGround.tga")))
	{
		return E_FAIL;
	}
	//プレイヤー
    if (FAILED(Player.Initialize()))
    {
        return E_FAIL;
    }

	//マウスカーソル
    if (FAILED(Operation.Initialize()))
    {
        return E_FAIL;
    }

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
    Back.Uninitialize();
	Operation.Uninitialize();
	Player.Uninitialize();

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
    //背景
    Back.Update();
	Operation.Update(); 	//マウスカーソル
	Player.Update();	//プレイヤー

    //---画面遷移---//
    if (INPUT_MANAGER::GetKey(DIK_A, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_GAMEOVER);
    }
}