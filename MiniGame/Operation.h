//
//	Operation.h
//
#pragma once

#ifndef _OPERATION_H_
#define _OPERATION_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������萔�E�}�N����`������//
//�}�E�X�J�[�\���T�C�Y
#define OPERATION_WIDTH			(30)	//��
#define OPERATION_HEIGHT		(30)	//����
//�l�p����p
#define OPERATION_HIT_WIDTH		(5)		//��
#define OPERATION_HIT_HEIGHT	(5)		//����
//�~����p
#define OPERATION_RADIUS	(30)

//�������N���X�錾������//
class OPERATION
{
	private:
		POINT Pos;								//�}�E�X�̂̈ʒu
		LPDIRECT3DTEXTURE9 Graphic;				//�e�N�X�`��
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//���_�o�b�t�@
		VERTEX* pVertex;

	public:
		OPERATION();
		~OPERATION();

		//===�v���g�^�C�v�錾===
		HRESULT Initialize(void);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);
		POINT* GetMousePos(void);

};

#endif