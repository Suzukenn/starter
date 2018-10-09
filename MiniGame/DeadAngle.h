#ifndef _DEADANGLE_H_
#define _DEADANGLE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class DEADANGLE
{
    private:
        D3DXVECTOR2 Position[4];
        D3DXVECTOR2 Size;
        LPDIRECT3DTEXTURE9 Graphic;           //�e�N�X�`��
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //���_�o�b�t�@
        VERTEX* Vertex;

    public:
        bool CheckDeadAngle(D3DXVECTOR2, D3DXVECTOR2);
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);

        void SetData(D3DXVECTOR2 position, D3DXVECTOR2 size) { Position[0] = position; Size = size; }
};

#endif