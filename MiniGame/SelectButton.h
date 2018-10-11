#ifndef _SELECT_BUTTON_H_
#define _SELECT_BUTTON_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "Operation.h"

//＝＝＝クラス宣言＝＝＝//
class SELECTBUTTON
{
    private:
        D3DXVECTOR2 Pos;						//プレイヤーの位置
        LPDIRECT3DTEXTURE9 Graphic;				//テクスチャ
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//頂点バッファ
        VERTEX* pVertex;
        OPERATION* Operation;					//マウスカーソル情報

    public:
        SELECTBUTTON();
        ~SELECTBUTTON();

        //===プロトタイプ宣言===
        HRESULT Initialize(void);
        void Uninitialize(void);
        void Update(void);
        void Draw(void);
};

#endif