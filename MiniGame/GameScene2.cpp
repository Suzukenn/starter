//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameScene2.h"
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
    //---各種宣言---//
    int nCounter;

    //---オブジェクトの描画---//
    Back.Draw();
    for (nCounter = 0; nCounter < MAX_CAMERA; nCounter++)
    {
        Camera[nCounter].Draw();
    }
    Lift.Draw();
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
HRESULT GAME_2::Initialize(void)
{
    //---各種宣言---//
    int nCounter;

    const D3DXVECTOR2 CameraPos[MAX_CAMERA] = { {200.0F,10.0F},{600.0F,10.0F} };

	//---オブジェクトの初期化---//
    if (FAILED(Back.Initialize(FILE_PATH)))
    {
        return E_FAIL;
    }

    for (nCounter = 0; nCounter < MAX_CAMERA; nCounter++)
    {
        if (FAILED(Camera[nCounter].Initialize(CameraPos[nCounter])))
        {
            return E_FAIL;
        }
    }

    if (FAILED(Lift.Initialize({550.0F,300.0F})))
    {
        return E_FAIL;
    }

    if (FAILED(Operation.Initialize()))
    {
        return E_FAIL;
    }

    if (FAILED(Player.Initialize(0)))
    {
        return E_FAIL;
    }

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
void GAME_2::Uninitialize(void)
{
    //---各種宣言---//
    int nCounter;

    //---各種解放---//
    Back.Uninitialize();
    for (nCounter = 0; nCounter < MAX_CAMERA; nCounter++)
    {
        Camera[nCounter].Uninitialize();
    }
    Lift.Uninitialize();
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
void GAME_2::Update(void)
{
    //---各種宣言---//
    int nCounter;

	//---オブジェクトの更新---//
    Back.Update();
    for (nCounter = 0; nCounter < MAX_CAMERA; nCounter++)
    {
        Camera[nCounter].Update();
    }
    Lift.Update();
    Operation.Update();
    Player.Update(0);
    Timer.Update();

    //---当たり判定---//
    for (nCounter = 0; nCounter < MAX_CAMERA; nCounter++)
    {
        Player.SetHit(Camera[nCounter].CheckPlayer(Player.GetPos(), Player.GetSize()));
    }
    //---画面遷移---//
    if (!Timer.GetTime())
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