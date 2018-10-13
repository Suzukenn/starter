#ifndef _TIMER_H_
#define _TIMER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������萔�E�}�N����`������//
#define CHECK_TIME 4
#define DIGITS 2				//�ő�\����

//�������N���X�錾������//
class TIMER
{
    private:
        int Fream;
        int Time;
        bool Check;
        LPDIRECT3DTEXTURE9 Graphic;				        //�e�N�X�`��
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//���_�o�b�t�@
        VERTEX Vertex[4];

    public:
        HRESULT Initialize(void);
        void Uninitialize(void);
        void Update(void);
        void Draw(void);

        bool GetCheck(void) { return Check; }
        int GetTime(void) { return Time; }
        void SetCheck(bool check) { Check = check; }
        void SetTime(int time) { Fream = time * 60; }

};

#endif