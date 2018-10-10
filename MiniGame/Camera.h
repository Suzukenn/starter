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
		LPDIRECT3DTEXTURE9 GraphicRoot;           //�e�N�X�`��
		LPDIRECT3DVERTEXBUFFER9 VertexBufferRoot; //���_�o�b�t�@
		VERTEX* VertexRoot;
		COLLISION Collision;

        bool CheckInst();

    public:
        bool CheckDeadAngle(D3DXVECTOR2, D3DXVECTOR2, D3DXVECTOR2, D3DXVECTOR2);
        bool CheckPlayer(D3DXVECTOR2, D3DXVECTOR2);
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(D3DXVECTOR2, float);
        void Update(void);
};

#endif