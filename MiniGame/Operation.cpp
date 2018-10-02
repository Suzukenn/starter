//
//	Operation.cpp
//

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"
#include "Operation.h"

//======定数・マクロ定義=====
// パス名
#define FILE_PATH	L"Data/Game/hand.png"
//プレイヤーサイズ
#define OPERATION_WIDTH	(30)	//幅
#define OPERATION_HEIGHT	(30)	//高さ
//#define OPERATION_HITBOX_WIDTH		(50)
//#define OPERATION_HITBOX_HEIGHT	(64)
//円判定用
#define OPERATION_RADIUS	(30)

//=====コンストラクタ=====
OPERATION::OPERATION()
{
	//位置設定
	Pos.x = 0.0f;
	Pos.y = 0.0f;
}

//=====デストラクタ=====
OPERATION::~OPERATION()
{
	
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：プレイヤーの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT OPERATION::Initialize(void)
{
	//---各種宣言---//
	int nCounter;
	HRESULT hResult;
	LPDIRECT3DDEVICE9 pDevice;

	//---初期化処理---//
	pDevice = GetDevice();

	//---テクスチャの読み込み---//
	hResult = D3DXCreateTextureFromFileW(pDevice, FILE_PATH, &Graphic);
	if (FAILED(hResult))
	{
		MessageBoxW(nullptr, L"ゲーム画面の初期化に失敗しました", FILE_PATH, MB_OK);
		Graphic = nullptr;
		return hResult;
	}

	//---頂点バッファの生成---//
	hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBuffer, nullptr);

	if (FAILED(hResult))
	{
		return hResult;
	}

	//---頂点バッファへの値の設定---//
	//バッファのポインタを取得
	VertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	//値の設定
	for (nCounter = 0; nCounter < 4; nCounter++)
	{
		pVertex[nCounter].U = (float)(nCounter & 1);
		pVertex[nCounter].V = (float)((nCounter >> 1) & 1);
		pVertex[nCounter].Position.x = pVertex[nCounter].U * OPERATION_WIDTH + Pos.x;
		pVertex[nCounter].Position.y = pVertex[nCounter].V * OPERATION_HEIGHT + Pos.y;
		pVertex[nCounter].Position.z = 0.0F;
		pVertex[nCounter].RHW = 1.0F;
		pVertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	//バッファのポインタの解放
	VertexBuffer->Unlock();

	return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：プレイヤーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void OPERATION::Uninitialize(void)
{
	//---解放---//
	if (VertexBuffer)
	{
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}

	if (Graphic)
	{
		Graphic->Release();
		Graphic = nullptr;
	}
}

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：プレイヤーの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void OPERATION::Draw(void)
{
	//---各種宣言---//
	LPDIRECT3DDEVICE9 pDevice;

	//---初期化処理---//
	pDevice = GetDevice();

	//---書式設定---//
	pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX)); //頂点書式設定
	pDevice->SetFVF(FVF_VERTEX);                                  //フォーマット設定
	pDevice->SetTexture(0, Graphic);                                 //テクスチャ設定
																	 
	// 頂点配列によるポリゴン描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(pVertex[0]));
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：プレイヤーの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void OPERATION::Update(void)
{
	//---各種宣言---//
	GetCursorPos(&Pos);									// マウス座標(スクリーン座標)取得
	ScreenToClient(*GethWnd(), &Pos);					// ウィンドウ ローカル座標に変換

	//---座標反映---//
	for (int i = 0; i < 4; ++i)
	{
		pVertex[i].Position.x = Pos.x + (i & 1) * OPERATION_WIDTH - OPERATION_WIDTH / 2;
		pVertex[i].Position.y = Pos.y + (i >> 1) * OPERATION_HEIGHT - OPERATION_HEIGHT / 2;
	}
}

/////////////////////////////////////////////
//関数名：GetMousePos
//
//機能：マウスの座標のゲッター
//
//引数：なし
//
//戻り値：(D3DXVECTOR2*)マウスカーソルの位置ポインタ
/////////////////////////////////////////////
POINT* OPERATION::GetMousePos(void)
{
	return &Pos;
}
