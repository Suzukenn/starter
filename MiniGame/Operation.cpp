//
//	Operation.cpp
//

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"
#include "Operation.h"

//======�萔�E�}�N����`=====
// �p�X��
#define FILE_PATH	L"Data/Game/hand.png"
//�v���C���[�T�C�Y
#define OPERATION_WIDTH	(30)	//��
#define OPERATION_HEIGHT	(30)	//����
//#define OPERATION_HITBOX_WIDTH		(50)
//#define OPERATION_HITBOX_HEIGHT	(64)
//�~����p
#define OPERATION_RADIUS	(30)

//=====�R���X�g���N�^=====
OPERATION::OPERATION()
{
	//�ʒu�ݒ�
	Pos.x = 0.0f;
	Pos.y = 0.0f;
}

//=====�f�X�g���N�^=====
OPERATION::~OPERATION()
{
	
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
HRESULT OPERATION::Initialize(void)
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
		pVertex[nCounter].Position.x = pVertex[nCounter].U * OPERATION_WIDTH + Pos.x;
		pVertex[nCounter].Position.y = pVertex[nCounter].V * OPERATION_HEIGHT + Pos.y;
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
void OPERATION::Uninitialize(void)
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
void OPERATION::Draw(void)
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
void OPERATION::Update(void)
{
	//---�e��錾---//
	GetCursorPos(&Pos);									// �}�E�X���W(�X�N���[�����W)�擾
	ScreenToClient(*GethWnd(), &Pos);					// �E�B���h�E ���[�J�����W�ɕϊ�

	//---���W���f---//
	for (int i = 0; i < 4; ++i)
	{
		pVertex[i].Position.x = Pos.x + (i & 1) * OPERATION_WIDTH - OPERATION_WIDTH / 2;
		pVertex[i].Position.y = Pos.y + (i >> 1) * OPERATION_HEIGHT - OPERATION_HEIGHT / 2;
	}
}

/////////////////////////////////////////////
//�֐����FGetMousePos
//
//�@�\�F�}�E�X�̍��W�̃Q�b�^�[
//
//�����F�Ȃ�
//
//�߂�l�F(D3DXVECTOR2*)�}�E�X�J�[�\���̈ʒu�|�C���^
/////////////////////////////////////////////
POINT* OPERATION::GetMousePos(void)
{
	return &Pos;
}