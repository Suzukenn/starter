#ifndef _GAME_SCENE_2_H_
#define _GAME_SCENE_2_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"
#include "Operation.h"
#include "Player.h"

//＝＝＝クラス宣言＝＝＝//
class GAME_2 final : public BASE_SCENE
{
    private:
		BACKGROUND Back;
		OPERATION Operation;
		PLAYER Player;

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif