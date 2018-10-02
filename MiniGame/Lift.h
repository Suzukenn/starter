#ifndef _LIFT_H_
#define _LIFT_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class LIFT
{
    private:
        D3DXVECTOR2 Position;                 //�ʒu
        D3DXVECTOR2 Size;                     //�ʒu
        D3DXVECTOR2 Center;                   //�摜���S�ʒu
        LPDIRECT3DTEXTURE9 Graphic;           //�e�N�X�`��
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //���_�o�b�t�@
        VERTEX* Vertex;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(D3DXVECTOR2 position, D3DXVECTOR2 size);
        void Update(void);

        D3DXVECTOR2 GetCenter(void) { return Center; }
        float GetSize(void) { return (Size.x + Size.y) / 2; }
};

#endif