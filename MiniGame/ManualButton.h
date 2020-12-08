#ifndef _MANUALBUTTON_H_
#define _MANUALBUTTON_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "Operation.h"

//＝＝＝クラス宣言＝＝＝//
class MANUALBUTTON
{
    private:
        D3DXVECTOR2 Pos;						//プレイヤーの位置
        LPDIRECT3DTEXTURE9 Graphic;				//テクスチャ
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//頂点バッファ
        VERTEX* pVertex;
        OPERATION* Operation;					//マウスカーソル情報

    public:
        MANUALBUTTON();
        ~MANUALBUTTON();

        //===プロトタイプ宣言===
        void Draw(void);
        HRESULT Initialize(void);
        void Uninitialize(void);
        void Update(void);
};

#endif