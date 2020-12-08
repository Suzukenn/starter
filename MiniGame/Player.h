//
//	Player.h
//
#ifndef _PLAYER_H_
#define _PLAYER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"
#include "Operation.h"

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
        D3DXVECTOR2				PosOld;			//�v���C���[�̑O�̈ʒu
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
        int			LiftLandCnt;				// ���n�A�j���[�V�����p�J�E���g
        bool					LiftLanding;		//�v���C���[�̒n�`���n����
        bool					GroundLanding;		//�v���C���[�̒n�㒅�n����

	public:
		PLAYER();
		~PLAYER();

		//===�v���g�^�C�v�錾===
        void CheckCollisionLift(D3DXVECTOR2 LiftPos, D3DXVECTOR2 LiftSize);
        void Draw(void);
		HRESULT Initialize(int);
        void SetPlayerAnimFrame(int);
		void Uninitialize(void);
		void Update(int, bool);

        bool GetHit(void) { return Hit; }
        D3DXVECTOR2	GetPos(void) { return Pos; }
        D3DXVECTOR2	GetSize(void) { return Size; }
        void SetHit(bool hit) { Hit = hit; }
};

#endif