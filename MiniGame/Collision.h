#ifndef _COLLISION_H_
#define _COLLISION_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class COLLISION
{
    private:
        D3DXVECTOR2 Position[3];// = { { Position.x, Position.y },{ Position.x + 50.0F, SCREEN_HEIGHT },{ Position.x - 50.0F, SCREEN_HEIGHT } };
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //���_�o�b�t�@
        VERTEX* Vertex;

    public:
        bool CheckPlayer(D3DXVECTOR2, float);
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(D3DXVECTOR2);
        void Update(void);
};

#endif