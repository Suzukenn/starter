#ifndef _TIMER_H_
#define _TIMER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define DIGITS 2				//最大表示桁

//＝＝＝クラス宣言＝＝＝//
class TIMER
{
    private:
        int Fream;
        int Time;
        LPDIRECT3DTEXTURE9 Graphic;				        //テクスチャ
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//頂点バッファ
        VERTEX Vertex[4];

    public:
        HRESULT Initialize(void);
        void Uninitialize(void);
        void Update(void);
        void Draw(void);

        int GetTime(void) { return Time; }
};

#endif