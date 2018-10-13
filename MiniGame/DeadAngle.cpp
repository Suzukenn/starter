//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "DeadAngle.h"
#include "Main.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define VIEW_ANGLE 15.0F

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：CheckDeadAngle
//
//機能：プレイヤーの死角内判定
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
bool DEADANGLE::CheckDeadAngle(D3DXVECTOR2 player_pos, D3DXVECTOR2 size)
{
    //---各種宣言---//
    int nCounter;
    double dCorner1;
    double dCorner2;
    double dCorner3;
    double dCorner4;
    D3DXVECTOR2 vecAB;
    D3DXVECTOR2 vecBC;
    D3DXVECTOR2 vecCD;
    D3DXVECTOR2 vecDA;
    D3DXVECTOR2 vecAP;
    D3DXVECTOR2 vecBP;
    D3DXVECTOR2 vecCP;
    D3DXVECTOR2 vecDP;

    D3DXVECTOR2 vecPlayerVertex[4];

    //---初期化処理---//
    vecPlayerVertex[0] = player_pos;
    vecPlayerVertex[1] = { player_pos.x + size.x, player_pos.y };
    vecPlayerVertex[2] = player_pos + size;
    vecPlayerVertex[3] = { player_pos.x, player_pos.y + size.y };

    //---判定---//
    for (nCounter = 0; nCounter < 4; nCounter++)
    {
        //方向ベクトル計算
        vecAB = Position[0] - Position[1];
        vecBP = vecPlayerVertex[nCounter] - Position[0];

        vecBC = Position[1] - Position[2];
        vecCP = vecPlayerVertex[nCounter] - Position[1];

        vecCD = Position[2] - Position[3];
        vecDP = vecPlayerVertex[nCounter] - Position[2];

        vecCD = Position[3] - Position[0];
        vecAP = vecPlayerVertex[nCounter] - Position[3];

        //外積の計算
        dCorner1 = vecAB.x * vecBP.y - vecAB.y * vecBP.x;
        dCorner2 = vecBC.x * vecCP.y - vecBC.y * vecCP.x;
        dCorner3 = vecCD.x * vecDP.y - vecCD.y * vecDP.x;
        dCorner4 = vecDA.x * vecAP.y - vecDA.y * vecAP.x;

        //判定
        if ((dCorner1 > 0 && dCorner2 > 0 && dCorner3 > 0 && dCorner4 > 0) || (dCorner1 < 0 && dCorner2 < 0 && dCorner3 < 0 && dCorner4 < 0))
        {
            return true;
        }
    }

    return false;
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：死角の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void DEADANGLE::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---書式設定---//
    pDevice->SetFVF(FVF_VERTEX);       //フォーマット設定
    pDevice->SetTexture(0, Graphic);   //テクスチャ設定

    //---描画---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertex, sizeof(VERTEX));
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：死角の初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT DEADANGLE::Initialize(void)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---テクスチャの読み込み---//
    hResult = D3DXCreateTextureFromFileW(pDevice, L"Data/Game/BackGround.png", &Graphic);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"死角用背景の初期化に失敗しました", L"Data/Game/BackGround.png", MB_OK);
        Uninitialize();
        return hResult;
    }

    //---頂点バッファの生成---//
    hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBuffer, nullptr);

    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"頂点バッファの生成に失敗しました", L"エラー", MB_OK);
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
        Vertex[nCounter].Position.x = 0.0F;
        Vertex[nCounter].Position.y = 0.0F;
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
//機能：死角の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void DEADANGLE::Uninitialize(void)
{
    //---解放---//
    SAFE_RELEASE(Graphic);
    SAFE_RELEASE(VertexBuffer);
    Vertex = nullptr;
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：死角の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void DEADANGLE::Update(void)
{
    //---各種宣言---//
    int nCounter;
    float fWidth1;
    float fWidth2;

    const short nRate[2] = { -1,1 };

    //---初期化処理---//

    //---頂点の算出---//
    for (nCounter = 1; nCounter < 4; nCounter++)
    {
        Position[nCounter].x = Position[0].x + nRate[nCounter & 1] * Size.x;
        Position[nCounter].y = Position[0].y + nRate[nCounter >> 1] * Size.y;
    }

    //---バッファに反映---//
    for (nCounter = 0; nCounter < 3; nCounter++)
    {
        Vertex[nCounter].Position = { Position[nCounter].x, Position[nCounter].y, 0.0F };
        Vertex[nCounter].U = SCREEN_WIDTH / Position[nCounter].x;
        Vertex[nCounter].V = SCREEN_HEIGHT / Position[nCounter].y;
    }
}