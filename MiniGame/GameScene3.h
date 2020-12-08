#ifndef _GAME_SCENE_3_H_
#define _GAME_SCENE_3_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"
#include "MoveCamera.h"
#include "Lift.h"
#include "Operation.h"
#include "Player.h"
#include "Timer.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define MAX_CAMERA 2
#define MAX_LIFT 2
#define MAX_PLAYER 2

//＝＝＝クラス宣言＝＝＝//
class GAME_3 final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        MOVECAMERA Camera[MAX_CAMERA];
        LIFT Lift[MAX_LIFT];
        OPERATION Operation;
        PLAYER Player[MAX_PLAYER];
        TIMER Timer;

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif