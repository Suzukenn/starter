#ifndef _DEADANGLE_H_
#define _DEADANGLE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class DEADANGLE
{
    private:
        D3DXVECTOR2 Position[4];
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //頂点バッファ
        VERTEX* Vertex;

    public:
        bool CheckPlayer(D3DXVECTOR2, D3DXVECTOR2);
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(D3DXVECTOR2);
        void Update(void);

        void SetData(D3DXVECTOR2 position, float rad) { Position[0] = position; Angle = rad; }
};

#endif