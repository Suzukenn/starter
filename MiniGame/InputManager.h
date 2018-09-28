#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include <memory>
#include "Keyboard.h"
#include "Mouse.h"

//�������񋓌^��`������//
typedef enum
{
    HOLD,
    RELEASE,
    TRIGGER,
    PUSH_TYPE_MAX
}PUSH_TYPE;

//�������N���X�錾������//
class INPUT_MANAGER
{
    private:
        static LPDIRECTINPUT8 Manager;
        static KEYBOARD Keyboard;
        static MOUSE Mouse;

    public:
        static HRESULT Initialize(HWND);
        static void Uninitialize(void);
        static void Update(void);

        static bool GetKey(DWORD, PUSH_TYPE);
        static bool GetMouseButton(MOUSE_BUTTON, PUSH_TYPE);
};

#endif