//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Camera.h"
#include "GameScene.h"
#include "InputManager.h"
#include "Lift.h"
#include "SceneManager.h"
#include "SoundManager.h"

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
    Camera.Draw();
    Lift.Draw();
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

    //カメラ
    if (FAILED(Camera.Initialize()))
    {
        return E_FAIL;
    }

    //リフト
    if (FAILED(Lift.Initialize({ 600.0F, 300.0F }, { 150.0F, 30.0F })))
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
    Camera.Uninitialize();
    Lift.Uninitialize();
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
    Back.Update();      //背景
    Camera.Update();
    Lift.Update();
	Operation.Update(); //マウスカーソル
	Player.Update();	//プレイヤー

    Player.SetHit(Camera.CheckPlayer(Player.GetPos(), Player.GetSize()));

    //---画面遷移---//
    if (INPUT_MANAGER::GetKey(DIK_SPACE, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_GAMEOVER);
    }
}