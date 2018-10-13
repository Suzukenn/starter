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
        D3DXVECTOR2				Pos;			//プレイヤーの位置
        D3DXVECTOR2				Size;			//プレイヤーの大きさ
        D3DXVECTOR2				Move;			//プレイヤーの重力用
		float					Interval;		//プレイヤーの重力用
		bool					Invincible;		//プレイヤーの無敵位置（スタート位置）判定用	
        bool Hit;
		LPDIRECT3DTEXTURE9 Graphic;				//テクスチャ
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//頂点バッファ
		VERTEX* pVertex;
		OPERATION* Operation;
		int			Anim;						// モーションNo.0～7
		int			AnimPat;					// パターンNo.0～2
		int			AnimCnt;					// フレーム数0～15

	public:
		PLAYER();
		~PLAYER();

		//===プロトタイプ宣言===
		HRESULT Initialize(int);
		void Uninitialize(void);
		void Update(int, bool);
		void Draw(void);

        bool GetHit(void) { return Hit; }
        D3DXVECTOR2	GetPos(void) { return Pos; }
        D3DXVECTOR2	GetSize(void) { return Size; }
        void SetHit(bool hit) { Hit = hit; }
		void SetPlayerAnimFrame(int);

};

#endif