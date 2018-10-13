#ifndef _CAMERA_H_
#define _CAMERA_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Collision.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class CAMERA
{
    protected:
        D3DXVECTOR2 Position;                 //位置
        D3DXVECTOR2 Center;                   //画像中心位置
		LPDIRECT3DTEXTURE9 Graphic;           //テクスチャ
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //頂点バッファ
		VERTEX* Vertex;
		LPDIRECT3DTEXTURE9 GraphicRoot;           //テクスチャ
		LPDIRECT3DVERTEXBUFFER9 VertexBufferRoot; //頂点バッファ
		VERTEX* VertexRoot;
		COLLISION Collision;

    public:
        virtual bool CheckPlayer(D3DXVECTOR2, D3DXVECTOR2);
        virtual void Draw(void);
        virtual void Uninitialize(void);
        virtual HRESULT Initialize(D3DXVECTOR2);
        virtual void Update(void);
};

#endif