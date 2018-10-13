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
        D3DXVECTOR2				Pos;			//�v���C���[�̈ʒu
        D3DXVECTOR2				Size;			//�v���C���[�̑傫��
        D3DXVECTOR2				Move;			//�v���C���[�̏d�͗p
		float					Interval;		//�v���C���[�̏d�͗p
		bool					Invincible;		//�v���C���[�̖��G�ʒu�i�X�^�[�g�ʒu�j����p	
        bool Hit;
		LPDIRECT3DTEXTURE9 Graphic;				//�e�N�X�`��
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//���_�o�b�t�@
		VERTEX* pVertex;
		OPERATION* Operation;
		int			Anim;						// ���[�V����No.0�`7
		int			AnimPat;					// �p�^�[��No.0�`2
		int			AnimCnt;					// �t���[����0�`15

	public:
		PLAYER();
		~PLAYER();

		//===�v���g�^�C�v�錾===
		HRESULT Initialize(int);
		void Uninitialize(void);
		void Update(int, bool);
		void Draw(void);

        bool GetHit(void) { return Hit; }
        D3DXVECTOR2	GetPos(void) { return Pos; }
        D3DXVECTOR2	GetSize(void) { return Size; }
        void SetHit(bool hit) { Hit = hit; }
		void SetPlayerAnimFrame(int);

};

#endif