//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Camera.h"
#include "Main.h"

//�������萔�E�}�N����`������//
#define FILE_CAMERAPATH L"Data/Game/Camera.tga" //�p�X��
#define FILE_ROOTCAMERA L"Data/Game/RootCamera.tga" //�p�X��
#define SIZE 50.0F

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FCheckDeadAngle
//
//�@�\�F�v���C���[�̎��p������
//
//�����F�Ȃ�
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool CAMERA::CheckDeadAngle(D3DXVECTOR2 player_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 lift_pos, D3DXVECTOR2 lift_size)
{
    //---�e��錾---//
    bool bJudge;
    D3DXVECTOR2 vecDifferential;

    vecDifferential = lift_size - Position;
    return false;
}

/////////////////////////////////////////////
//�֐����FCheckPlayer
//
//�@�\�F�v���C���[�̎���p������
//
//�����F(D3DXVECTOR2)�v���C���[�̈ʒu,(D3DXVECTOR2)�v���C���[�̑傫��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool CAMERA::CheckPlayer(D3DXVECTOR2 player_pos, D3DXVECTOR2 size)
{
    return Collision.CheckPlayer(player_pos, size);
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�J�����̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CAMERA::Draw(void)
{
    //---�����蔻��`��---//
    Collision.Draw();

    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�����蔻��̕`��---//
    Collision.Draw();

    //---�����ݒ�---//
	pDevice->SetFVF(FVF_VERTEX);       //�t�H�[�}�b�g�ݒ�

    //---�J�����x���`��---//
    pDevice->SetTexture(0, GraphicRoot);   //�e�N�X�`���ݒ�
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, VertexRoot, sizeof(VERTEX));

    //---�J�����`��---//
	pDevice->SetTexture(0, Graphic);   //�e�N�X�`���ݒ�
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertex, sizeof(VERTEX));
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�J�����̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT CAMERA::Initialize(D3DXVECTOR2 position, float angle)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();
    Position = position;
    Center = { SIZE / 2, SIZE / 2 };
    Angle = angle;

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = D3DXCreateTextureFromFileW(pDevice, FILE_CAMERAPATH, &Graphic);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"�J�����e�N�X�`���̎擾�Ɏ��s���܂���", FILE_CAMERAPATH, MB_OK);
        Uninitialize();
        return hResult;
    }

    //---���_�o�b�t�@�̐���---//
	hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBuffer, nullptr);

	if (FAILED(hResult))
	{
		MessageBoxW(nullptr, L"���_�o�b�t�@�̐����Ɏ��s���܂���", FILE_CAMERAPATH, MB_OK);
		Uninitialize();
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
		Vertex[nCounter].Position.x = Position.x + Vertex[nCounter].U * SIZE;
		Vertex[nCounter].Position.y = Position.y + Vertex[nCounter].V * SIZE;
		Vertex[nCounter].Position.z = 0.0F;
		Vertex[nCounter].RHW = 1.0F;
		Vertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

    //�o�b�t�@�̃|�C���^�̉��
    VertexBuffer->Unlock();

	//---�e�N�X�`���̓ǂݍ���---//
	hResult = D3DXCreateTextureFromFileW(pDevice, FILE_ROOTCAMERA, &GraphicRoot);
	if (FAILED(hResult))
	{
		MessageBoxW(nullptr, L"�J�����̎x���̃e�N�X�`���̎擾�Ɏ��s���܂���", FILE_ROOTCAMERA, MB_OK);
		Uninitialize();
		return hResult;
	}

	//---���_�o�b�t�@�̐���---//
	hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBufferRoot, nullptr);

	if (FAILED(hResult))
	{
		MessageBoxW(nullptr, L"���_�o�b�t�@�̐����Ɏ��s���܂���", FILE_ROOTCAMERA, MB_OK);
		Uninitialize();
		return hResult;
	}

	//---���_�o�b�t�@�ւ̒l�̐ݒ�---//
	//�o�b�t�@�̃|�C���^���擾
	VertexBufferRoot->Lock(0, 0, (void**)&VertexRoot, 0);

	//�l�̐ݒ�
	for (nCounter = 0; nCounter < 4; nCounter++)
	{
		VertexRoot[nCounter].U = (float)(nCounter & 1);
		VertexRoot[nCounter].V = (float)((nCounter >> 1) & 1);
		VertexRoot[nCounter].Position.x = Vertex[nCounter].Position.x - 26.5F;
		VertexRoot[nCounter].Position.y = Vertex[nCounter].Position.y + 10.0F;
		VertexRoot[nCounter].Position.z = 0.0F;
		VertexRoot[nCounter].RHW = 1.0F;
		VertexRoot[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	//�o�b�t�@�̃|�C���^�̉��
	VertexBufferRoot->Unlock();

	//�����蔻��̏�����
    hResult = Collision.Initialize();
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"�J�����̏������Ɏ��s���܂���", L"�����蔻��", MB_OK);
        Uninitialize();
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�J�����̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CAMERA::Uninitialize(void)
{
    Collision.Uninitialize();

    //---���---//
	SAFE_RELEASE(VertexBuffer);
	SAFE_RELEASE(Graphic);
	SAFE_RELEASE(VertexBufferRoot);
	SAFE_RELEASE(GraphicRoot);
	Vertex = nullptr;
	VertexRoot = nullptr;
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�J�����̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CAMERA::Update(void)
{
    //---�e��錾---//
    int nCounter;
    float fCosine;
    float fDx;
    float fDy;
    float fSin;

    fCosine = cosf(D3DXToRadian(Angle));
    fSin = sinf(D3DXToRadian(Angle));

    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        fDx = (nCounter % 2) * SIZE - Center.x;
        fDy = (nCounter / 2) * SIZE - Center.y;

        Vertex[nCounter].Position.x = (Position.x + (fDx * fCosine - fDy * fSin)) + SIZE / 2;
        Vertex[nCounter].Position.y = (Position.y + (fDx * fSin + fDy * fCosine)) + SIZE / 2;
    }

    Collision.SetData(Position + Center, Angle);
    Collision.Update();
}