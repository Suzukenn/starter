#ifndef _TITLE_H_
#define _TITLE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"
#include "StartButton.h"

//＝＝＝クラス宣言＝＝＝//
class TITLE final: public BASE_SCENE
{
    private:
		BACKGROUND Back;
		STARTBUTTON Start_B;

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif