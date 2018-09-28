//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"
#include "Title.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define FILE_PATH L"Data/Game/Title.png" //パス名

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：背景の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TITLE::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---書式設定---//
    pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX)); //頂点書式設定
    pDevice->SetFVF(FVF_VERTEX);                                  //フォーマット設定
    pDevice->SetTexture(0, Graphic);                                 //テクスチャ設定

    //---頂点バッファによる背景描画---//
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：背景の初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT TITLE::Initialize(void)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;
    VERTEX* pVertex;

    //---初期化処理---//
    pDevice = GetDevice();

    //---テクスチャの読み込み---//
    hResult = D3DXCreateTextureFromFileW(pDevice, FILE_PATH, &Graphic);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"タイトル画面の画像の読み込みに失敗しました", FILE_PATH, MB_OK);
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
        pVertex[nCounter].Position.x = pVertex[nCounter].U * SCREEN_WIDTH;
        pVertex[nCounter].Position.y = pVertex[nCounter].V * SCREEN_HEIGHT;
        pVertex[nCounter].Position.z = 0.0F;
        pVertex[nCounter].RHW = 1.0F;
        pVertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    //バッファのポインタの解放
    VertexBuffer->Unlock();

    //---BGM再生---//
    SOUND_MANAGER::Play(BGM_OPENING);

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：背景の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TITLE::Uninitialize(void)
{
    //---解放---//
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(Graphic)

    //---BGM停止---//
    SOUND_MANAGER::Stop(BGM_OPENING);
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：背景の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TITLE::Update(void)
{
    if (INPUT_MANAGER::GetKey(DIK_A, TRIGGER) || INPUT_MANAGER::GetMouseButton(BUTTON_LEFT, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_GAME);
    }
}