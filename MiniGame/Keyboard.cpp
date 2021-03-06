//＝＝＝ヘッダファイル読み込み＝＝＝//
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include "Keyboard.h"
#include "Main.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Initialize
//
//機能：デバイスの初期化
//
//引数：(HWND)ハンドル,(LPDIRECTINPUT8)デバイスマネージャー
//
//戻り値：(LRESULT)処理の成否
/////////////////////////////////////////////
HRESULT KEYBOARD::Initialize(HWND hWnd, LPDIRECTINPUT8 manager)
{
    //---各種宣言---//
    HRESULT hResult;

    //---デバイス生成---//
    hResult = manager->CreateDevice(GUID_SysKeyboard, &Device, nullptr);

    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"キーボードのオブジェクト生成に失敗しました。", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //---入力設定---//
    //データフォーマット設定
    hResult = Device->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"キーボードのデータフォーマット設定に失敗しました。", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //協調レベルの設定
    hResult = Device->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"キーボードの協調レベル設定に失敗しました。", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //デバイスへの入力制御開始
    Device->Acquire();
    
    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：デバイスの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void KEYBOARD::Uninitialize(void)
{
    if (Device)
    {
        Device->Unacquire();
    }

    SAFE_RELEASE(Device);
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：入力情報の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void KEYBOARD::Update(void)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hr;

    if (Device)
    {
        Device->Acquire();
        memcpy(Preview, Current, 256);
        hr = Device->GetDeviceState(256, Current);
        if (hr == DIERR_INPUTLOST)
        {
            Device->Acquire();
        }
        else
        {
            for (nCounter = 0; nCounter < 256; nCounter++)
            {
                Trigger[nCounter] = (~Preview[nCounter] & Current[nCounter]) & 0x80;
                Release[nCounter] = (Preview[nCounter] & ~Current[nCounter]) & 0x80;
            }
        }
    }
}

/////////////////////////////////////////////
//関数名：GetHold
//
//機能：ボタンホールド判定
//
//引数：(DWORD)入力ボタン
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool KEYBOARD::GetHold(DWORD button)
{
    return (Current[button & 0xff] & 0x80) != 0;
}

/////////////////////////////////////////////
//関数名：GetTrigger
//
//機能：ボタントリガ判定
//
//引数：(DWORD)入力ボタン
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool KEYBOARD::GetTrigger(DWORD button)
{
    return (Trigger[button & 0xff] & 0x80) != 0;
}

/////////////////////////////////////////////
//関数名：GetRelease
//
//機能：ボタンリリース判定
//
//引数：(DWORD)入力ボタン
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool KEYBOARD::GetRelease(DWORD button)
{
    return (Release[button & 0xff] & 0x80) != 0;
}