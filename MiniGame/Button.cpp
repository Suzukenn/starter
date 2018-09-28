//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <math.h>
#include "button.h"

//＝＝＝関数定義＝＝＝//
///////////////////////////////////
//関数名：Draw
//
//機能：ボタンの描画処理
//
//引数：(SPRITE_NORMAL*)座標データ
//
//戻り値：なし
///////////////////////////////////
void BUTTON::Draw(void)
{	
    //---テクスチャの設定---//
    
    //テクスチャの取得
    GXLoadTexObj(GetUITex(Texture), GX_TEXMAP0);

    //---描画---//
    
	//正方形の生成
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    
	//頂点1
	GXPosition2f32(Pos_X, Pos_Y);
	GXColor4u8(255, 255, 255, 255);	
	GXTexCoord2f32(0.0F, 0.0F);
	
	//頂点2
	GXPosition2f32(Pos_X + Width, Pos_Y);
	GXColor4u8(255, 255, 255, 255);	
	GXTexCoord2f32(1.0F, 0.0F);
	
	//頂点3
	GXPosition2f32(Pos_X + Width, Pos_Y + Height);
	GXColor4u8(255, 255, 255, 255);	
	GXTexCoord2f32(1.0F, 1.0F);
	
	//頂点4
	GXPosition2f32(Pos_X, Pos_Y + Height);
	GXColor4u8(255, 255, 255, 255);	
	GXTexCoord2f32(0.0F, 1.0F);
	
    GXEnd();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ボタンの初期化
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BUTTON::Initialize(float x, float y, float width, float height, UI_TEX texture)
{
    Pos_X = x;
    Pos_Y = y;
    Width = width;
    Height = height;
    Texture = texture;
    D_Pos_X = Pos_X;
    D_Pos_Y = Pos_Y;
    D_Width = Width;
	D_Height = Height;
	Push = false;
}

///////////////////////////////////
//関数名：Update
//
//機能：ボタンの更新
//
//引数：なし
//
//戻り値：なし
///////////////////////////////////
void BUTTON::Update(void)
{	
	//---データの公開---//
	D_Pos_X = Pos_X;
    D_Pos_Y = Pos_Y;
    D_Width = Width;
	D_Height = Height;
	
	//---入力状態のリセット---//
	Push = false;
}