//
//	Operation.h
//
#pragma once

#ifndef _OPERATION_H_
#define _OPERATION_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝定数・マクロ定義＝＝＝//
//マウスカーソルサイズ
#define OPERATION_WIDTH			(30)	//幅
#define OPERATION_HEIGHT		(30)	//高さ
//四角判定用
#define OPERATION_HIT_WIDTH		(5)		//幅
#define OPERATION_HIT_HEIGHT	(5)		//高さ
//円判定用
#define OPERATION_RADIUS	(30)

//＝＝＝クラス宣言＝＝＝//
class OPERATION
{
	private:
		POINT Pos;								//マウスのの位置
		LPDIRECT3DTEXTURE9 Graphic;				//テクスチャ
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//頂点バッファ
		VERTEX* pVertex;

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