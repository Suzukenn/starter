//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Stage_EasyButton.h"

//======定数・マクロ定義=====
// パス名
#define FILE_PATH	L"Data/Game/Select_EasyButton.png"
//スタートボタンサイズ
#define STARTBUTTON_WIDTH	(170)	//幅
#define STARTBUTTON_HEIGHT	(57)	//高さ
//四角判定用
#define STARTBUTTON_HIT_WIDTH	(80)	//幅
#define STARTBUTTON_HIT_HEIGHT	(25)	//高さ
//円判定用
#define STARTBUTTON_RADIUS	(30)

//=====コンストラクタ=====
STAGEEASYBUTTON::STAGEEASYBUTTON()
{
    //動的確保
    Operation = new OPERATION();
    //位置設定
    Pos.x = SCREEN_CENTER_X - 200.0F;
    Pos.y = SCREEN_CENTER_Y + 160.0F;
}

//=====デストラクタ=====
STAGEEASYBUTTON::~STAGEEASYBUTTON()
{
    //解放
    if (Operation)
    {
        delete Operation;
    }
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：スタートボタンの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT STAGEEASYBUTTON::Initialize(void)
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
        pVertex[nCounter].Position.x = pVertex[nCounter].U * STARTBUTTON_WIDTH + Pos.x;
        pVertex[nCounter].Position.y = pVertex[nCounter].V * STARTBUTTON_HEIGHT + Pos.y;
        pVertex[nCounter].Position.z = 0.0F;
        pVertex[nCounter].RHW = 1.0F;
        pVertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    //バッファのポインタの解放
    VertexBuffer->Unlock();

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：スタートボタンの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void STAGEEASYBUTTON::Uninitialize(void)
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
}

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：スタートボタンの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void STAGEEASYBUTTON::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---書式設定---//
    pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX)); //頂点書式設定
    pDevice->SetFVF(FVF_VERTEX);                                  //フォーマット設定
    pDevice->SetTexture(0, Graphic);                                 //テクスチャ設定

                                                                     //--- 座標反映 ---//
    for (int i = 0; i < 4; ++i)
    {
        pVertex[i].Position.x = Pos.x + (i % 2) * STARTBUTTON_WIDTH - STARTBUTTON_WIDTH / 2;
        pVertex[i].Position.y = Pos.y + (i / 2) * STARTBUTTON_HEIGHT - STARTBUTTON_HEIGHT / 2;
    }

    // 頂点配列によるポリゴン描画
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(pVertex[0]));
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：スタートボタンの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void STAGEEASYBUTTON::Update(void)
{
    //----- 各種宣言 -----
    POINT* MousePos = Operation->GetMousePos();
    GetCursorPos(MousePos);										// マウス座標(スクリーン座標)取得
    ScreenToClient(*GethWnd(), MousePos);						// ウィンドウ ローカル座標に変換

                                                                //スタートボタンとマウスカーソルの当たり判定
    if (INPUT_MANAGER::GetMouseButton(BUTTON_LEFT, TRIGGER) &&
        (Pos.x - STARTBUTTON_HIT_WIDTH <= MousePos->x + OPERATION_HIT_WIDTH && MousePos->x - OPERATION_HIT_WIDTH
            <= Pos.x + STARTBUTTON_HIT_WIDTH && Pos.y - STARTBUTTON_HIT_HEIGHT
            <= MousePos->y + OPERATION_HIT_HEIGHT && MousePos->y - OPERATION_HIT_HEIGHT <= Pos.y + STARTBUTTON_HIT_HEIGHT))
    {
        //ゲームシーン切替
        SCENE_MANAGER::SetScene(SCENE_GAME);

        //---決定音再生---//
        SOUND_MANAGER::Play(SE_DECISION);
    }
}
