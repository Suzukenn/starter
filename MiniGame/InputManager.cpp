//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "Main.h"

//�������O���[�o���錾������//
LPDIRECTINPUT8 INPUT_MANAGER::Manager;
KEYBOARD INPUT_MANAGER::Keyboard;
MOUSE INPUT_MANAGER::Mouse;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�f�o�C�X�̏�����
//
//�����F(HWND)�n���h��
//
//�߂�l�F(LRESULT)�����̐���
/////////////////////////////////////////////
HRESULT INPUT_MANAGER::Initialize(HWND hWnd)
{
	//---�e��錾---//
	HRESULT hResult;

	//DirectInput�I�u�W�F�N�g����
    hResult = DirectInput8Create(::GetModuleHandleW(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8W, (void**)&Manager, nullptr);
    if (FAILED(hResult))
    {
        MessageBoxW(hWnd, L"DirectInput�I�u�W�F�N�g�����Ɏ��s���܂����B", L"ERROR", MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

	//�L�[�{�[�h�̏�����
    hResult = Keyboard.Initialize(hWnd, Manager);
	if (FAILED(hResult))
	{
		Uninitialize();
		return hResult;
	}

    //�}�E�X�̏�����
    hResult = Mouse.Initialize(hWnd, Manager);
    if (FAILED(hResult))
    {
        Uninitialize();
        return hResult;
    }

	return hResult;
}

//////////////////////////////////2///////////
//�֐����FUninitialize
//
//�@�\�F�f�o�C�X�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void INPUT_MANAGER::Uninitialize(void)
{
	Keyboard.Uninitialize();
    Mouse.Uninitialize();
    SAFE_RELEASE(Manager);
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
void INPUT_MANAGER::Update(void)
{
	Keyboard.Update();
    Mouse.Update();
}

/////////////////////////////////////////////
//�֐����FGetKey
//
//�@�\�F�L�[�{�[�h���͔���
//
//�����F(DWORD)���̓{�^��,(PUSH_TYPE)����^�C�v
//
//�߂�l�F(bool)���茋��
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
//�֐����FGetMouseButton
//
//�@�\�F�}�E�X�{�^�����͔���
//
//�����F(MOUSE_BUTTON)���̓{�^��,(PUSH_TYPE)����^�C�v
//
//�߂�l�F(bool)���茋��
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