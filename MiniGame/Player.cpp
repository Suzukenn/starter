//
//	Player.cpp
//

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Player.h"

//======定数・マクロ定義=====
// パス名
#define FILE_PATH	L"Data/Game/Player.png"
//プレイヤーサイズ
#define PLAYER_WIDTH	(64)	//幅
#define PLAYER_HEIGHT	(64)	//高さ
#define PLAYER_HITBOX_WIDTH		(50)
#define PLAYER_HITBOX_HEIGHT	(50)
//円判定用
#define PLAYER_RADIUS	(30)
//重力
#define VAL_GRAVITY     (0.09f)  //重力
//テクスチャ分割数
#define PLAYER_DIV_U	(2)		//横分割数
#define PLAYER_DIV_V	(3)		//縦分割数
//アニメーションのパターン数
#define PLAYER_ANIM_PAT

//＝＝＝グローバル宣言＝＝＝//
//アニメーションパターン
static ANIM_PAT g_animPat[][3] = {
    { { 0,  30 },{ 1,  30 },{ -1, -1 } },		//待機モーション
    { { 4,  1 },{ 4,  1 },{ -1, -1 } },			//掴まれるモーション
    { { 2,  1 },{ 2,  1 },{ -1, -1 } },			//落下モーション
    { { 3,  1 },{ 3,  1 },{ -1, -1 } },			//落下モーション
};


//=====コンストラクタ=====
PLAYER::PLAYER()
{
	//動的確保
	Operation = new OPERATION();
	//各初期化
	Interval = 100.0f;
	Anim	= 0;
	AnimPat = 0;
	AnimCnt = 0;
}

//=====デストラクタ=====
PLAYER::~PLAYER()
{
	//解放
	if (Operation)
	{
		delete Operation;
	}
}

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：CheckCollisionLift
//
//機能：プレイヤーとリフトの当たり判定
//
//引数：(D3DXVECTOR2)リフトのポジション, (D3DXVECTOR2)リフトのサイズ
//
//戻り値：なし
/////////////////////////////////////////////
void PLAYER::CheckCollisionLift(D3DXVECTOR2 LiftPos, D3DXVECTOR2 LiftSize)
{
    //----------上判定----------//
    //if (Pos.x + PLAYER_HITBOX_WIDTH / 2 > LiftPos.x &&
    //    Pos.x - PLAYER_HITBOX_WIDTH / 2 < LiftPos.x + LiftSize.x)
    if (Pos.x + PLAYER_HITBOX_WIDTH / 2 > LiftPos.x &&
        Pos.x - PLAYER_HITBOX_WIDTH / 2 < LiftPos.x + LiftSize.x)
    {
        //----- 着地 ------//
        if (Pos.y + PLAYER_HITBOX_HEIGHT / 2 >= LiftPos.y &&
            PosOld.y + PLAYER_HITBOX_HEIGHT / 2 <= LiftPos.y)
        {
            //高さOK
            Pos.y = LiftPos.y - PLAYER_HITBOX_HEIGHT / 2;
            Move.y = 0.0f;			//移動量Y方向リセット
            LiftLanding = true;
            return;
        }
    }
    return;
}

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
    pDevice->SetFVF(FVF_VERTEX);                                  //フォーマット設定
    pDevice->SetTexture(0, Graphic);                               //テクスチャ設定

                                                                   // 頂点配列によるポリゴン描画
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(pVertex[0]));
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
HRESULT PLAYER::Initialize(int num)
{
	//---各種宣言---//
	int nCounter;
	HRESULT hResult;
	LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();
    Invincible = false;
    LiftLanding = false;
    GroundLanding = false;
    Pos.x = PLAYER_WIDTH / 2.0f;
    Pos.y = SCREEN_HEIGHT - PLAYER_HEIGHT / 2.0f - (Interval * num);
    PosOld.x = 0.0f;
    PosOld.y = 0.0f;
    LiftLandCnt = 0;

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
		pVertex[nCounter].Position.x = pVertex[nCounter].U * PLAYER_WIDTH + Pos.x;
		pVertex[nCounter].Position.y = pVertex[nCounter].V * PLAYER_HEIGHT + Pos.y;
		pVertex[nCounter].Position.z = 0.0F;
		pVertex[nCounter].RHW = 1.0F;
		pVertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	//バッファのポインタの解放
	VertexBuffer->Unlock();

	return hResult;
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
	//---解放---//
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(Graphic);
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
void PLAYER::Update(int num, bool move)
{
    //----- 各種宣言 -----//
    POINT* MousePos = Operation->GetMousePos();
    GetCursorPos(MousePos);										// マウス座標(スクリーン座標)取得
    ScreenToClient(*GethWnd(), MousePos);						// ウィンドウ ローカル座標に変換

    PosOld = Pos;

    if (!Invincible)
    {
        //移動量への影響を反映
        Move.y += VAL_GRAVITY;
    }
    else
    {
        //無敵位置（スタート位置）へ
        Pos.x = PLAYER_WIDTH / 2.0f;
        Pos.y = SCREEN_HEIGHT - PLAYER_HEIGHT / 2.0f - (Interval * num);
    }

    //----- マウスカーソルとの当たり判定 -----//
    if (INPUT_MANAGER::GetMouseButton(BUTTON_LEFT, HOLD) &&
        (Pos.x - MousePos->x) * (Pos.x - MousePos->x) + (Pos.y - MousePos->y) * (Pos.y - MousePos->y) <=
        (PLAYER_RADIUS + 20) * (PLAYER_RADIUS + 20))
    {
        if (move)
        {
            //ポジションの更新
            Pos.x = MousePos->x;
            Pos.y = MousePos->y + PLAYER_HEIGHT / 2;
            //重力の無効
            Move.y = 0.0f;
            //掴まれたアニメーション
            Anim = 1;
            //無敵状態を解放
            Invincible = false;
            //着地してない
            LiftLanding = false;
            GroundLanding = false;
        }
    }
    else
    {
        //落下アニメーション
        Anim = 2;
        //待機＆着地アニメーション
        if (GroundLanding || LiftLanding)
        {
            //着地アニメーション
            if (LiftLandCnt > 0)
            {
                Anim = 3;
                LiftLandCnt--;
            }
            //待機アニメーション
            else
            {
                Anim = 0;
            }
        }
        else
        {
            LiftLandCnt = 15;	//0.25秒をセット
        }
        //無敵位置（スタート位置）判定
        if (Pos.x - PLAYER_WIDTH < 30.0f)
        {
            Invincible = true;
            Anim = 0;
        }
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
		pVertex[i].Position.x = Pos.x + (i & 1) * PLAYER_WIDTH - PLAYER_WIDTH / 2;
		pVertex[i].Position.y = Pos.y + (i >> 1) * PLAYER_HEIGHT - PLAYER_HEIGHT / 2;
	}

	//----- 位置情報更新 -----//
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
        GroundLanding = true;
	}
}
