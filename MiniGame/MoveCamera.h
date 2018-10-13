#ifndef _MOVE_CAMERA_H_
#define _MOVE_CAMERA_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Camera.h"
#include "Collision.h"
#include "Main.h"

//�������N���X�錾������//
class MOVECAMERA : public CAMERA
{
    private:
        float SinWave;
        float Angle;                          //��]

    public:
        virtual bool CheckPlayer(D3DXVECTOR2, D3DXVECTOR2) override;
        virtual void Draw(void) override;
        virtual void Uninitialize(void) override;
        virtual HRESULT Initialize(D3DXVECTOR2) override;
        virtual void Update(void) override;
};

#endif