//＝＝＝ヘッダファイル読み込み＝＝＝//
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include <memory>
#include "Main.h"
#include "Mouse.h"

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
HRESULT MOUSE::Initialize(HWND hWnd , LPDIRECTINPUT8 manager)
{
    //---各種宣言---//
    HRESULT hResult;

    //---デバイス生成---//
    hResult = manager->CreateDevice(GUID_SysMouse, &Device, nullptr);

    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"マウスのオブジェクト生成に失敗しました。", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //---入力設定---//
    //データフォーマット設定
    hResult = Device->SetDataFormat(&c_dfDIMouse);
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"マウスのデータフォーマット設定に失敗しました。", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //協調レベルの設定
    hResult = Device->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"マウスの協調レベル設定に失敗しました。", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //デバイス設定
    DIPROPDWORD dipdw;
    dipdw.diph.dwSize = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj = 0;
    dipdw.diph.dwHow = DIPH_DEVICE;
    dipdw.dwData = DIPROPAXISMODE_REL;
    hResult = Device->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"マウスの軸設定に失敗しました。", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //デバイスへの入力制御開始
    Device->Acquire();
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"マウスの入力制御開始に失敗しました。", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

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
void MOUSE::Uninitialize(void)
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
void MOUSE::Update(void)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hr;

    if (Device)
    {
        Device->Acquire();
        memmove(&Preview, &Current, sizeof(DIMOUSESTATE));
        hr = Device->GetDeviceState(sizeof(DIMOUSESTATE), &Current);
        if (hr == DIERR_INPUTLOST)
        {
            Device->Acquire();
        }
        else
        {
            for (nCounter = 0; nCounter < 4; nCounter++)
            {
                Trigger.rgbButtons[nCounter] = (~Preview.rgbButtons[nCounter] & Current.rgbButtons[nCounter]) & 0x80;
                Release.rgbButtons[nCounter] = (Preview.rgbButtons[nCounter] & ~Current.rgbButtons[nCounter]) & 0x80;
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
bool MOUSE::GetHold(DWORD button)
{
    if (button >= _countof(Current.rgbButtons))
    {
        return false;
    }

    return (Current.rgbButtons[button] & 0x80) != 0;
}

/////////////////////////////////////////////
//関数名：GetMove
//
//機能：マウス状態取得
//
//引数：なし
//
//戻り値：(DIMOUSESTATE*)状態
/////////////////////////////////////////////
DIMOUSESTATE* MOUSE::GetMove(void)
{
    return &Current;
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
bool MOUSE::GetTrigger(DWORD button)
{
    if (button >= _countof(Trigger.rgbButtons))
    {
        return false;
    }
    return (Trigger.rgbButtons[button] & 0x80) != 0;
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
bool MOUSE::GetRelease(DWORD button)
{
    if (button >= _countof(Release.rgbButtons))
    {
        return false;
    }
    return (Release.rgbButtons[button] & 0x80) != 0;
}