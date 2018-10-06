#ifndef _CAMERA_H_
#define _CAMERA_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Collision.h"
#include "Main.h"

//�������N���X�錾������//
class CAMERA
{
    private:
        D3DXVECTOR2 Position;                 //�ʒu
        D3DXVECTOR2 Center;                   //�摜���S�ʒu
        float Angle;                          //��]
        LPDIRECT3DTEXTURE9 Graphic;           //�e�N�X�`��
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //���_�o�b�t�@
        VERTEX* Vertex;
        COLLISION Collision;

    public:
        bool CheckPlayer(D3DXVECTOR2, D3DXVECTOR2);
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif