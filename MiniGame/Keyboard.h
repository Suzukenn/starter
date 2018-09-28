#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>

//�������N���X�錾������//
class KEYBOARD
{
    private:
        LPDIRECTINPUTDEVICE8 Device; //�f�o�C�X
        BYTE Current[256];	         //���݂̏��
        BYTE Preview[256];	         //�O��̏��
        BYTE Trigger[256];	         //�g���K���
        BYTE Release[256];	         //�����[�X���

    public:
        HRESULT Initialize(HWND, LPDIRECTINPUT8);
        void Uninitialize(void);
        void Update(void);

        bool GetHold(DWORD);
        bool GetTrigger(DWORD);
        bool GetRelease(DWORD);
};

#endif