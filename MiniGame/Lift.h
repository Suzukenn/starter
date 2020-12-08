#ifndef _LIFT_H_
#define _LIFT_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "DeadAngle.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class LIFT
{
    private:
        D3DXVECTOR2 Position;                 //位置
        D3DXVECTOR2 Size;                     //位置
        D3DXVECTOR2 Center;                   //画像中心位置
        LPDIRECT3DTEXTURE9 Graphic;           //テクスチャ
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //頂点バッファ
        VERTEX* Vertex;
        DEADANGLE DeadAngle;

    public:
        bool CheckDeadAngle(D3DXVECTOR2, D3DXVECTOR2);
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(D3DXVECTOR2);
        void Update(void);

        D3DXVECTOR2 GetCenter(void) { return Center; }
        D3DXVECTOR2 GetPos(void) { return Position; }
        D3DXVECTOR2 GetSize(void) { return Size; }
};

#endif