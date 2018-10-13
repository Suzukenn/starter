//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Camera.h"
#include "GameScene3.h"
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
void GAME_3::Draw(void)
{
    //---オブジェクトの描画---//
    Back.Draw();
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        Camera[i].Draw();
    }
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
HRESULT GAME_3::Initialize(void)
{
    //---各種宣言---//
    const D3DXVECTOR2 CameraPos[MAX_CAMERA] = { { 200.0F,10.0F },{ 600.0F,10.0F } };

    //---オブジェクトの初期化---//
    //背景
    if (FAILED(Back.Initialize(L"Data/Game/BackGround3.jpg")))
    {
        return E_FAIL;
    }

    //プレイヤーの初期化
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        if (FAILED(Player[i].Initialize(i)))
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
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        if (FAILED(Camera[i].Initialize(CameraPos[i])))
        {
            return E_FAIL;
        }
    }

    //リフト
    if (FAILED(Lift.Initialize({ 600.0F, 300.0F })))
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
void GAME_3::Uninitialize(void)
{
    //---各種解放---//
    Back.Uninitialize();
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        Camera[i].Uninitialize();
    }
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
void GAME_3::Update(void)
{
    //---オブジェクトの更新---//
    Operation.Update();
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        Player[i].Update(i);
    }
    Back.Update();
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        Camera[i].Update();
    }
    Lift.Update();
    Timer.Update();

    for (int i = 0; i < MAX_PLAYER; i++)
    {
        for (int j = 0; j < MAX_CAMERA; j++)
        {
            Player[i].SetHit(Camera[j].CheckPlayer(Player[i].GetPos(), Player[i].GetSize()));
        }
    }

    //---画面遷移---//
    if (!Timer.GetTime())
    {
        for (int i = 0; i < MAX_PLAYER; i++)
        {
            if (Player[i].GetHit())
            {
                SCENE_MANAGER::SetScene(SCENE_GAMEOVER);
                return;
            }
        }
        SCENE_MANAGER::SetScene(SCENE_GAMECLEAR);
    }
}