#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "Base_Scene.h"
#include "Main.h"
#include "RetryButton.h"
#include "TitleButton.h"

//＝＝＝クラス宣言＝＝＝//
class GAMEOVER final : public BASE_SCENE
{
    private:
		BACKGROUND Back;
		RETRYBUTTON Retry_B;	//リトライボタン用
		TITLEBUTTON Title_B;	//タイトルボタン用

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif