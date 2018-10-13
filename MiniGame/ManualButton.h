#ifndef _MANUALBUTTON_H_
#define _MANUALBUTTON_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"
#include "Operation.h"

//�������N���X�錾������//
class MANUALBUTTON
{
    private:
        D3DXVECTOR2 Pos;						//�v���C���[�̈ʒu
        LPDIRECT3DTEXTURE9 Graphic;				//�e�N�X�`��
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//���_�o�b�t�@
        VERTEX* pVertex;
        OPERATION* Operation;					//�}�E�X�J�[�\�����

    public:
        MANUALBUTTON();
        ~MANUALBUTTON();

        //===�v���g�^�C�v�錾===
        void Draw(void);
        HRESULT Initialize(void);
        void Uninitialize(void);
        void Update(void);
};

#endif