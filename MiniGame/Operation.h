//
//	Operation.h
//
#pragma once

#ifndef _OPERATION_H_
#define _OPERATION_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class OPERATION
{
	private:
		POINT Pos;								//マウスのの位置
		LPDIRECT3DTEXTURE9 Graphic;				//テクスチャ
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//頂点バッファ
		VERTEX* Vertex;

	public:
		OPERATION();
		~OPERATION();

		//===プロトタイプ宣言===
		HRESULT Initialize(void);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);
		POINT* GetMousePos(void);
};

#endif