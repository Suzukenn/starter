//
//	TitleButton.cpp
//

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Sound_Manager.h"
#include "TitleButton.h"

//======�萔�E�}�N����`=====
// �p�X��
#define FILE_PATH	L"Data/Game/TitleButton.tga"
//�^�C�g���{�^���T�C�Y
#define TITLEBUTTON_WIDTH	(170)	//��
#define TITLEBUTTON_HEIGHT	(57)	//����
//�l�p����p
#define TITLEBUTTON_HIT_WIDTH	(80)	//��
#define TITLEBUTTON_HIT_HEIGHT	(25)	//����
//�~����p
#define TITLEBUTTON_RADIUS	(30)

//=====�R���X�g���N�^=====
TITLEBUTTON::TITLEBUTTON()
{
	//���I�m��
	Operation = new OPERATION();
	//�ʒu�ݒ�
	Pos.x = SCREEN_CENTER_X - 150;
	Pos.y = SCREEN_CENTER_Y + 150;
}

//=====�f�X�g���N�^=====
TITLEBUTTON::~TITLEBUTTON()
{
	//���
	if (Operation)
	{
		delete Operation;
	}
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�^�C�g���{�^���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT TITLEBUTTON::Initialize(void)
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
		pVertex[nCounter].Position.x = pVertex[nCounter].U * TITLEBUTTON_WIDTH + Pos.x;
		pVertex[nCounter].Position.y = pVertex[nCounter].V * TITLEBUTTON_HEIGHT + Pos.y;
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
//�@�\�F�^�C�g���{�^���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLEBUTTON::Uninitialize(void)
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
//�@�\�F�^�C�g���{�^���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLEBUTTON::Draw(void)
{
	//---�e��錾---//
	LPDIRECT3DDEVICE9 pDevice;

	//---����������---//
	pDevice = GetDevice();

	//---�����ݒ�---//
	pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX)); //���_�����ݒ�
	pDevice->SetFVF(FVF_VERTEX);                                  //�t�H�[�}�b�g�ݒ�
	pDevice->SetTexture(0, Graphic);                                 //�e�N�X�`���ݒ�
	
	//--- ���W���f ---//
	for (int i = 0; i < 4; ++i)
	{
		pVertex[i].Position.x = Pos.x + (i % 2) * TITLEBUTTON_WIDTH - TITLEBUTTON_WIDTH / 2;
		pVertex[i].Position.y = Pos.y + (i / 2) * TITLEBUTTON_HEIGHT - TITLEBUTTON_HEIGHT / 2;
	}

	// ���_�z��ɂ��|���S���`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(pVertex[0]));
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�^�C�g���{�^���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLEBUTTON::Update(void)
{
	//----- �e��錾 -----
	POINT* MousePos = Operation->GetMousePos();
	GetCursorPos(MousePos);										// �}�E�X���W(�X�N���[�����W)�擾
	ScreenToClient(*GethWnd(), MousePos);						// �E�B���h�E ���[�J�����W�ɕϊ�

	//�^�C�g���{�^���ƃ}�E�X�J�[�\���̓����蔻��
	if (INPUT_MANAGER::GetMouseButton(BUTTON_LEFT, TRIGGER) &&
		(Pos.x - TITLEBUTTON_HIT_WIDTH <= MousePos->x + OPERATION_HIT_WIDTH && MousePos->x - OPERATION_HIT_WIDTH 
			<= Pos.x + TITLEBUTTON_HIT_WIDTH && Pos.y - TITLEBUTTON_HIT_HEIGHT
			<= MousePos->y + OPERATION_HIT_HEIGHT && MousePos->y - OPERATION_HIT_HEIGHT <= Pos.y + TITLEBUTTON_HIT_HEIGHT))
	{
		//�Q�[���V�[���ؑ�
		SCENE_MANAGER::SetScene(SCENE_TITLE);
	}
}
