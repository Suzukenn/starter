#ifndef _BUTTON_H_
#define _BUTTON_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "Sprite.h"

//＝＝＝クラス定義＝＝＝//
class BUTTON : private SPRITE
{		
	public:
		D3DXVECTOR3 D_Pos;	//位置の公開バッファ
        D3DXVECTOR3 D_Size;	//大きさの公開バッファ
		bool Push;		    //押下判定

		void Draw(void) override;
        void Initialize(D3DXVECTOR3, D3DXVECTOR3, LPCWSTR);
        void Uninitialize(void) override;
		void Update(void);
};

#endif