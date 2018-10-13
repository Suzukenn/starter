#ifndef _MANUAL_H_
#define _MANUAL_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"
#include "TitleButton.h"

//＝＝＝クラス宣言＝＝＝//
class MANUAL final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        TITLEBUTTON Title_B;	//タイトルボタン用

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif