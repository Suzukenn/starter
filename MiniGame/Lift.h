#ifndef _LIFT_H_
#define _LIFT_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "DeadAngle.h"
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
        DEADANGLE DeadAngle;

    public:
        bool CheckDeadAngle(D3DXVECTOR2, D3DXVECTOR2);
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(D3DXVECTOR2);
        void Update(void);

        D3DXVECTOR2 GetCenter(void) { return Center; }
        D3DXVECTOR2 GetPos(void) { return Position; }
        D3DXVECTOR2 GetSize(void) { return Size; }
};

#endif