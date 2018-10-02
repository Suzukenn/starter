#ifndef _MOUSE_H_
#define _MOUSE_H_

//＝＝＝列挙型定義＝＝＝//
typedef enum
{
    BUTTON_LEFT,
    BUTTON_CENTER,
    BUTTON_RIGHT,
} MOUSE_BUTTON;

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

        bool GetHold(MOUSE_BUTTON);
        DIMOUSESTATE* GetMove(void);
        bool GetTrigger(MOUSE_BUTTON);
        bool GetRelease(MOUSE_BUTTON);
};

#endif