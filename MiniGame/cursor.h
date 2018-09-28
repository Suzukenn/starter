#ifndef _CURSOR_H_
#define _CURSOR_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "main.h"
#include "title.h"
//�������N���X��`������//
class CURSOR
{
	private:
		float Pos_X;		//X���W
		float Pos_Y;		//Y���W
		float Width;		//��
		float Height;		//����
		UI_TEX Texture;		//�e�N�X�`��
		KPADStatus* Input;	//�R���g���[�����
		
		bool CheckPush(BUTTON*);
		
	public:
		void Draw(void);
        void Initialize(float, float, float, float, UI_TEX);
		void Update(BUTTON*);
};

#endif