#ifndef _COLLISION_H_
#define _COLLISION_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class COLLISION
{
    private:
        D3DXVECTOR2 Position[3];
        float Angle;
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //���_�o�b�t�@
        VERTEX* Vertex;

    public:
        bool CheckPlayer(D3DXVECTOR2, D3DXVECTOR2);
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);

        void SetData(D3DXVECTOR2 position, float rad) { Position[0] = position; Angle = rad; }
};

#endif