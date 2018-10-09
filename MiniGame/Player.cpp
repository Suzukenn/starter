//
//	Player.cpp
//

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "Player.h"

//======定数・マクロ定義=====
// パス名
#define FILE_PATH	L"Data/Game/PlayerGirl.png"
//プレイヤーサイズ
#define PLAYER_WIDTH	(64)	//幅
#define PLAYER_HEIGHT	(64)	//高さ
//円判定用
#define PLAYER_RADIUS	(30)
//重力
#define VAL_GRAVITY     (0.09f)  //重力
//テクスチャ分割数
#define PLAYER_DIV_U	(2)		//横分割数
#define PLAYER_DIV_V	(2)		//縦分割数
//アニメーションのパターン数
#define PLAYER_ANIM_PAT

//＝＝＝グローバル宣言＝＝＝//
//アニメーションパターン
static ANIM_PAT g_animPat[][3] = {
	{ { 0,  30 },{ 2,  30 },{ -1, -1 } },
	{ { 1,  15 },{ 3,  15 },{ -1, -1 } },
};


//=====コンストラクタ=====
PLAYER::PLAYER()
{
	//動的確保
<<<<<<< HEAD
	Operation = new OPERATION();
	//各初期化
	Pos.x	= SCREEN_CENTER_X;
	Pos.y	= SCREEN_CENTER_Y;
	Anim	= 0;
	AnimPat = 0;
	AnimCnt = 0;
=======
    Operation = new OPERATION();
	//位置設定
	Pos.x = SCREEN_CENTER_X;
	Pos.y = SCREEN_CENTER_Y;
    Size.x = 50.0F;
    Size.y = 50.0F;
    Hit = false;
>>>>>>> 7d89c597109ed6004bd3f05ead395712797e4aa4
}

//=====デストラクタ=====
PLAYER::~PLAYER()
{
	//解放
	delete Operation;
    Operation = nullptr;
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
void PLAYER::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---書式設定---//
    //pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX)); //頂点書式設定
    pDevice->SetFVF(FVF_VERTEX);                                  //フォーマット設定
    pDevice->SetTexture(0, Graphic);                              //テクスチャ設定

    // 頂点配列によるポリゴン描画                                                               
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertex, sizeof(VERTEX));
}

/////////////////////////////////////////////
//関数名：SetPlayerAnimFrame
//
//機能：プレイヤーのアニメーションフレーム設定
//
//引数：(int)現在のアニメーションフレーム
//
//戻り値：なし
/////////////////////////////////////////////
void PLAYER::SetPlayerAnimFrame(int nFrame)
{
	float fU = (nFrame % PLAYER_DIV_U) * (1.0f / PLAYER_DIV_U);
	float fV = (nFrame / PLAYER_DIV_U) * (1.0f / PLAYER_DIV_V);

	for (int i = 0; i < 4; ++i)
	{
		pVertex[i].U = fU + (i % 2) * (1.0f / PLAYER_DIV_U);
		pVertex[i].V = fV + (i / 2) * (1.0f / PLAYER_DIV_V);
	}
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
HRESULT PLAYER::Initialize(void)
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
		MessageBoxW(nullptr, L"プレイヤーのテクスチャを読み込めませんでした", FILE_PATH, MB_OK);
		Graphic = nullptr;
		return hResult;
	}

	//---頂点バッファの生成---//
	hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBuffer, nullptr);

	if (FAILED(hResult))
	{
        MessageBoxW(nullptr, L"頂点バッファの生成に失敗しました", L"初期化エラー", MB_OK);
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
        Vertex[nCounter].Position.x = Vertex[nCounter].U * PLAYER_WIDTH + Pos.x;
        Vertex[nCounter].Position.y = Vertex[nCounter].V * PLAYER_HEIGHT + Pos.y;
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
//機能：プレイヤーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void PLAYER::Uninitialize(void)
{
    Operation->Uninitialize();

	//---解放---//
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(Graphic);
    Vertex = nullptr;
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
void PLAYER::Update(void)
{
	//----- 各種宣言 -----//
	POINT* MousePos = Operation->GetMousePos();
	GetCursorPos(MousePos);										// マウス座標(スクリーン座標)取得
	ScreenToClient(*GethWnd(), MousePos);						// ウィンドウ ローカル座標に変換

	//----- 移動量への影響を反映 -----//
	Move.y += VAL_GRAVITY;

	//----- マウスカーソルとの当たり判定 -----//
	if (INPUT_MANAGER::GetMouseButton(BUTTON_LEFT, HOLD) &&
		(Pos.x - MousePos->x) * (Pos.x - MousePos->x) + (Pos.y - MousePos->y) * (Pos.y - MousePos->y) <= 
		(PLAYER_RADIUS + 20) * (PLAYER_RADIUS + 20))
	{
		//ポジションの更新
		Pos.x = MousePos->x;
		Pos.y = MousePos->y;
		//重力の無効
		Move.y = 0.0f;
		//掴まれたアニメーション
		Anim = 1;
	}
	else
	{
		//通常アニメーション
		Anim = 0;
	}
	//-----アニメーション-----//
	//アニメーション更新
	++AnimCnt;
	if (AnimCnt >= g_animPat[Anim][AnimPat].Count)
	{
		AnimCnt = 0;
		++AnimPat;

		if (g_animPat[Anim][AnimPat].Frame < 0)
		{
			AnimPat = 0;
		}
	}
	// アニメーション設定
	SetPlayerAnimFrame(g_animPat[Anim][AnimPat].Frame);

	//----- 座標反映 -----//
	for (int i = 0; i < 4; ++i)
	{
        Vertex[i].Position.x = Pos.x + (i & 1) * PLAYER_WIDTH - PLAYER_WIDTH / 2;
        Vertex[i].Position.y = Pos.y + (i >> 1) * PLAYER_HEIGHT - PLAYER_HEIGHT / 2;

        //---当たり判定---//
        if (INPUT_MANAGER::GetMouseButton(BUTTON_LEFT, HOLD))
        {
            Vertex[i].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
            continue;
        }

        if (Hit)
        {
            Vertex[i].Diffuse = D3DCOLOR_ARGB(128, 255, 255, 255);
        }
        else
        {
            Vertex[i].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
        }
	}

	//----- 位置情報更新 -----//
	Pos.x += Move.x;
	Pos.y += Move.y;

	//----- 移動範囲制限 -----//
	if (Pos.x + PLAYER_WIDTH / 2.0f > SCREEN_WIDTH)			//右端
	{
		Pos.x = SCREEN_WIDTH - PLAYER_WIDTH / 2.0f;
	}
	else if (Pos.x - PLAYER_WIDTH / 2.0f < 0)				//左端
	{
		Pos.x = PLAYER_WIDTH / 2.0f;
	}
	if (Pos.y > SCREEN_HEIGHT - PLAYER_HEIGHT / 2)			//下端
	{
		Pos.y = SCREEN_HEIGHT - PLAYER_HEIGHT / 2;
		Move.y = 0.0f;
	}
}