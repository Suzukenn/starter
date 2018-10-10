#ifndef _GAMECLEAR_H_
#define _GAMECLEAR_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"
#include "RetryButton.h"
#include "TitleButton.h"

//�������N���X�錾������//
class GAMECLEAR final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        RETRYBUTTON Retry_B;	//���g���C�{�^���p
        TITLEBUTTON Title_B;	//�^�C�g���{�^���p

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif