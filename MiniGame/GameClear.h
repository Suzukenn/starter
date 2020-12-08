#ifndef _GAMECLEAR_H_
#define _GAMECLEAR_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"
#include "SelectButton.h"
#include "RetryButton.h"

//＝＝＝クラス宣言＝＝＝//
class GAMECLEAR final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        RETRYBUTTON Retry_B;	//リトライボタン用
        SELECTBUTTON Select_B;	//セレクトボタン用

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif