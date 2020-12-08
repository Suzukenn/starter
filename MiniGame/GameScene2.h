#ifndef _GAME_SCENE_2_H_
#define _GAME_SCENE_2_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Camera.h"
#include "Lift.h"
#include "Main.h"
#include "Operation.h"
#include "Player.h"
#include "Timer.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define MAX_CAMERA 2

//＝＝＝クラス宣言＝＝＝//
class GAME_2 final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        CAMERA Camera[MAX_CAMERA];
        LIFT Lift;
		OPERATION Operation;
		PLAYER Player;
        TIMER Timer;

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif