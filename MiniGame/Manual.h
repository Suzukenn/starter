#ifndef _MANUAL_H_
#define _MANUAL_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"
#include "TitleButton.h"

//�������N���X�錾������//
class MANUAL final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        TITLEBUTTON Title_B;	//�^�C�g���{�^���p

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif