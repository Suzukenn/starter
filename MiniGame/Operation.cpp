//
//	Operation.cpp
//

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "Operation.h"

//======�萔�E�}�N����`=====
// �p�X��
#define FILE_PATH	L"Data/Game/hand.png"

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

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F����|�C���^�̕`��
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
    pDevice->SetTexture(0, Graphic);                              //�e�N�X�`���ݒ�

    // ���_�z��ɂ��|���S���`��
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertex, sizeof(VERTEX));
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F����|�C���^�̏�����
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
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);

	//�l�̐ݒ�
	for (nCounter = 0; nCounter < 4; nCounter++)
	{
        Vertex[nCounter].U = (float)(nCounter & 1);
        Vertex[nCounter].V = (float)((nCounter >> 1) & 1);
        Vertex[nCounter].Position.x = Vertex[nCounter].U * OPERATION_WIDTH + Pos.x;
        Vertex[nCounter].Position.y = Vertex[nCounter].V * OPERATION_HEIGHT + Pos.y;
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
//�@�\�F����|�C���^�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void OPERATION::Uninitialize(void)
{
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(Graphic);
    Vertex = nullptr;
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F����|�C���^�̍X�V
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
        Vertex[i].Position.x = Pos.x + (i & 1) * OPERATION_WIDTH - OPERATION_WIDTH / 2;
        Vertex[i].Position.y = Pos.y + (i >> 1) * OPERATION_HEIGHT - OPERATION_HEIGHT / 2;
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