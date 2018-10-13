//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <cmath>
#include "Main.h"
#include "Timer.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define FILE_PATH L"Data/Game/Number.tga" //パス名
#define SIZE 50.0F					//表示サイズ

//＝＝＝関数定義＝＝＝//
///////////////////////////////////
//関数名：Draw
//
//機能：スコアの描画
//
//引数：なし
//
//戻り値：なし
///////////////////////////////////
void TIMER::Draw(void)
{
    //---各種宣言---//
    int nCounter;
    int nPosLeft;
    int nPosRight;
    float fTexLeft;
    float fTexRight;
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

///////////////////////////////////
//関数名：End
//
//機能：タイマーの削除
//
//引数：なし
//
//戻り値：なし
///////////////////////////////////
void TIMER::Uninitialize(void)
{
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(Graphic);
}

///////////////////////////////////
//関数名：Initialize
//
//機能：タイマーの初期化
//
//引数：なし
//
//戻り値：なし
///////////////////////////////////
HRESULT TIMER::Initialize(void)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;
    D3DXVECTOR2 vecPosition;

    //---初期化処理---//
    vecPosition = { 746.0F, 5.0F };
    Fream = 600;
    Time = 9;
    pDevice = GetDevice();

    //---テクスチャの読み込み---//
    hResult = D3DXCreateTextureFromFileW(pDevice, FILE_PATH, &Graphic);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"カメラテクスチャの取得に失敗しました", FILE_PATH, MB_OK);
        Uninitialize();
        return hResult;
    }

    //---頂点バッファの生成---//
    hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBuffer, nullptr);

    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"頂点バッファの生成に失敗しました", FILE_PATH, MB_OK);
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
        Vertex[nCounter].Position.x = vecPosition.x + Vertex[nCounter].U * SIZE;
        Vertex[nCounter].Position.y = vecPosition.y + Vertex[nCounter].V * SIZE;
        Vertex[nCounter].Position.z = 0.0F;
        Vertex[nCounter].RHW = 1.0F;
        Vertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    //バッファのポインタの解放
    VertexBuffer->Unlock();

    Check = false;

    return hResult;
}

///////////////////////////////////
//関数名：Update
//
//機能：タイマーの更新
//
//引数：なし
//
//戻り値：なし
///////////////////////////////////
void TIMER::Update(void)
{
    //---各種宣言---//
    int nCounter;
    int nDigits;
    int nWork;

    //---各種処理---//

    //残フレームカウント
    if (Fream)
    {
        Fream--;
    }
    nWork = Fream / 60;

    //値代入
    Time = nWork % 10;
    for (nCounter = 0; nCounter < 4; nCounter++)
    {
        Vertex[nCounter].U = (float)(Time + (nCounter & 1)) * 0.1F;
    }

    if (Check)
    {
        for (nCounter = 0; nCounter < 4; nCounter++)
        {
            Vertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 0, 0);
        }
    }
}