#ifndef _STAGE_EASY_BUTTON_H_
#define _STAGE_EASY_BUTTON_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"
#include "Operation.h"

//�������N���X�錾������//
class STAGEEASYBUTTON
{
    private:
        D3DXVECTOR2 Pos;						//�v���C���[�̈ʒu
        LPDIRECT3DTEXTURE9 Graphic;				//�e�N�X�`��
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//���_�o�b�t�@
        VERTEX* pVertex;
        OPERATION* Operation;					//�}�E�X�J�[�\�����

    public:
        STAGEEASYBUTTON();
        ~STAGEEASYBUTTON();

        //===�v���g�^�C�v�錾===
        HRESULT Initialize(void);
        void Uninitialize(void);
        void Update(void);
        void Draw(void);
};

#endif