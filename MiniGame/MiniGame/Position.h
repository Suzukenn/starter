#ifndef _POSITION_H_
#define _POSITION_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "Base_Scene.h"
#include "Main.h"

//�������N���X�錾������//
class POSITION
{
    private:
        D3DXVECTOR2 Position;

    public:
        void Draw(void);
        HRESULT Initialize(void);
        void Update(void);
        void Uninitialize(void);
};

#endif