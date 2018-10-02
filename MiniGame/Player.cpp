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

//=====�R���X�g���N�^=====
PLAYER::PLAYER()
{
	//���I�m��
	Operation = new OPERATION();
	//�ʒu�ݒ�
	Pos.x = SCREEN_CENTER_X;
	Pos.y = SCREEN_CENTER_Y;
    Hit = false;
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
		MessageBoxW(nullptr, L"�v���C���[�̏������Ɏ��s���܂���", FILE_PATH, MB_OK);
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
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);

	//�l�̐ݒ�
	for (nCounter = 0; nCounter < 4; nCounter++)
	{
        Vertex[nCounter].U = (float)(nCounter & 1);
        Vertex[nCounter].V = (float)((nCounter >> 1) & 1);
        Vertex[nCounter].Position.x = Vertex[nCounter].U * PLAYER_WIDTH + Pos.x;
        Vertex[nCounter].Position.y = Vertex[nCounter].V * PLAYER_HEIGHT + Pos.y;
        Vertex[nCounter].Position.z = 0.0F;
        Vertex[nCounter].RHW = 1.0F;
        Vertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
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
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(Graphic)
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
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertex, sizeof(VERTEX));
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
	//----- �e��錾 -----
	POINT* MousePos = Operation->GetMousePos();
	GetCursorPos(MousePos);										// �}�E�X���W(�X�N���[�����W)�擾
	ScreenToClient(*GethWnd(), MousePos);						// �E�B���h�E ���[�J�����W�ɕϊ�

	//----- �ړ��ʂւ̉e���𔽉f -----
	Move.y += VAL_GRAVITY;

	if (INPUT_MANAGER::GetMouseButton(BUTTON_LEFT, HOLD) &&
		(Pos.x - MousePos->x) * (Pos.x - MousePos->x) + (Pos.y - MousePos->y) * (Pos.y - MousePos->y) <= 
		(PLAYER_RADIUS + 20) * (PLAYER_RADIUS + 20))
	{
		//�|�W�V�����̍X�V
		Pos.x = MousePos->x;
		Pos.y = MousePos->y;
		//�d�̖͂���
		Move.y = 0.0f;
	}

	//----- ���W���f -----
	for (int i = 0; i < 4; ++i)
	{
        Vertex[i].Position.x = Pos.x + (i & 1) * PLAYER_WIDTH - PLAYER_WIDTH / 2;
        Vertex[i].Position.y = Pos.y + (i >> 1) * PLAYER_HEIGHT - PLAYER_HEIGHT / 2;

        //---�����蔻��---//
        if (INPUT_MANAGER::GetMouseButton(BUTTON_LEFT, HOLD))
        {
            Vertex[i].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
            continue;
        }

        if (Hit)
        {
            Vertex[i].Diffuse = D3DCOLOR_ARGB(128, 255, 255, 255);
        }
        else
        {
            Vertex[i].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
        }
	}

	//----- �ʒu���X�V -----
	Pos.x += Move.x;
	Pos.y += Move.y;

	//----- �ړ��͈͐��� -----
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
