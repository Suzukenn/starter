#ifndef _TITLE_H_
#define _TITLE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Base_Scene.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class TITLE final: public BASE_SCENE
{
    private:
        unsigned int Score;
        LPDIRECT3DTEXTURE9 Graphic;           //テクスチャ
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //頂点バッファ

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif