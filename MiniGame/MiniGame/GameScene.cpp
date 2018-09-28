//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define FILE_PATH L"Data/Game/BackGround.tga" //パス名

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：ゲームシーンの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAME::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---書式設定---//
    pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX_2D)); //頂点書式設定
    pDevice->SetFVF(FVF_VERTEX_2D);                                  //フォーマット設定
    pDevice->SetTexture(0, Graphic);                                 //テクスチャ設定

    //---頂点バッファによる背景描画---//
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ゲームシーンの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT GAME::Initialize(void)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;
    VERTEX_2D* pVertex;

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
    hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, &VertexBuffer, nullptr);

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
    SOUND_MANAGER::Play(BGM_GAME);

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ゲームシーンの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAME::Uninitialize(void)
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

    //---BGM停止---//
    SOUND_MANAGER::Stop(BGM_GAME);
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ゲームシーンの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAME::Update(void)
{
    //---画面遷移---//
    if (INPUT_MANAGER::GetKey(DIK_A, TRIGGER))
    {
        SCENE_MANAGER::SetScene(SCENE_GAMEOVER);
    }
}