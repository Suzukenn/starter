#ifndef _CAMERA_H_
#define _CAMERA_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Collision.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class CAMERA
{
    private:
        D3DXVECTOR2 Position;                 //位置
        D3DXVECTOR2 Center;                   //画像中心位置
        float Angle;                          //回転
		LPDIRECT3DTEXTURE9 Graphic;           //テクスチャ
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //頂点バッファ
		VERTEX* Vertex;
		LPDIRECT3DTEXTURE9 GraphicRoot;           //テクスチャ
		LPDIRECT3DVERTEXBUFFER9 VertexBufferRoot; //頂点バッファ
		VERTEX* VertexRoot;
		COLLISION Collision;

        bool CheckInst();

    public:
        bool CheckDeadAngle(D3DXVECTOR2, D3DXVECTOR2, D3DXVECTOR2, D3DXVECTOR2);
        bool CheckPlayer(D3DXVECTOR2, D3DXVECTOR2);
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(D3DXVECTOR2, float);
        void Update(void);
};

#endif