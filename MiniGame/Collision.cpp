//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Collision.h"
#include "GameScene.h"
#include "Main.h"

//＝＝＝定数・マクロ定義＝＝＝//

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：CheckPlayer
//
//機能：プレイヤーの視野角内判定
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
bool COLLISION::CheckPlayer(D3DXVECTOR2 player_pos, float radius)
{
    //---各種宣言---//
    int nCounter;
    float fDotAA;
    float fDotAV;
    float fS;
    float fSq;
    D3DXVECTOR2 vRayVector;
    D3DXVECTOR2 vOrigin;
    float Angle = 0.0F;
    const D3DXVECTOR2 vCameraVector[4] = { {1.0F, 1.0F}, {-1.0F,-1.0F}, {-1.0F, -1.0F}, {1.0F, -1.0F} };

    //---初期化処理---//
    nCounter = 0;
    vOrigin = { SCREEN_CENTER_X, 10.0F };
    vRayVector = { Angle, SCREEN_HEIGHT };
    vRayVector.x *= vCameraVector[(int)(Angle / 90.0F)].x;
    vRayVector.y *= vCameraVector[(int)(Angle / 90.0F)].y;

    //半径がマイナスはエラー（半径ゼロは許容）
    if (radius < 0.0F)
    {
        return false;
    }

    //円の中心点が原点になるように始点をオフセット
    vOrigin -= player_pos;

    for (nCounter = 0; nCounter < 3; nCounter++)
    {
        //レイの方向ベクトルを正規化
        vRayVector /= sqrtf(vRayVector.x * vRayVector.x + vRayVector.y * vRayVector.y);

        //係数tを算出
        fDotAV = vOrigin.x * vRayVector.x + vOrigin.y * vRayVector.y;
        fDotAA = vOrigin.x * vOrigin.x + vOrigin.y * vOrigin.y;
        fS = fDotAV * fDotAV - fDotAA + radius * radius;

        //誤差修正
        if (fabsf(fS) < 0.000001F)
        {
            fS = 0.0F;
        }

        //衝突していない
        if (fS < 0.0F)
        {
            vRayVector = { Angle + 15.0F * (nCounter + 1), SCREEN_HEIGHT };
            vRayVector *= *vCameraVector[(int)(Angle / 90.0F)];
            continue;
        }

        fSq = sqrtf(fS);

        //もしt1及びt2がマイナスだったら始点が円内にめり込んでいるのでエラーとする
        if ((-fDotAV - fSq) < 0.0F || (-fDotAV + fSq) < 0.0F)
        {
            vRayVector = { Angle + 15.0F * (nCounter + 1), SCREEN_HEIGHT };
            vRayVector *= *vCameraVector[(int)(Angle / 90.0F)];
        }
        else
        {
            return true;
        }
    }
    return false;

    //const D3DXVECTOR2 poVertex[3] = { { player_pos.x, player_pos.y },{ player_pos.x + 50.0F, SCREEN_HEIGHT },{ player_pos.x - 50.0F, SCREEN_HEIGHT } };
    //return false;
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：当たり判定の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void COLLISION::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---書式設定---//
    pDevice->SetFVF(FVF_VERTEX);       //フォーマット設定
    pDevice->SetTexture(0, nullptr);   //テクスチャ設定

    //---描画---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, Vertex, sizeof(VERTEX));
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
HRESULT COLLISION::Initialize(D3DXVECTOR2 position)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();
    Position[0] = { position.x, position.y };
    Position[1] = { position.x + 50.0F, SCREEN_HEIGHT };
    Position[2] = { position.x - 50.0F, SCREEN_HEIGHT };

    //---頂点バッファの生成---//
    hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 3, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBuffer, nullptr);

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
    for (nCounter = 0; nCounter < 3; nCounter++)
    {
        Vertex[nCounter].U = (float)(nCounter & 1);
        Vertex[nCounter].V = (float)((nCounter >> 1) & 1);
        Vertex[nCounter].Position.x = Position[nCounter].x;
        Vertex[nCounter].Position.y = Position[nCounter].y;
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
//機能：カメラの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void COLLISION::Uninitialize(void)
{
    //---解放---//
    SAFE_RELEASE(VertexBuffer);
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
void COLLISION::Update(void)
{

}