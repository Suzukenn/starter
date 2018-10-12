//
//	RetryButton.h
//
#pragma once

#ifndef _RETRYBUTTON_H_
#define _RETRYBUTTON_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"
#include "Operation.h"
#include "SceneManager.h"

//�������N���X�錾������//
class RETRYBUTTON
{
	private:
		D3DXVECTOR2 Pos;						//�v���C���[�̈ʒu
		LPDIRECT3DTEXTURE9 Graphic;				//�e�N�X�`��
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//���_�o�b�t�@
		VERTEX* pVertex;
		OPERATION* Operation;					//�}�E�X�J�[�\�����
		static SCENE RetryScene;				//���g���C��̃V�[��

	public:
		RETRYBUTTON();
		~RETRYBUTTON();

		//===�v���g�^�C�v�錾===
		HRESULT Initialize(void);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

		static void SetRetryScene(SCENE);		//���g���C��̃Z�b�g
};

#endif