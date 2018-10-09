//
//	RetryButton.h
//
#pragma once

#ifndef _RETRYBUTTON_H_
#define _RETRYBUTTON_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "Operation.h"
#include "SceneManager.h"

//＝＝＝クラス宣言＝＝＝//
class RETRYBUTTON
{
	private:
		D3DXVECTOR2 Pos;						//プレイヤーの位置
		LPDIRECT3DTEXTURE9 Graphic;				//テクスチャ
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//頂点バッファ
		VERTEX* pVertex;
		OPERATION* Operation;					//マウスカーソル情報
		static SCENE RetryScene;				//リトライ先のシーン

	public:
		RETRYBUTTON();
		~RETRYBUTTON();

		//===プロトタイプ宣言===
		HRESULT Initialize(void);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

		static void SetRetryScene(SCENE);		//リトライ先のセット
};

#endif