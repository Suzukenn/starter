//�������w�b�_�t�@�C���ǂݍ��݁�����//
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include <memory>
#include "Main.h"
#include "Mouse.h"

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
HRESULT MOUSE::Initialize(HWND hWnd , LPDIRECTINPUT8 manager)
{
    //---�e��錾---//
    HRESULT hResult;

    //---�f�o�C�X����---//
    hResult = manager->CreateDevice(GUID_SysMouse, &Device, nullptr);

    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"�}�E�X�̃I�u�W�F�N�g�����Ɏ��s���܂����B", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //---���͐ݒ�---//
    //�f�[�^�t�H�[�}�b�g�ݒ�
    hResult = Device->SetDataFormat(&c_dfDIMouse);
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"�}�E�X�̃f�[�^�t�H�[�}�b�g�ݒ�Ɏ��s���܂����B", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�������x���̐ݒ�
    hResult = Device->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"�}�E�X�̋������x���ݒ�Ɏ��s���܂����B", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�f�o�C�X�ݒ�
    DIPROPDWORD dipdw;
    dipdw.diph.dwSize = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj = 0;
    dipdw.diph.dwHow = DIPH_DEVICE;
    dipdw.dwData = DIPROPAXISMODE_REL;
    hResult = Device->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"�}�E�X�̎��ݒ�Ɏ��s���܂����B", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�f�o�C�X�ւ̓��͐���J�n
    Device->Acquire();
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"�}�E�X�̓��͐���J�n�Ɏ��s���܂����B", L"ERROR", MB_ICONSTOP | MB_OK);
        return hResult;
    }

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
void MOUSE::Uninitialize(void)
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
void MOUSE::Update(void)
{
    //---�e��錾---//
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
//�֐����FGetHold
//
//�@�\�F�{�^���z�[���h����
//
//�����F(DWORD)���̓{�^��
//
//�߂�l�F(bool)���茋��
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
//�֐����FGetMove
//
//�@�\�F�}�E�X��Ԏ擾
//
//�����F�Ȃ�
//
//�߂�l�F(DIMOUSESTATE*)���
/////////////////////////////////////////////
DIMOUSESTATE* MOUSE::GetMove(void)
{
    return &Current;
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
bool MOUSE::GetTrigger(DWORD button)
{
    if (button >= _countof(Trigger.rgbButtons))
    {
        return false;
    }
    return (Trigger.rgbButtons[button] & 0x80) != 0;
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
bool MOUSE::GetRelease(DWORD button)
{
    if (button >= _countof(Release.rgbButtons))
    {
        return false;
    }
    return (Release.rgbButtons[button] & 0x80) != 0;
}