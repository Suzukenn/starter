//
//	TitleButton.h
//
#pragma once

#ifndef _TITLEBUTTON_H_
#define _TITLEBUTTON_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "Operation.h"

//＝＝＝クラス宣言＝＝＝//
class TITLEBUTTON
{
	private:
		D3DXVECTOR2 Pos;						//プレイヤーの位置
		LPDIRECT3DTEXTURE9 Graphic;				//テクスチャ
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//頂点バッファ
		VERTEX* pVertex;
		OPERATION* Operation;					//マウスカーソル情報

	public:
		TITLEBUTTON();
		~TITLEBUTTON();

		//===プロトタイプ宣言===
		HRESULT Initialize(void);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void SetPos(D3DXVECTOR2 pos) { Pos = pos; }

};

#endif