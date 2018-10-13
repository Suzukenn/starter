#ifndef _CAMERA_H_
#define _CAMERA_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Collision.h"
#include "Main.h"

//�������N���X�錾������//
class CAMERA
{
    protected:
        D3DXVECTOR2 Position;                 //�ʒu
        D3DXVECTOR2 Center;                   //�摜���S�ʒu
		LPDIRECT3DTEXTURE9 Graphic;           //�e�N�X�`��
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //���_�o�b�t�@
		VERTEX* Vertex;
		LPDIRECT3DTEXTURE9 GraphicRoot;           //�e�N�X�`��
		LPDIRECT3DVERTEXBUFFER9 VertexBufferRoot; //���_�o�b�t�@
		VERTEX* VertexRoot;
		COLLISION Collision;

    public:
        virtual bool CheckPlayer(D3DXVECTOR2, D3DXVECTOR2);
        virtual void Draw(void);
        virtual void Uninitialize(void);
        virtual HRESULT Initialize(D3DXVECTOR2);
        virtual void Update(void);
};

#endif