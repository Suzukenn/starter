//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Camera.h"
#include "Main.h"

//�������萔�E�}�N����`������//
#define FILE_PATH L"Data/Game/Camera.png" //�p�X��
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
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�����蔻��̕`��---//
    Collision.Draw();

    //---�����ݒ�---//
    pDevice->SetFVF(FVF_VERTEX);       //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, Graphic);   //�e�N�X�`���ݒ�

    //---�`��---//
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
HRESULT CAMERA::Initialize(void)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();
    Position = { SCREEN_CENTER_X, 50.0F };
    Center = { SIZE / 2, SIZE / 2 };
    Angle = 45.0F;

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = D3DXCreateTextureFromFileW(pDevice, FILE_PATH, &Graphic);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"�J�����e�N�X�`���̎擾�Ɏ��s���܂���", FILE_PATH, MB_OK);
        Uninitialize();
        return hResult;
    }

    //---���_�o�b�t�@�̐���---//
    hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBuffer, nullptr);

    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"���_�o�b�t�@�̐����Ɏ��s���܂���", FILE_PATH, MB_OK);
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

    //�����蔻��̏�����
    hResult = Collision.Initialize(Center);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"�J�����̏������Ɏ��s���܂���", FILE_PATH, MB_OK);
        Uninitialize();
        return hResult;
    }

    Collision.Initialize({ Position.x + SIZE / 2, Position.y + SIZE });

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
    Vertex = nullptr;
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