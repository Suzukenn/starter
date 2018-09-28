#ifndef _MOUSE_H_
#define _MOUSE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>

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

        bool GetHold(DWORD);
        DIMOUSESTATE* GetMove(void);
        bool GetTrigger(DWORD);
        bool GetRelease(DWORD);
};

#endif