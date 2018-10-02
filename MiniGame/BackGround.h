#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class BACKGROUND
{
	private:
		unsigned int Score;
		LPDIRECT3DTEXTURE9 Graphic;           //テクスチャ
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //頂点バッファ

	public:
		void Draw(void);
		void Uninitialize(void);
		HRESULT Initialize(LPCWSTR);
		void Update(void);
};

#endif