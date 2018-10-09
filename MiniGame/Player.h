//
//	Player.h
//
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"
#include "Operation.h"

//�������N���X�錾������//
class PLAYER
{
	private:
		D3DXVECTOR2 Pos;						//�v���C���[�̈ʒu
		D3DXVECTOR2 Move;						//�v���C���[�̏d�͗p
        D3DXVECTOR2 Size;
		LPDIRECT3DTEXTURE9 Graphic;				//�e�N�X�`��
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//���_�o�b�t�@
		VERTEX* Vertex;
		OPERATION* Operation;
        bool Hit;

	public:
		PLAYER();
		~PLAYER();

		//===�v���g�^�C�v�錾===
		HRESULT Initialize(void);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        D3DXVECTOR2 GetPos(void) { return Pos; }
        D3DXVECTOR2 GetSize(void) { return Size; }

        void SetHit(bool hit) { Hit = hit; }
};

#endif