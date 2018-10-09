#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class BASE_SCENE
{
    public:
        virtual void Draw(void) = 0;
        virtual void Uninitialize(void) = 0;
        virtual HRESULT Initialize(void) = 0;
        virtual void Update(void) = 0;
};

#endif