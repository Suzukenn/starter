#ifndef _GAME_SCENE_3_H_
#define _GAME_SCENE_3_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"
#include "MoveCamera.h"
#include "Lift.h"
#include "Operation.h"
#include "Player.h"
#include "Timer.h"

//�������萔�E�}�N����`������//
#define MAX_CAMERA 2
#define MAX_LIFT 2
#define MAX_PLAYER 2

//�������N���X�錾������//
class GAME_3 final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        MOVECAMERA Camera[MAX_CAMERA];
        LIFT Lift[MAX_LIFT];
        OPERATION Operation;
        PLAYER Player[MAX_PLAYER];
        TIMER Timer;

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif