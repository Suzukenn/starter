//
//	Player.h
//
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "Operation.h"

//=====マクロ定数定義=====
#define MAX_PLAYER (2)

//＝＝＝構造体定義＝＝＝//
typedef struct _ANIM_PAT {
	int Frame;		//パターンNo
	int Count;		//フレーム数	
} ANIM_PAT;

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
<<<<<<< HEAD
		int			Anim;						// モーションNo.0～7
		int			AnimPat;					// パターンNo.0～2
		int			AnimCnt;					// フレーム数0～15
=======
        bool Hit;
>>>>>>> 7d89c597109ed6004bd3f05ead395712797e4aa4

	public:
		PLAYER();
		~PLAYER();

		//===プロトタイプ宣言===
		HRESULT Initialize(void);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

<<<<<<< HEAD
		void SetPlayerAnimFrame(int);

=======
        D3DXVECTOR2 GetPos(void) { return Pos; }
        D3DXVECTOR2 GetSize(void) { return Size; }

        void SetHit(bool hit) { Hit = hit; }
>>>>>>> 7d89c597109ed6004bd3f05ead395712797e4aa4
};

#endif