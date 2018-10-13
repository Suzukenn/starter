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
    Operation.Draw();
    Player.Draw();
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
    if (FAILED(Player.Initialize(0)))
    {
        return E_FAIL;
    }

	//マウスカーソル
    if (FAILED(Operation.Initialize()))
    {
        return E_FAIL;
    }

    //カメラ
    if (FAILED(Camera.Initialize({ 400.0F, 10.0F })))
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
	Operation.Uninitialize();
    Player.Uninitialize();
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
	Back.Update();
    Camera.Update();
    Operation.Update();
    Player.Update(0, !Timer.GetCheck());
    Timer.Update();

    //---当たり判定---//
    Player.SetHit(Camera.CheckPlayer(Player.GetPos(), Player.GetSize()));

    //---画面遷移---//
    if (!Timer.GetTime())
    {
        if (!Timer.GetCheck())
        {
            Timer.SetTime(CHECK_TIME);
            Timer.SetCheck(true);
        }
        else
        {
            if (Player.GetHit())
            {
                SCENE_MANAGER::SetScene(SCENE_GAMEOVER);
            }
            else
            {
                SCENE_MANAGER::SetScene(SCENE_GAMECLEAR);
            }
        }
    }
}