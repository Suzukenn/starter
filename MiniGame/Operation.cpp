//
//	Operation.cpp
//

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "Operation.h"

//======定数・マクロ定義=====
// パス名
#define FILE_PATH	L"Data/Game/hand.png"

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

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：操作ポインタの描画
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
    pDevice->SetTexture(0, Graphic);                              //テクスチャ設定

    // 頂点配列によるポリゴン描画
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertex, sizeof(VERTEX));
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：操作ポインタの初期化
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
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);

	//値の設定
	for (nCounter = 0; nCounter < 4; nCounter++)
	{
        Vertex[nCounter].U = (float)(nCounter & 1);
        Vertex[nCounter].V = (float)((nCounter >> 1) & 1);
        Vertex[nCounter].Position.x = Vertex[nCounter].U * OPERATION_WIDTH + Pos.x;
        Vertex[nCounter].Position.y = Vertex[nCounter].V * OPERATION_HEIGHT + Pos.y;
        Vertex[nCounter].Position.z = 0.0F;
        Vertex[nCounter].RHW = 1.0F;
        Vertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	//バッファのポインタの解放
	VertexBuffer->Unlock();

	return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：操作ポインタの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void OPERATION::Uninitialize(void)
{
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(Graphic);
    Vertex = nullptr;
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：操作ポインタの更新
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
        Vertex[i].Position.x = Pos.x + (i & 1) * OPERATION_WIDTH - OPERATION_WIDTH / 2;
        Vertex[i].Position.y = Pos.y + (i >> 1) * OPERATION_HEIGHT - OPERATION_HEIGHT / 2;
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