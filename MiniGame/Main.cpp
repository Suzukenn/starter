//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <cstdlib>
#include <ctime>
#include "InputManager.h"
#include "Main.h"
#include "SceneManager.h"
#include "SoundManager.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define FPS 1000 / 60
#define WINDOW_CAPTION L"SPY's"	        //ウインドウのキャプション名
#define WINDOW_CLASS_NAME L"MiniGame"	//ウインドウのクラス名

//＝＝＝プロトタイプ宣言＝＝＝//
void Draw(void);
HRESULT Initialize(HINSTANCE, HWND);
static void OnCreate(HWND, LPCREATESTRUCT);
static HRESULT SetupEnvironment(HWND);
void UnInitialize(void);
void Update(void);
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

#ifdef _DEBUG
void DrawFPS(void);
#endif

//＝＝＝グローバル変数＝＝＝//
LPDIRECT3D9 g_pD3D;			    //Direct3D オブジェクト
LPDIRECT3DDEVICE9 g_pD3DDevice; //Deviceオブジェクト(描画に必要)
HWND g_hWnd;
#ifdef _DEBUG
int	g_nCountFPS;	    //FPSカウンタ
LPD3DXFONT g_pD3DXFont;	//フォントへのポインタ
#endif


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //---未使用宣言---//
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

    //---各種宣言---//
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
    MSG msg;
    
    const WNDCLASSEXW wcex = { sizeof(WNDCLASSEXW), CS_CLASSDC, WindowProc, 0, 0, hInstance, nullptr, LoadCursorW(nullptr, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), nullptr, WINDOW_CLASS_NAME, nullptr };

    //---初期化処理---//
    //乱数シード値の初期化
    srand((unsigned int)time(NULL));

    //---ウィンドウ準備---//
    //COMライブラリの初期化
    if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
    {
        MessageBoxW(nullptr, L"COMライブラリの初期化に失敗しました", L"初期化エラー", MB_OK);
        return -1;
    }

	//ウィンドウクラスの登録
	RegisterClassExW(&wcex);

	//ウィンドウの作成
    g_hWnd = CreateWindowExW(0, WINDOW_CLASS_NAME, WINDOW_CAPTION, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, (int)(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2), (int)(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)), nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd)
    {
        MessageBoxW(nullptr, L"ウィンドウの作成に失敗しました", L"初期化エラー", MB_OK);
        return -1;
    }

    //ウィンドウの表示
    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

	//データ初期化処理
	if (FAILED(Initialize(hInstance, g_hWnd)))
	{
        MessageBoxW(nullptr, L"データの初期化に失敗しました", L"初期化エラー", MB_OK);
		return -1;
	}

	//---フレーム制御初期化---//
    //分解能を設定
    if (timeBeginPeriod(1))
    {
        MessageBoxW(nullptr, L"タイマー分解能を指定値に設定できませんでした", L"FPS設定エラー", MB_OK);
        return -1;
    }

    //時間の初期化
    dwExecLastTime = dwFPSLastTime = timeGetTime();

    //フレーム数を初期化
	dwCurrentTime =	dwFrameCount = 0;

	//---メッセージループ---//
	while (true)
	{
		if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
                //PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				//メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

            //0.5秒ごとに実行
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= FPS)
			{
                //最終更新時間更新
				dwExecLastTime = dwCurrentTime;

				//更新処理
				Update();

				//描画処理
				Draw();

                //フレームカウントアップ
				dwFrameCount++;
			}
		}
	}

    //---終了処理---//
    UnInitialize();

    //分解能を戻す
    timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClassW(WINDOW_CLASS_NAME, wcex.hInstance);

    //COMライブラリを閉じる
    CoUninitialize();

    return (int)msg.wParam;
}


//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：WindowProc
//
//機能：ウィンドウプロシージャ
//
//引数：(HWND)ハンドル,(UINT)メッセージキュー,(WPARAM)パラメータ,(LPARAM)パラメータ
//
//戻り値：(LRESULT)処理の成否
/////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
        case WM_CREATE:
            OnCreate(hWnd, (LPCREATESTRUCT)lParam);
            break;

	    case WM_DESTROY:
		    PostQuitMessage(0);
            break;

	    default:
		    break;
	}

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：描画処理の統合関数
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void Draw(void)
{
    //バックバッファ＆Ｚバッファ＆ステンシルバッファのクリア
    g_pD3DDevice->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0F, 0);

    //Direct3Dによる描画の開始
    if (SUCCEEDED(g_pD3DDevice->BeginScene()))
    {
        //シーン描画
        SCENE_MANAGER::Draw();

#ifdef _DEBUG
        //FPS表示
        DrawFPS();
#endif

        //Direct3Dによる描画の終了
        g_pD3DDevice->EndScene();
    }

    //バックバッファとフロントバッファの入れ替え
    g_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：初期化の統合関数
//
//引数：(HINSTANCE)インスタンス,(HWND)ハンドル
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT Initialize(HINSTANCE hInstance, HWND hWnd)
{
    //---環境設定---//
    if (FAILED(SetupEnvironment(hWnd)))
    {
        return E_FAIL;
    }

    //---入力初期化---//
    if (FAILED(INPUT_MANAGER::Initialize(hWnd)))
    {
        return E_FAIL;
    }

    //---サウンド初期化---//
    if (FAILED(SOUND_MANAGER::Initialize()))
    {
        return E_FAIL;
    }

    //---シーン初期化---//
    if (FAILED(SCENE_MANAGER::Initialize()))
    {
        return E_FAIL;
    }

    return S_FALSE;
}

/////////////////////////////////////////////
//関数名：OnCreate
//
//機能：更新処理の統合関数
//
//引数：(HWND)ウィンドウハンドル,(LPCREATESTRUCT)サイズ
//
//戻り値：なし
/////////////////////////////////////////////
static void OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
    //---各種宣言---//
    RECT rcClnt;
    RECT rcWnd;
    SIZE sizeWnd;

    //---ウィンドウウィンドウサイズの設定---//
    GetWindowRect(hWnd, &rcWnd);
    GetClientRect(hWnd, &rcClnt);

    sizeWnd.cx = (LONG)((rcWnd.right - rcWnd.left) - (rcClnt.right - rcClnt.left) + SCREEN_WIDTH);
    sizeWnd.cy = (LONG)((rcWnd.bottom - rcWnd.top) - (rcClnt.bottom - rcClnt.top) + SCREEN_HEIGHT);

    SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);

    //---IME入力の禁止---//
    ImmAssociateContext(hWnd, nullptr);
}

/////////////////////////////////////////////
//関数名：SetupEnvironment
//
//機能：環境設定
//
//引数：(HWND)ハンドル
//
//戻り値：なし
/////////////////////////////////////////////
static HRESULT SetupEnvironment(HWND hWnd)
{
    //---各種宣言---//
    D3DDISPLAYMODE d3ddm;
    D3DPRESENT_PARAMETERS d3dpp;

    //---Direct3Dオブジェクトの作成---//
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!g_pD3D)
    {
        return E_FAIL;
    }

    //---現在のディスプレイモードを取得---//
    if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        return E_FAIL;
    }

    //---デバイスのプレゼンテーションパラメータの設定---//
    memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));	    //ワークをゼロクリア
    d3dpp.BackBufferCount = 1;						        //バックバッファの数
    d3dpp.BackBufferWidth = (UINT)SCREEN_WIDTH;				//ゲーム画面サイズ(幅)
    d3dpp.BackBufferHeight = (UINT)SCREEN_HEIGHT;			//ゲーム画面サイズ(高さ)
    d3dpp.BackBufferFormat = d3ddm.Format;				    //バックバッファフォーマットはディスプレイモードに合わせて設定
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	            //映像信号に同期してフリップする
    d3dpp.Windowed = TRUE;  					            //ウィンドウモード
    d3dpp.EnableAutoDepthStencil = TRUE;				    //デプスバッファ（Ｚバッファ）とステンシルバッファを作成
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;		    //デプスバッファとして24bit、ステンシルバッファとして8bitを使う

    //---ウィンドウモード---//
    d3dpp.FullScreen_RefreshRateInHz = 0;						//リフレッシュレート
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//垂直同期信号に同期しない

    //---デバイスオブジェクトの生成---//
    //[デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
    {
        //上記の設定が失敗したら[デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
        if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
        {
            //上記の設定が失敗したら[デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
            if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
            {
                //初期化失敗
                return E_FAIL;
            }
        }
    }

    //---レンダーステートパラメータの設定---//
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				//カリングしない
    g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);						//Zバッファを使用しない
    g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//αブレンドを行う
    g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//αソースカラーの指定
    g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//αデスティネーションカラーの指定

    //---サンプラーステートパラメータの設定---//
    g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//テクスチャアドレッシング方法(U値)を設定
    g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//テクスチャアドレッシング方法(V値)を設定
    g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);	    //テクスチャ縮小フィルタモードを設定
    g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);	    //テクスチャ拡大フィルタモードを設定

    //---テクスチャステージステートの設定---//
    g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//アルファブレンディング処理
    g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	//最初のアルファ引数
    g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	//２番目のアルファ引数

#ifdef _DEBUG
    //---情報表示用フォントを設定---//
    D3DXCreateFontW(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Terminal", &g_pD3DXFont);
#endif

    return S_OK;
}

/////////////////////////////////////////////
//関数名：UnInitialize
//
//機能：終了処理の統合関数
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void UnInitialize(void)
{
    //---入力の終了---//
    INPUT_MANAGER::Uninitialize();

    //---シーンの終了---//
    SCENE_MANAGER::Uninitialize();

    //---サウンドの終了---//
    SOUND_MANAGER::Uninitialize();

#ifdef _DEBUG
    //情報表示用フォントの解放
    SAFE_RELEASE(g_pD3DXFont);
#endif

    //デバイスの解放
    SAFE_RELEASE(g_pD3DDevice);

    //Direct3Dオブジェクトの解放
    SAFE_RELEASE(g_pD3D);
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：更新処理の統合関数
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void Update(void)
{
    //---入力の更新---//
    INPUT_MANAGER::Update();

	//---シーンの更新---//
    SCENE_MANAGER::Update();
}

/////////////////////////////////////////////
//関数名：GetDevice
//
//機能：デバイスの取得
//
//引数：なし
//
//戻り値：(LPDIRECT3DDEVICE9)デバイス
/////////////////////////////////////////////
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

/////////////////////////////////////////////
//関数名：GethWnd
//
//機能：hWndの取得
//
//引数：なし
//
//戻り値：(HWND)ハンドル
/////////////////////////////////////////////
HWND* GethWnd(void)
{
	return &g_hWnd;
}

#ifdef _DEBUG
/////////////////////////////////////////////
//関数名：DrawFPS
//
//機能：フレームレートの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void DrawFPS(void)
{
	static RECT rRectangle = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
    WCHAR szString[1024];

	wsprintfW(szString, L"FPS:%d\n", g_nCountFPS);

	//テキスト描画
	g_pD3DXFont->DrawTextW(nullptr, szString, -1, &rRectangle, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
}
#endif