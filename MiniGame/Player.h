//
//	Player.h
//
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "Operation.h"

//＝＝＝クラス宣言＝＝＝//
class PLAYER
{
	private:
		D3DXVECTOR2 Pos;						//プレイヤーの位置
		D3DXVECTOR2 Move;						//プレイヤーの重力用
        D3DXVECTOR2 Size;
		LPDIRECT3DTEXTURE9 Graphic;				//テクスチャ
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//頂点バッファ
		VERTEX* Vertex;
		OPERATION* Operation;
        bool Hit;

	public:
		PLAYER();
		~PLAYER();

		//===プロトタイプ宣言===
		HRESULT Initialize(void);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        D3DXVECTOR2 GetPos(void) { return Pos; }
        D3DXVECTOR2 GetSize(void) { return Size; }

        void SetHit(bool hit) { Hit = hit; }
};

#endif