//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Collision.h"
#include "Main.h"

//�������萔�E�}�N����`������//
#define VIEW_ANGLE 20.0F

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FCheckPlayer
//
//�@�\�F�v���C���[�̎���p������
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
bool COLLISION::CheckPlayer(D3DXVECTOR2 player_pos, D3DXVECTOR2 size)
{
    //---�e��錾---//
    int nCounter;
    double dCorner1;
    double dCorner2;
    double dCorner3;
    D3DXVECTOR2 vecAB;
    D3DXVECTOR2 vecBC;
    D3DXVECTOR2 vecCA;
    D3DXVECTOR2 vecAP;
    D3DXVECTOR2 vecBP;
    D3DXVECTOR2 vecCP;

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

        vecCA = Position[2] - Position[0];
        vecAP = vecPlayerVertex[nCounter] - Position[2];


        //�O�ς̌v�Z
        dCorner1 = vecAB.x * vecBP.y - vecAB.y * vecBP.x;
        dCorner2 = vecBC.x * vecCP.y - vecBC.y * vecCP.x;
        dCorner3 = vecCA.x * vecAP.y - vecCA.y * vecAP.x;

        //����
        if ((dCorner1 > 0 && dCorner2 > 0 && dCorner3 > 0) || (dCorner1 < 0 && dCorner2 < 0 && dCorner3 < 0))
        {
            //���p����
            if (!DeadAngle.CheckDeadAngle(player_pos, size))
            {
                return true;
            }
        }
    }

    return false;
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�����蔻��̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void COLLISION::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�����ݒ�---//
    pDevice->SetFVF(FVF_VERTEX);       //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, nullptr);   //�e�N�X�`���ݒ�

    //---�`��---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, Vertex, sizeof(VERTEX));

    //---���p�̕`��---//
    DeadAngle.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�����蔻��̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT COLLISION::Initialize(void)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---���_�o�b�t�@�̐���---//
    hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX) * 3, 0, FVF_VERTEX, D3DPOOL_MANAGED, &VertexBuffer, nullptr);

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
    for (nCounter = 0; nCounter < 3; nCounter++)
    {
        Vertex[nCounter].U = (float)(nCounter & 1);
        Vertex[nCounter].V = (float)((nCounter >> 1) & 1);
        Vertex[nCounter].Position.x = 0.0F;
        Vertex[nCounter].Position.y = 0.0F;
        Vertex[nCounter].Position.z = 0.0F;
        Vertex[nCounter].RHW = 1.0F;
        Vertex[nCounter].Diffuse = D3DCOLOR_ARGB(128, 255, 255, 255);
    }

    //�o�b�t�@�̃|�C���^�̉��
    VertexBuffer->Unlock();

    DeadAngle.Initialize();

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�����蔻��̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void COLLISION::Uninitialize(void)
{
    //---���---//
    DeadAngle.Uninitialize();
    SAFE_RELEASE(VertexBuffer);
    Vertex = nullptr;
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�����蔻��̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void COLLISION::Update(void)
{
    //---�e��錾---//
    int nCounter;
    float fCosine;
    float fDx;
    float fDy;
    float fSin;
    float fHeight;
    float fWidth1;
    float fWidth2;

    //---����������---//
    fHeight = SCREEN_HEIGHT - Position[0].y;

    //---���_�̎Z�o---//
    fWidth1 = fabsf(fHeight * tanf(D3DXToRadian(VIEW_ANGLE)));
    Position[1] = { Position[0].x + fWidth1, SCREEN_HEIGHT };

    fWidth2 = fabsf(fHeight * tanf(D3DXToRadian(VIEW_ANGLE)));
    Position[2] = { Position[0].x - fWidth2, SCREEN_HEIGHT };

    //---�o�b�t�@�ɔ��f---//
    for (nCounter = 0; nCounter < 3; nCounter++)
    {
        Vertex[nCounter].Position = { Position[nCounter].x, Position[nCounter].y, 0.0F };
    }

    //---��]---//
    if (!Angle)
    {
        return;
    }
    fCosine = cosf(D3DXToRadian(Angle));
    fSin = sinf(D3DXToRadian(Angle));

    for (nCounter = 1; nCounter < 3; nCounter++)
    {
        fDx = (nCounter % 2) * 800.0F;
        fDy = (nCounter / 2) * 800.0F;

        Vertex[nCounter].Position.x = (Position[nCounter].x + (fDx * fCosine - fDy * fSin));
        Vertex[nCounter].Position.y = (Position[nCounter].y + (fDx * fSin + fDy * fCosine));
    }
}