#ifndef _SELECTSCENE_H_
#define _SELECTSCENE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"
#include "Stage_EasyButton.h"
#include "Stage_HardButton.h"
#include "Stage_NormalButton.h"
#include "TitleButton.h"

//＝＝＝クラス宣言＝＝＝//
class SELECTSCENE final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        STAGEEASYBUTTON Easy;
        STAGEHARDBUTTON Hard;
        STAGENORMALBUTTON Normal;
        TITLEBUTTON Title;

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif