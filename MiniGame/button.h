#ifndef _BUTTON_H_
#define _BUTTON_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"
#include "Sprite.h"

//�������N���X��`������//
class BUTTON : private SPRITE
{		
	public:
		D3DXVECTOR3 D_Pos;	//�ʒu�̌��J�o�b�t�@
        D3DXVECTOR3 D_Size;	//�傫���̌��J�o�b�t�@
		bool Push;		    //��������

		void Draw(void) override;
        void Initialize(D3DXVECTOR3, D3DXVECTOR3, LPCWSTR);
        void Uninitialize(void) override;
		void Update(void);
};

#endif