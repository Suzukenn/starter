//
//	Player.h
//
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"
#include "Operation.h"

//=====�}�N���萔��`=====
#define MAX_PLAYER (2)

//�������\���̒�`������//
typedef struct _ANIM_PAT {
	int Frame;		//�p�^�[��No
	int Count;		//�t���[����	
} ANIM_PAT;

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
<<<<<<< HEAD
		int			Anim;						// ���[�V����No.0�`7
		int			AnimPat;					// �p�^�[��No.0�`2
		int			AnimCnt;					// �t���[����0�`15
=======
        bool Hit;
>>>>>>> 7d89c597109ed6004bd3f05ead395712797e4aa4

	public:
		PLAYER();
		~PLAYER();

		//===�v���g�^�C�v�錾===
		HRESULT Initialize(void);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

<<<<<<< HEAD
		void SetPlayerAnimFrame(int);

=======
        D3DXVECTOR2 GetPos(void) { return Pos; }
        D3DXVECTOR2 GetSize(void) { return Size; }

        void SetHit(bool hit) { Hit = hit; }
>>>>>>> 7d89c597109ed6004bd3f05ead395712797e4aa4
};

#endif