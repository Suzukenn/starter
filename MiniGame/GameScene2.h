#ifndef _GAME_SCENE_2_H_
#define _GAME_SCENE_2_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "BaseScene.h"
#include "Camera.h"
#include "Lift.h"
#include "Main.h"
#include "Operation.h"
#include "Player.h"
#include "Timer.h"

//�������萔�E�}�N����`������//
#define MAX_CAMERA 2

//�������N���X�錾������//
class GAME_2 final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        CAMERA Camera[MAX_CAMERA];
        LIFT Lift;
		OPERATION Operation;
		PLAYER Player;
        TIMER Timer;

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif