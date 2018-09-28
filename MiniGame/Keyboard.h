#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>

//＝＝＝クラス宣言＝＝＝//
class KEYBOARD
{
    private:
        LPDIRECTINPUTDEVICE8 Device; //デバイス
        BYTE Current[256];	         //現在の状態
        BYTE Preview[256];	         //前回の状態
        BYTE Trigger[256];	         //トリガ状態
        BYTE Release[256];	         //リリース状態

    public:
        HRESULT Initialize(HWND, LPDIRECTINPUT8);
        void Uninitialize(void);
        void Update(void);

        bool GetHold(DWORD);
        bool GetTrigger(DWORD);
        bool GetRelease(DWORD);
};

#endif