//�������w�b�_�t�@�C���ǂݍ��݁�����//
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include "Keyboard.h"
#include "Main.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�f�o�C�X�̏�����
//
//�����F(HWND)�n���h��,(LPDIRECTINPUT8)�f�o�C�X�}�l�[�W���[
//
//�߂�l�F(LRESULT)�����̐���
/////////////////////////////////////////////
HRESULT KEYBOARD::Initialize(HWND hWnd, LPDIRECTINPUT8 manager)
{
    //---�e��錾---//
    HRESULT hResult;

    //---�f�o�C�X����---//
    hResult = manager->CreateDevice(GUID_SysKeyboard, &Device, nullptr);

    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"�L�[�{�[�h�̃I�u�W�F�N�g�����Ɏ��s���܂����B", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //---���͐ݒ�---//
    //�f�[�^�t�H�[�}�b�g�ݒ�
    hResult = Device->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g�ݒ�Ɏ��s���܂����B", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�������x���̐ݒ�
    hResult = Device->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"�L�[�{�[�h�̋������x���ݒ�Ɏ��s���܂����B", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�f�o�C�X�ւ̓��͐���J�n
    Device->Acquire();
    
    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�f�o�C�X�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
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
//�֐����FUpdate
//
//�@�\�F���͏��̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void KEYBOARD::Update(void)
{
    //---�e��錾---//
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
//�֐����FGetHold
//
//�@�\�F�{�^���z�[���h����
//
//�����F(DWORD)���̓{�^��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool KEYBOARD::GetHold(DWORD button)
{
    return (Current[button & 0xff] & 0x80) != 0;
}

/////////////////////////////////////////////
//�֐����FGetTrigger
//
//�@�\�F�{�^���g���K����
//
//�����F(DWORD)���̓{�^��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool KEYBOARD::GetTrigger(DWORD button)
{
    return (Trigger[button & 0xff] & 0x80) != 0;
}

/////////////////////////////////////////////
//�֐����FGetRelease
//
//�@�\�F�{�^�������[�X����
//
//�����F(DWORD)���̓{�^��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool KEYBOARD::GetRelease(DWORD button)
{
    return (Release[button & 0xff] & 0x80) != 0;
}