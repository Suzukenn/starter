#ifndef _TIMER_H_
#define _TIMER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������萔�E�}�N����`������//
#define DIGITS 2				//�ő�\����

//�������N���X�錾������//
class TIMER
{
    private:
        int Fream;
        int Time;
        LPDIRECT3DTEXTURE9 Graphic;				        //�e�N�X�`��
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//���_�o�b�t�@
        VERTEX Vertex[4];

    public:
        HRESULT Initialize(void);
        void Uninitialize(void);
        void Update(void);
        void Draw(void);

        int GetTime(void) { return Time; }
};

#endif