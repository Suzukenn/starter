//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "Main.h"

//＝＝＝グローバル宣言＝＝＝//
LPDIRECTINPUT8 INPUT_MANAGER::Manager;
KEYBOARD INPUT_MANAGER::Keyboard;
MOUSE INPUT_MANAGER::Mouse;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Initialize
//
//機能：デバイスの初期化
//
//引数：(HWND)ハンドル
//
//戻り値：(LRESULT)処理の成否
/////////////////////////////////////////////
HRESULT INPUT_MANAGER::Initialize(HWND hWnd)
{
	//---各種宣言---//
	HRESULT hResult;

	//DirectInputオブジェクト生成
    hResult = DirectInput8Create(::GetModuleHandleW(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8W, (void**)&Manager, nullptr);
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"DirectInputオブジェクト生成に失敗しました。", L"ERROR", MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

	//キーボードの初期化
    hResult = Keyboard.Initialize(hWnd, Manager);
	if (FAILED(hResult))
	{
		Uninitialize();
		return hResult;
	}

    //マウスの初期化
    hResult = Mouse.Initialize(hWnd, Manager);
    if (FAILED(hResult))
    {
        Uninitialize();
        return hResult;
    }

	return hResult;
}

//////////////////////////////////2///////////
//関数名：Uninitialize
//
//機能：デバイスの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void INPUT_MANAGER::Uninitialize(void)
{
	Keyboard.Uninitialize();
    Mouse.Uninitialize();
    SAFE_RELEASE(Manager);
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
void INPUT_MANAGER::Update(void)
{
	Keyboard.Update();
    Mouse.Update();
}

/////////////////////////////////////////////
//関数名：GetKey
//
//機能：キーボード入力判定
//
//引数：(DWORD)入力ボタン,(PUSH_TYPE)判定タイプ
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool INPUT_MANAGER::GetKey(DWORD button, PUSH_TYPE type)
{
	switch (type)
	{
		case HOLD:
			return Keyboard.GetHold(button);

		case TRIGGER:
			return Keyboard.GetTrigger(button);

		case RELEASE:
			return Keyboard.GetRelease(button);

		default:
			return false;
	}
}

/////////////////////////////////////////////
//関数名：GetMouseButton
//
//機能：マウスボタン入力判定
//
//引数：(MOUSE_BUTTON)入力ボタン,(PUSH_TYPE)判定タイプ
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool INPUT_MANAGER::GetMouseButton(MOUSE_BUTTON button, PUSH_TYPE type)
{
    switch (type)
    {
        case HOLD:
            return Mouse.GetHold(button);

        case TRIGGER:
            return Mouse.GetTrigger(button);

        case RELEASE:
            return Mouse.GetRelease(button);

        default:
            return false;
    }
}