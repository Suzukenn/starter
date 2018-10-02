#ifndef _MOUSE_H_
#define _MOUSE_H_

//�������񋓌^��`������//
typedef enum
{
    BUTTON_LEFT,
    BUTTON_CENTER,
    BUTTON_RIGHT,
} MOUSE_BUTTON;

//�������N���X�錾������//
class MOUSE
{
    private:
        LPDIRECTINPUTDEVICE8 Device; //�f�o�C�X
        DIMOUSESTATE Current;	 //���݂̏��
        DIMOUSESTATE Preview;	 //�O��̏��
        DIMOUSESTATE Trigger;	 //�g���K���
        DIMOUSESTATE Release;	 //�����[�X���

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