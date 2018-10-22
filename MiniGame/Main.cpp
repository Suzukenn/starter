//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <cstdlib>
#include <ctime>
#include "InputManager.h"
#include "Main.h"
#include "SceneManager.h"
#include "SoundManager.h"

//�������萔�E�}�N����`������//
#define FPS 1000 / 60
#define WINDOW_CAPTION L"SPY's"	        //�E�C���h�E�̃L���v�V������
#define WINDOW_CLASS_NAME L"MiniGame"	//�E�C���h�E�̃N���X��

//�������v���g�^�C�v�錾������//
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

//�������O���[�o���ϐ�������//
LPDIRECT3D9 g_pD3D;			    //Direct3D �I�u�W�F�N�g
LPDIRECT3DDEVICE9 g_pD3DDevice; //Device�I�u�W�F�N�g(�`��ɕK�v)
HWND g_hWnd;
#ifdef _DEBUG
int	g_nCountFPS;	    //FPS�J�E���^
LPD3DXFONT g_pD3DXFont;	//�t�H���g�ւ̃|�C���^
#endif


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //---���g�p�錾---//
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

    //---�e��錾---//
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
    MSG msg;
    
    const WNDCLASSEXW wcex = { sizeof(WNDCLASSEXW), CS_CLASSDC, WindowProc, 0, 0, hInstance, nullptr, LoadCursorW(nullptr, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), nullptr, WINDOW_CLASS_NAME, nullptr };

    //---����������---//
    //�����V�[�h�l�̏�����
    srand((unsigned int)time(NULL));

    //---�E�B���h�E����---//
    //COM���C�u�����̏�����
    if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
    {
        MessageBoxW(nullptr, L"COM���C�u�����̏������Ɏ��s���܂���", L"�������G���[", MB_OK);
        return -1;
    }

	//�E�B���h�E�N���X�̓o�^
	RegisterClassExW(&wcex);

	//�E�B���h�E�̍쐬
    g_hWnd = CreateWindowExW(0, WINDOW_CLASS_NAME, WINDOW_CAPTION, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, (int)(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2), (int)(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)), nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd)
    {
        MessageBoxW(nullptr, L"�E�B���h�E�̍쐬�Ɏ��s���܂���", L"�������G���[", MB_OK);
        return -1;
    }

    //�E�B���h�E�̕\��
    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

	//�f�[�^����������
	if (FAILED(Initialize(hInstance, g_hWnd)))
	{
        MessageBoxW(nullptr, L"�f�[�^�̏������Ɏ��s���܂���", L"�������G���[", MB_OK);
		return -1;
	}

	//---�t���[�����䏉����---//
    //����\��ݒ�
    if (timeBeginPeriod(1))
    {
        MessageBoxW(nullptr, L"�^�C�}�[����\���w��l�ɐݒ�ł��܂���ł���", L"FPS�ݒ�G���[", MB_OK);
        return -1;
    }

    //���Ԃ̏�����
    dwExecLastTime = dwFPSLastTime = timeGetTime();

    //�t���[������������
	dwCurrentTime =	dwFrameCount = 0;

	//---���b�Z�[�W���[�v---//
	while (true)
	{
		if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
                //PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				//���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

            //0.5�b���ƂɎ��s
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
                //�ŏI�X�V���ԍX�V
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Update();

				//�`�揈��
				Draw();

                //�t���[���J�E���g�A�b�v
				dwFrameCount++;
			}
		}
	}

    //---�I������---//
    UnInitialize();

    //����\��߂�
    timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClassW(WINDOW_CLASS_NAME, wcex.hInstance);

    //COM���C�u���������
    CoUninitialize();

    return (int)msg.wParam;
}


//�������֐���`������//
/////////////////////////////////////////////
//�֐����FWindowProc
//
//�@�\�F�E�B���h�E�v���V�[�W��
//
//�����F(HWND)�n���h��,(UINT)���b�Z�[�W�L���[,(WPARAM)�p�����[�^,(LPARAM)�p�����[�^
//
//�߂�l�F(LRESULT)�����̐���
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
//�֐����FDraw
//
//�@�\�F�`�揈���̓����֐�
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void Draw(void)
{
    //�o�b�N�o�b�t�@���y�o�b�t�@���X�e���V���o�b�t�@�̃N���A
    g_pD3DDevice->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0F, 0);

    //Direct3D�ɂ��`��̊J�n
    if (SUCCEEDED(g_pD3DDevice->BeginScene()))
    {
        //�V�[���`��
        SCENE_MANAGER::Draw();

#ifdef _DEBUG
        //FPS�\��
        DrawFPS();
#endif

        //Direct3D�ɂ��`��̏I��
        g_pD3DDevice->EndScene();
    }

    //�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
    g_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�������̓����֐�
//
//�����F(HINSTANCE)�C���X�^���X,(HWND)�n���h��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT Initialize(HINSTANCE hInstance, HWND hWnd)
{
    //---���ݒ�---//
    if (FAILED(SetupEnvironment(hWnd)))
    {
        return E_FAIL;
    }

    //---���͏�����---//
    if (FAILED(INPUT_MANAGER::Initialize(hWnd)))
    {
        return E_FAIL;
    }

    //---�T�E���h������---//
    if (FAILED(SOUND_MANAGER::Initialize()))
    {
        return E_FAIL;
    }

    //---�V�[��������---//
    if (FAILED(SCENE_MANAGER::Initialize()))
    {
        return E_FAIL;
    }

    return S_FALSE;
}

/////////////////////////////////////////////
//�֐����FOnCreate
//
//�@�\�F�X�V�����̓����֐�
//
//�����F(HWND)�E�B���h�E�n���h��,(LPCREATESTRUCT)�T�C�Y
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
static void OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
    //---�e��錾---//
    RECT rcClnt;
    RECT rcWnd;
    SIZE sizeWnd;

    //---�E�B���h�E�E�B���h�E�T�C�Y�̐ݒ�---//
    GetWindowRect(hWnd, &rcWnd);
    GetClientRect(hWnd, &rcClnt);

    sizeWnd.cx = (LONG)((rcWnd.right - rcWnd.left) - (rcClnt.right - rcClnt.left) + SCREEN_WIDTH);
    sizeWnd.cy = (LONG)((rcWnd.bottom - rcWnd.top) - (rcClnt.bottom - rcClnt.top) + SCREEN_HEIGHT);

    SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);

    //---IME���͂̋֎~---//
    ImmAssociateContext(hWnd, nullptr);
}

/////////////////////////////////////////////
//�֐����FSetupEnvironment
//
//�@�\�F���ݒ�
//
//�����F(HWND)�n���h��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
static HRESULT SetupEnvironment(HWND hWnd)
{
    //---�e��錾---//
    D3DDISPLAYMODE d3ddm;
    D3DPRESENT_PARAMETERS d3dpp;

    //---Direct3D�I�u�W�F�N�g�̍쐬---//
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!g_pD3D)
    {
        return E_FAIL;
    }

    //---���݂̃f�B�X�v���C���[�h���擾---//
    if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        return E_FAIL;
    }

    //---�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�---//
    memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));	    //���[�N���[���N���A
    d3dpp.BackBufferCount = 1;						        //�o�b�N�o�b�t�@�̐�
    d3dpp.BackBufferWidth = (UINT)SCREEN_WIDTH;				//�Q�[����ʃT�C�Y(��)
    d3dpp.BackBufferHeight = (UINT)SCREEN_HEIGHT;			//�Q�[����ʃT�C�Y(����)
    d3dpp.BackBufferFormat = d3ddm.Format;				    //�o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Đݒ�
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	            //�f���M���ɓ������ăt���b�v����
    d3dpp.Windowed = TRUE;  					            //�E�B���h�E���[�h
    d3dpp.EnableAutoDepthStencil = TRUE;				    //�f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;		    //�f�v�X�o�b�t�@�Ƃ���24bit�A�X�e���V���o�b�t�@�Ƃ���8bit���g��

    //---�E�B���h�E���[�h---//
    d3dpp.FullScreen_RefreshRateInHz = 0;						//���t���b�V�����[�g
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//���������M���ɓ������Ȃ�

    //---�f�o�C�X�I�u�W�F�N�g�̐���---//
    //[�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
    {
        //��L�̐ݒ肪���s������[�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
        if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
        {
            //��L�̐ݒ肪���s������[�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
            if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
            {
                //���������s
                return E_FAIL;
            }
        }
    }

    //---�����_�[�X�e�[�g�p�����[�^�̐ݒ�---//
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				//�J�����O���Ȃ�
    g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);						//Z�o�b�t�@���g�p���Ȃ�
    g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//���u�����h���s��
    g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//���\�[�X�J���[�̎w��
    g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//���f�X�e�B�l�[�V�����J���[�̎w��

    //---�T���v���[�X�e�[�g�p�����[�^�̐ݒ�---//
    g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//�e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
    g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//�e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
    g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);	    //�e�N�X�`���k���t�B���^���[�h��ݒ�
    g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);	    //�e�N�X�`���g��t�B���^���[�h��ݒ�

    //---�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�---//
    g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//�A���t�@�u�����f�B���O����
    g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	//�ŏ��̃A���t�@����
    g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	//�Q�Ԗڂ̃A���t�@����

#ifdef _DEBUG
    //---���\���p�t�H���g��ݒ�---//
    D3DXCreateFontW(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Terminal", &g_pD3DXFont);
#endif

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUnInitialize
//
//�@�\�F�I�������̓����֐�
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void UnInitialize(void)
{
    //---���͂̏I��---//
    INPUT_MANAGER::Uninitialize();

    //---�V�[���̏I��---//
    SCENE_MANAGER::Uninitialize();

    //---�T�E���h�̏I��---//
    SOUND_MANAGER::Uninitialize();

#ifdef _DEBUG
    //���\���p�t�H���g�̉��
    SAFE_RELEASE(g_pD3DXFont);
#endif

    //�f�o�C�X�̉��
    SAFE_RELEASE(g_pD3DDevice);

    //Direct3D�I�u�W�F�N�g�̉��
    SAFE_RELEASE(g_pD3D);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�X�V�����̓����֐�
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void Update(void)
{
    //---���͂̍X�V---//
    INPUT_MANAGER::Update();

	//---�V�[���̍X�V---//
    SCENE_MANAGER::Update();
}

/////////////////////////////////////////////
//�֐����FGetDevice
//
//�@�\�F�f�o�C�X�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(LPDIRECT3DDEVICE9)�f�o�C�X
/////////////////////////////////////////////
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

/////////////////////////////////////////////
//�֐����FGethWnd
//
//�@�\�FhWnd�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(HWND)�n���h��
/////////////////////////////////////////////
HWND* GethWnd(void)
{
	return &g_hWnd;
}

#ifdef _DEBUG
/////////////////////////////////////////////
//�֐����FDrawFPS
//
//�@�\�F�t���[�����[�g�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void DrawFPS(void)
{
	static RECT rRectangle = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
    WCHAR szString[1024];

	wsprintfW(szString, L"FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�`��
	g_pD3DXFont->DrawTextW(nullptr, szString, -1, &rRectangle, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
}
#endif