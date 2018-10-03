//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "Lift.h"
#include "Main.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define FILE_PATH L"Data/Game/Lift.tga" //パス名

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：リフトの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void LIFT::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---書式設定---//
    pDevice->SetFVF(FVF_VERTEX);        //フォーマット設定
    pDevice->SetTexture(0, Graphic);    //テクスチャ設定

    //---描画---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertex, sizeof(VERTEX));
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：リフトの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT LIFT::Initialize(D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();
    Position = position;
    Size = size;
    Center = { Position.x + Size.x / 2, Position.y + Size.y / 2 };

    //---テクスチャの読み込み---//
    hResult = D3DXCreateTextureFromFileW(pDevice, FILE_PATH, &Graphic);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"リフトテクスチャの取得に失敗しました", FILE_PATH, MB_OK);
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
        Vertex[nCounter].Position.x = Position.x + Vertex[nCounter].U * Size.x;
        Vertex[nCounter].Position.y = Position.y + Vertex[nCounter].V * Size.y;
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
//機能：リフトの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void LIFT::Uninitialize(void)
{
    //---解放---//
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(Graphic);
    Vertex = nullptr;
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：リフトの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void LIFT::Update(void)
{

}