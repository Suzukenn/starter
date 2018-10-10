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
    Operation.Draw();
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        //プレイヤーの描画処理
        Player[i].Draw();
    }
    Timer.Draw();
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

    //プレイヤーの初期化
	for (int i = 0; i < MAX_PLAYER; i++)
	{
        if (FAILED(Player[i].Initialize()))
        {
            return E_FAIL;
        }
    }
	//マウスカーソルの初期化
	Operation.Initialize();

	//マウスカーソル
    if (FAILED(Operation.Initialize()))
    {
        return E_FAIL;
    }

    //カメラ
    if (FAILED(Camera.Initialize({ 400.0F, 10.0F }, 45.0F)))
    {
        return E_FAIL;
    }

    //リフト
    if (FAILED(Lift.Initialize({ 600.0F, 300.0F }, { 150.0F, 30.0F })))
    {
        return E_FAIL;
    }

    //タイマー
    if (FAILED(Timer.Initialize()))
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
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		Player[i].Uninitialize();
	}
	Back.Uninitialize();
    Timer.Uninitialize();

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
		Player[i].Update();
	}
	Back.Update();
    Camera.Update();
    Lift.Update();
    Timer.Update();

    //Player.SetHit(Camera.CheckPlayer(Player.GetPos(), Player.GetSize()));

    //---画面遷移---//
    if (!Timer.GetTime())
    {
        SCENE_MANAGER::SetScene(SCENE_GAME_2);
    }
}