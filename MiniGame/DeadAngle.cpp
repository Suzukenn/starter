//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "DeadAngle.h"
#include "Main.h"

//�������萔�E�}�N����`������//
#define VIEW_ANGLE 15.0F

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FCheckDeadAngle
//
//�@�\�F�v���C���[�̎��p������
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
bool DEADANGLE::CheckDeadAngle(D3DXVECTOR2 player_pos, D3DXVECTOR2 size)
{
    //---�e��錾---//
    int nCounter;
    double dCorner1;
    double dCorner2;
    double dCorner3;
    double dCorner4;
    D3DXVECTOR2 vecAB;
    D3DXVECTOR2 vecBC;
    D3DXVECTOR2 vecCD;
    D3DXVECTOR2 vecDA;
    D3DXVECTOR2 vecAP;
    D3DXVECTOR2 vecBP;
    D3DXVECTOR2 vecCP;
    D3DXVECTOR2 vecDP;

    D3DXVECTOR2 vecPlayerVertex[4];

    //---����������---//
    vecPlayerVertex[0] = player_pos;
    vecPlayerVertex[1] = { player_pos.x + size.x, player_pos.y };
    vecPlayerVertex[2] = player_pos + size;
    vecPlayerVertex[3] = { player_pos.x, player_pos.y + size.y };

    //---����---//
    for (nCounter = 0; nCounter < 4; nCounter++)
    {
        //�����x�N�g���v�Z
        vecAB = Position[0] - Position[1];
        vecBP = vecPlayerVertex[nCounter] - Position[0];

        vecBC = Position[1] - Position[2];
        vecCP = vecPlayerVertex[nCounter] - Position[1];

        vecCD = Position[2] - Position[3];
        vecDP = vecPlayerVertex[nCounter] - Position[2];

        vecCD = Position[3] - Position[0];
        vecAP = vecPlayerVertex[nCounter] - Position[3];

        //�O�ς̌v�Z
        dCorner1 = vecAB.x * vecBP.y - vecAB.y * vecBP.x;
        dCorner2 = vecBC.x * vecCP.y - vecBC.y * vecCP.x;
        dCorner3 = vecCD.x * vecDP.y - vecCD.y * vecDP.x;
        dCorner4 = vecDA.x * vecAP.y - vecDA.y * vecAP.x;

        //����
        if ((dCorner1 > 0 && dCorner2 > 0 && dCorner3 > 0 && dCorner4 > 0) || (dCorner1 < 0 && dCorner2 < 0 && dCorner3 < 0 && dCorner4 < 0))
        {
            return true;
        }
    }

    return false;
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F���p�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void DEADANGLE::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�����ݒ�---//
    pDevice->SetFVF(FVF_VERTEX);       //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, Graphic);   //�e�N�X�`���ݒ�

    //---�`��---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertex, sizeof(VERTEX));
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F���p�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT DEADANGLE::Initialize(void)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = D3DXCreateTextureFromFileW(pDevice, L"Data/Game/BackGround.png", &Graphic);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"���p�p�w�i�̏������Ɏ��s���܂���", L"Data/Game/BackGround.png", MB_OK);
        Uninitialize();
        return hResult;
    }

    //---���_�o�b�t�@�̐���---//
    hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBuffer, nullptr);

    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"���_�o�b�t�@�̐����Ɏ��s���܂���", L"�G���[", MB_OK);
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
        Vertex[nCounter].Position.x = 0.0F;
        Vertex[nCounter].Position.y = 0.0F;
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
//�@�\�F���p�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void DEADANGLE::Uninitialize(void)
{
    //---���---//
    SAFE_RELEASE(Graphic);
    SAFE_RELEASE(VertexBuffer);
    Vertex = nullptr;
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F���p�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void DEADANGLE::Update(void)
{
    //---�e��錾---//
    int nCounter;
    float fWidth1;
    float fWidth2;

    const short nRate[2] = { -1,1 };

    //---����������---//

    //---���_�̎Z�o---//
    for (nCounter = 1; nCounter < 4; nCounter++)
    {
        Position[nCounter].x = Position[0].x + nRate[nCounter & 1] * Size.x;
        Position[nCounter].y = Position[0].y + nRate[nCounter >> 1] * Size.y;
    }

    //---�o�b�t�@�ɔ��f---//
    for (nCounter = 0; nCounter < 3; nCounter++)
    {
        Vertex[nCounter].Position = { Position[nCounter].x, Position[nCounter].y, 0.0F };
        Vertex[nCounter].U = SCREEN_WIDTH / Position[nCounter].x;
        Vertex[nCounter].V = SCREEN_HEIGHT / Position[nCounter].y;
    }
}