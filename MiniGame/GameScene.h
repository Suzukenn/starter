#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Camera.h"
#include "Main.h"
#include "Lift.h"
#include "Operation.h"
#include "Player.h"
#include "Timer.h"

//＝＝＝クラス宣言＝＝＝//
class GAME final : public BASE_SCENE
{
    private:
		BACKGROUND Back;
        CAMERA Camera;
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