#ifndef _DEADANGLE_H_
#define _DEADANGLE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class DEADANGLE
{
    private:
        D3DXVECTOR2 Position[4];
        D3DXVECTOR2 Size;
        LPDIRECT3DTEXTURE9 Graphic;           //テクスチャ
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //頂点バッファ
        VERTEX* Vertex;

    public:
        bool CheckDeadAngle(D3DXVECTOR2, D3DXVECTOR2);
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);

        void SetData(D3DXVECTOR2 position, D3DXVECTOR2 size) { Position[0] = position; Size = size; }
};

#endif