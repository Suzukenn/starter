#ifndef _MOUSE_H_
#define _MOUSE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>

//＝＝＝クラス宣言＝＝＝//
class MOUSE
{
    private:
        LPDIRECTINPUTDEVICE8 Device; //デバイス
        DIMOUSESTATE Current;	 //現在の状態
        DIMOUSESTATE Preview;	 //前回の状態
        DIMOUSESTATE Trigger;	 //トリガ状態
        DIMOUSESTATE Release;	 //リリース状態


    public:
        HRESULT Initialize(HWND, LPDIRECTINPUT8);
        void Uninitialize(void);
        void Update(void);

        bool GetHold(DWORD);
        DIMOUSESTATE* GetMove(void);
        bool GetTrigger(DWORD);
        bool GetRelease(DWORD);
};

#endif