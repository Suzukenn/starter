//
//	Player.cpp
//

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"
#include "Player.h"

//======�萔�E�}�N����`=====
// �p�X��
#define FILE_PATH	L"Data/Game/PlayerGirl.png"
//�v���C���[�T�C�Y
#define PLAYER_WIDTH	(64)	//��
#define PLAYER_HEIGHT	(64)	//����
#define PLAYER_HITBOX_WIDTH		(50)
#define PLAYER_HITBOX_HEIGHT	(64)
//�~����p
#define PLAYER_RADIUS	(30)
//�d��
#define VAL_GRAVITY     (0.09f)  //�d��
//�e�N�X�`��������
#define PLAYER_DIV_U	(2)		//��������
#define PLAYER_DIV_V	(2)		//�c������
//�A�j���[�V�����̃p�^�[����
#define PLAYER_ANIM_PAT

//�������O���[�o���錾������//
//�A�j���[�V�����p�^�[��
static ANIM_PAT g_animPat[][3] = {
	{ { 0,  30 },{ 2,  30 },{ -1, -1 } },
	{ { 1,  15 },{ 3,  15 },{ -1, -1 } },
};


//=====�R���X�g���N�^=====
PLAYER::PLAYER()
{
	//���I�m��
	Operation = new OPERATION();
	//�e������
	Pos.x	= SCREEN_CENTER_X;
	Pos.y	= SCREEN_CENTER_Y;
	Anim	= 0;
	AnimPat = 0;
	AnimCnt = 0;
}

//=====�f�X�g���N�^=====
PLAYER::~PLAYER()
{
	//���
	if (Operation)
	{
		delete Operation;
	}
}

/////////////////////////////////////////////
//�֐����FSetPlayerAnimFrame
//
//�@�\�F�v���C���[�̃A�j���[�V�����t���[���ݒ�
//
//�����F(int)���݂̃A�j���[�V�����t���[��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void PLAYER::SetPlayerAnimFrame(int nFrame)
{
	float fU = (nFrame % PLAYER_DIV_U) * (1.0f / PLAYER_DIV_U);
	float fV = (nFrame / PLAYER_DIV_U) * (1.0f / PLAYER_DIV_V);

	for (int i = 0; i < 4; ++i)
	{
		pVertex[i].U = fU + (i % 2) * (1.0f / PLAYER_DIV_U);
		pVertex[i].V = fV + (i / 2) * (1.0f / PLAYER_DIV_V);
	}
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�v���C���[�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT PLAYER::Initialize(void)
{
	//---�e��錾---//
	int nCounter;
	HRESULT hResult;
	LPDIRECT3DDEVICE9 pDevice;

	//---����������---//
	pDevice = GetDevice();

	//---�e�N�X�`���̓ǂݍ���---//
	hResult = D3DXCreateTextureFromFileW(pDevice, FILE_PATH, &Graphic);
	if (FAILED(hResult))
	{
		MessageBoxW(nullptr, L"�Q�[����ʂ̏������Ɏ��s���܂���", FILE_PATH, MB_OK);
		Graphic = nullptr;
		return hResult;
	}

	//---���_�o�b�t�@�̐���---//
	hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBuffer, nullptr);

	if (FAILED(hResult))
	{
		return hResult;
	}

	//---���_�o�b�t�@�ւ̒l�̐ݒ�---//
	//�o�b�t�@�̃|�C���^���擾
	VertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	//�l�̐ݒ�
	for (nCounter = 0; nCounter < 4; nCounter++)
	{
		pVertex[nCounter].U = (float)(nCounter & 1);
		pVertex[nCounter].V = (float)((nCounter >> 1) & 1);
		pVertex[nCounter].Position.x = pVertex[nCounter].U * PLAYER_WIDTH + Pos.x;
		pVertex[nCounter].Position.y = pVertex[nCounter].V * PLAYER_HEIGHT + Pos.y;
		pVertex[nCounter].Position.z = 0.0F;
		pVertex[nCounter].RHW = 1.0F;
		pVertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	//�o�b�t�@�̃|�C���^�̉��
	VertexBuffer->Unlock();

	return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�v���C���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void PLAYER::Uninitialize(void)
{
	//---���---//
	if (VertexBuffer)
	{
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}

	if (Graphic)
	{
		Graphic->Release();
		Graphic = nullptr;
	}
}

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�v���C���[�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void PLAYER::Draw(void)
{
	//---�e��錾---//
	LPDIRECT3DDEVICE9 pDevice;

	//---����������---//
	pDevice = GetDevice();

	//---�����ݒ�---//
	pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX)); //���_�����ݒ�
	pDevice->SetFVF(FVF_VERTEX);                                  //�t�H�[�}�b�g�ݒ�
	pDevice->SetTexture(0, Graphic);                                 //�e�N�X�`���ݒ�
																	 
	// ���_�z��ɂ��|���S���`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(pVertex[0]));
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�v���C���[�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void PLAYER::Update(void)
{
	//----- �e��錾 -----//
	POINT* MousePos = Operation->GetMousePos();
	GetCursorPos(MousePos);										// �}�E�X���W(�X�N���[�����W)�擾
	ScreenToClient(*GethWnd(), MousePos);						// �E�B���h�E ���[�J�����W�ɕϊ�

	//----- �ړ��ʂւ̉e���𔽉f -----//
	Move.y += VAL_GRAVITY;

	//----- �}�E�X�J�[�\���Ƃ̓����蔻�� -----//
	if (INPUT_MANAGER::GetMouseButton(BUTTON_LEFT, HOLD) &&
		(Pos.x - MousePos->x) * (Pos.x - MousePos->x) + (Pos.y - MousePos->y) * (Pos.y - MousePos->y) <= 
		(PLAYER_RADIUS + 20) * (PLAYER_RADIUS + 20))
	{
		//�|�W�V�����̍X�V
		Pos.x = MousePos->x;
		Pos.y = MousePos->y;
		//�d�̖͂���
		Move.y = 0.0f;
		//�͂܂ꂽ�A�j���[�V����
		Anim = 1;
	}
	else
	{
		//�ʏ�A�j���[�V����
		Anim = 0;
	}
	//-----�A�j���[�V����-----//
	//�A�j���[�V�����X�V
	++AnimCnt;
	if (AnimCnt >= g_animPat[Anim][AnimPat].Count)
	{
		AnimCnt = 0;
		++AnimPat;

		if (g_animPat[Anim][AnimPat].Frame < 0)
		{
			AnimPat = 0;
		}
	}
	// �A�j���[�V�����ݒ�
	SetPlayerAnimFrame(g_animPat[Anim][AnimPat].Frame);

	//----- ���W���f -----//
	for (int i = 0; i < 4; ++i)
	{
		pVertex[i].Position.x = Pos.x + (i & 1) * PLAYER_WIDTH - PLAYER_WIDTH / 2;
		pVertex[i].Position.y = Pos.y + (i >> 1) * PLAYER_HEIGHT - PLAYER_HEIGHT / 2;
	}

	//----- �ʒu���X�V -----//
	Pos.x += Move.x;
	Pos.y += Move.y;

	//----- �ړ��͈͐��� -----//
	if (Pos.x + PLAYER_WIDTH / 2.0f > SCREEN_WIDTH)			//�E�[
	{
		Pos.x = SCREEN_WIDTH - PLAYER_WIDTH / 2.0f;
	}
	else if (Pos.x - PLAYER_WIDTH / 2.0f < 0)				//���[
	{
		Pos.x = PLAYER_WIDTH / 2.0f;
	}
	if (Pos.y > SCREEN_HEIGHT - PLAYER_HEIGHT / 2)			//���[
	{
		Pos.y = SCREEN_HEIGHT - PLAYER_HEIGHT / 2;
		Move.y = 0.0f;
	}
}
