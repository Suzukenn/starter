//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Collision.h"
#include "Main.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define VIEW_ANGLE 25.0F

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
bool COLLISION::CheckInst(D3DXVECTOR2 lift_left, D3DXVECTOR2 lift_right, D3DXVECTOR2 lift_pos, D3DXVECTOR2 lift_size)
{
    ////---各種宣言---//
    //float Crs_v_v1;
    //float Crs_v_v2;
    //float Crs_v1_v2;
    //float t1;
    //float t2;
    //D3DXVECTOR2 v;

    //const float eps = 0.00001F;

    //v = Position[0] - lift_left;
    //Crs_v1_v2 = Position[1].x * lift_right.y - Position[1].y * lift_right.x;

    //// 平行状態
    //if (!Crs_v1_v2)
    //{
    //    return false;
    //}

    //Crs_v_v1 = v.x * lift_left.y - v.y * lift_left.x;
    //Crs_v_v2 = v.x * lift_right.y - v.y * lift_right.x;

    //t1 = Crs_v_v2 / Crs_v1_v2;
    //t2 = Crs_v_v1 / Crs_v1_v2;

    //// 交差していない
    //if (t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1) 
    //{
    //    return false;
    //}

    //if (outPos)
    //    *outPos = seg1.s + seg1.v * t1;

    return true;
}

/////////////////////////////////////////////
//関数名：CheckPlayer
//
//機能：プレイヤーの視野角内判定
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
bool COLLISION::CheckPlayer(D3DXVECTOR2 player_pos, D3DXVECTOR2 size)
{
    //---各種宣言---//
    int nCounter;
    double dCorner1;
    double dCorner2;
    double dCorner3;
    D3DXVECTOR2 vecAB;
    D3DXVECTOR2 vecBC;
    D3DXVECTOR2 vecCA;
    D3DXVECTOR2 vecAP;
    D3DXVECTOR2 vecBP;
    D3DXVECTOR2 vecCP;

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

        vecCA = Position[2] - Position[0];
        vecAP = vecPlayerVertex[nCounter] - Position[2];


        //外積の計算
        dCorner1 = vecAB.x * vecBP.y - vecAB.y * vecBP.x;
        dCorner2 = vecBC.x * vecCP.y - vecBC.y * vecCP.x;
        dCorner3 = vecCA.x * vecAP.y - vecCA.y * vecAP.x;

        //判定
        if ((dCorner1 > 0 && dCorner2 > 0 && dCorner3 > 0) || (dCorner1 < 0 && dCorner2 < 0 && dCorner3 < 0))
        {
            //死角判定
            if (!DeadAngle.CheckDeadAngle(player_pos, size))
            {
                return true;
            }
        }
    }

    return false;
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

    //---死角の描画---//
    DeadAngle.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：当たり判定の初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT COLLISION::Initialize(void)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

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
        Vertex[nCounter].Position.x = 0.0F;
        Vertex[nCounter].Position.y = 0.0F;
        Vertex[nCounter].Position.z = 0.0F;
        Vertex[nCounter].RHW = 1.0F;
        Vertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    //バッファのポインタの解放
    VertexBuffer->Unlock();

    DeadAngle.Initialize();

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：当たり判定の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void COLLISION::Uninitialize(void)
{
    //---解放---//
    DeadAngle.Uninitialize();
    SAFE_RELEASE(VertexBuffer);
    Vertex = nullptr;
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：当たり判定の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void COLLISION::Update(void)
{
    //---各種宣言---//
    int nCounter;
    float fHeight;
    float fWidth1;
    float fWidth2;

    //---初期化処理---//
    fHeight = SCREEN_HEIGHT - Position[0].y;

    //---頂点の算出---//
    fWidth1 = fabsf(fHeight * tanf(D3DXToRadian(VIEW_ANGLE)));
    Position[1] = { Position[0].x + fWidth1, SCREEN_HEIGHT };

    fWidth2 = fabsf(fHeight * tanf(D3DXToRadian(VIEW_ANGLE)));
    Position[2] = { Position[0].x - fWidth2, SCREEN_HEIGHT };

    //---バッファに反映---//
    for (nCounter = 0; nCounter < 3; nCounter++)
    {
        Vertex[nCounter].Position = { Position[nCounter].x, Position[nCounter].y, 0.0F };
    }
}