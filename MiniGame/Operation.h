//
//	Operation.h
//
#pragma once

#ifndef _OPERATION_H_
#define _OPERATION_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class OPERATION
{
	private:
		POINT Pos;								//�}�E�X�̂̈ʒu
		LPDIRECT3DTEXTURE9 Graphic;				//�e�N�X�`��
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//���_�o�b�t�@
		VERTEX* Vertex;

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