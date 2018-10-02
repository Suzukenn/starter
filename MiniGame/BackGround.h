#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class BACKGROUND
{
	private:
		unsigned int Score;
		LPDIRECT3DTEXTURE9 Graphic;           //�e�N�X�`��
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //���_�o�b�t�@

	public:
		void Draw(void);
		void Uninitialize(void);
		HRESULT Initialize(LPCWSTR);
		void Update(void);
};

#endif