#ifndef _COLLISION_H_
#define _COLLISION_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "DeadAngle.h"
#include "Main.h"

//�������N���X�錾������//
class COLLISION
{
    private:
        D3DXVECTOR2 Position[3];
        float Angle;
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //���_�o�b�t�@
        VERTEX* Vertex;
        DEADANGLE DeadAngle;

        bool CheckInst(D3DXVECTOR2 lift_left, D3DXVECTOR2 lift_right, D3DXVECTOR2 lift_pos, D3DXVECTOR2 lift_size);

    public:
        bool CheckPlayer(D3DXVECTOR2, D3DXVECTOR2);
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(D3DXVECTOR2);
        void Update(void);

        void SetData(D3DXVECTOR2 position, float rad) { Position[0] = position; Angle = rad; }
};

#endif