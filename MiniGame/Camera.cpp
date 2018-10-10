//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Camera.h"
#include "Main.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define FILE_CAMERAPATH L"Data/Game/Camera.tga" //パス名
#define FILE_ROOTCAMERA L"Data/Game/RootCamera.tga" //パス名
#define SIZE 50.0F

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：CheckDeadAngle
//
//機能：プレイヤーの死角内判定
//
//引数：なし
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool CAMERA::CheckDeadAngle(D3DXVECTOR2 player_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 lift_pos, D3DXVECTOR2 lift_size)
{
    //---各種宣言---//
    bool bJudge;
    D3DXVECTOR2 vecDifferential;

    vecDifferential = lift_size - Position;
    return false;
}

/////////////////////////////////////////////
//関数名：CheckPlayer
//
//機能：プレイヤーの視野角内判定
//
//引数：(D3DXVECTOR2)プレイヤーの位置,(D3DXVECTOR2)プレイヤーの大きさ
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool CAMERA::CheckPlayer(D3DXVECTOR2 player_pos, D3DXVECTOR2 size)
{
    return Collision.CheckPlayer(player_pos, size);
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：カメラの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void CAMERA::Draw(void)
{
    //---当たり判定描画---//
    Collision.Draw();

    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---当たり判定の描画---//
    Collision.Draw();

    //---書式設定---//
	pDevice->SetFVF(FVF_VERTEX);       //フォーマット設定

    //---カメラ支柱描画---//
    pDevice->SetTexture(0, GraphicRoot);   //テクスチャ設定
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, VertexRoot, sizeof(VERTEX));

    //---カメラ描画---//
	pDevice->SetTexture(0, Graphic);   //テクスチャ設定
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertex, sizeof(VERTEX));
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：カメラの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT CAMERA::Initialize(D3DXVECTOR2 position, float angle)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();
    Position = position;
    Center = { SIZE / 2, SIZE / 2 };
    Angle = angle;

    //---テクスチャの読み込み---//
    hResult = D3DXCreateTextureFromFileW(pDevice, FILE_CAMERAPATH, &Graphic);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"カメラテクスチャの取得に失敗しました", FILE_CAMERAPATH, MB_OK);
        Uninitialize();
        return hResult;
    }

    //---頂点バッファの生成---//
	hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBuffer, nullptr);

	if (FAILED(hResult))
	{
		MessageBoxW(nullptr, L"頂点バッファの生成に失敗しました", FILE_CAMERAPATH, MB_OK);
		Uninitialize();
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
		Vertex[nCounter].Position.x = Position.x + Vertex[nCounter].U * SIZE;
		Vertex[nCounter].Position.y = Position.y + Vertex[nCounter].V * SIZE;
		Vertex[nCounter].Position.z = 0.0F;
		Vertex[nCounter].RHW = 1.0F;
		Vertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

    //バッファのポインタの解放
    VertexBuffer->Unlock();

	//---テクスチャの読み込み---//
	hResult = D3DXCreateTextureFromFileW(pDevice, FILE_ROOTCAMERA, &GraphicRoot);
	if (FAILED(hResult))
	{
		MessageBoxW(nullptr, L"カメラの支柱のテクスチャの取得に失敗しました", FILE_ROOTCAMERA, MB_OK);
		Uninitialize();
		return hResult;
	}

	//---頂点バッファの生成---//
	hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBufferRoot, nullptr);

	if (FAILED(hResult))
	{
		MessageBoxW(nullptr, L"頂点バッファの生成に失敗しました", FILE_ROOTCAMERA, MB_OK);
		Uninitialize();
		return hResult;
	}

	//---頂点バッファへの値の設定---//
	//バッファのポインタを取得
	VertexBufferRoot->Lock(0, 0, (void**)&VertexRoot, 0);

	//値の設定
	for (nCounter = 0; nCounter < 4; nCounter++)
	{
		VertexRoot[nCounter].U = (float)(nCounter & 1);
		VertexRoot[nCounter].V = (float)((nCounter >> 1) & 1);
		VertexRoot[nCounter].Position.x = Vertex[nCounter].Position.x - 26.5F;
		VertexRoot[nCounter].Position.y = Vertex[nCounter].Position.y + 10.0F;
		VertexRoot[nCounter].Position.z = 0.0F;
		VertexRoot[nCounter].RHW = 1.0F;
		VertexRoot[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	//バッファのポインタの解放
	VertexBufferRoot->Unlock();

	//当たり判定の初期化
    hResult = Collision.Initialize();
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"カメラの初期化に失敗しました", L"当たり判定", MB_OK);
        Uninitialize();
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：カメラの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void CAMERA::Uninitialize(void)
{
    Collision.Uninitialize();

    //---解放---//
	SAFE_RELEASE(VertexBuffer);
	SAFE_RELEASE(Graphic);
	SAFE_RELEASE(VertexBufferRoot);
	SAFE_RELEASE(GraphicRoot);
	Vertex = nullptr;
	VertexRoot = nullptr;
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：カメラの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void CAMERA::Update(void)
{
    //---各種宣言---//
    int nCounter;
    float fCosine;
    float fDx;
    float fDy;
    float fSin;

    fCosine = cosf(D3DXToRadian(Angle));
    fSin = sinf(D3DXToRadian(Angle));

    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        fDx = (nCounter % 2) * SIZE - Center.x;
        fDy = (nCounter / 2) * SIZE - Center.y;

        Vertex[nCounter].Position.x = (Position.x + (fDx * fCosine - fDy * fSin)) + SIZE / 2;
        Vertex[nCounter].Position.y = (Position.y + (fDx * fSin + fDy * fCosine)) + SIZE / 2;
    }

    Collision.SetData(Position + Center, Angle);
    Collision.Update();
}