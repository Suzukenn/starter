//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Collision.h"
#include "GameScene.h"
#include "Main.h"

//�������萔�E�}�N����`������//

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
bool COLLISION::CheckPlayer(D3DXVECTOR2 player_pos, float radius)
{
    //---�e��錾---//
    int nCounter;
    float fDotAA;
    float fDotAV;
    float fS;
    float fSq;
    D3DXVECTOR2 vRayVector;
    D3DXVECTOR2 vOrigin;
    float Angle = 0.0F;
    const D3DXVECTOR2 vCameraVector[4] = { {1.0F, 1.0F}, {-1.0F,-1.0F}, {-1.0F, -1.0F}, {1.0F, -1.0F} };

    //---����������---//
    nCounter = 0;
    vOrigin = { SCREEN_CENTER_X, 10.0F };
    vRayVector = { Angle, SCREEN_HEIGHT };
    vRayVector.x *= vCameraVector[(int)(Angle / 90.0F)].x;
    vRayVector.y *= vCameraVector[(int)(Angle / 90.0F)].y;

    //���a���}�C�i�X�̓G���[�i���a�[���͋��e�j
    if (radius < 0.0F)
    {
        return false;
    }

    //�~�̒��S�_�����_�ɂȂ�悤�Ɏn�_���I�t�Z�b�g
    vOrigin -= player_pos;

    for (nCounter = 0; nCounter < 3; nCounter++)
    {
        //���C�̕����x�N�g���𐳋K��
        vRayVector /= sqrtf(vRayVector.x * vRayVector.x + vRayVector.y * vRayVector.y);

        //�W��t���Z�o
        fDotAV = vOrigin.x * vRayVector.x + vOrigin.y * vRayVector.y;
        fDotAA = vOrigin.x * vOrigin.x + vOrigin.y * vOrigin.y;
        fS = fDotAV * fDotAV - fDotAA + radius * radius;

        //�덷�C��
        if (fabsf(fS) < 0.000001F)
        {
            fS = 0.0F;
        }

        //�Փ˂��Ă��Ȃ�
        if (fS < 0.0F)
        {
            vRayVector = { Angle + 15.0F * (nCounter + 1), SCREEN_HEIGHT };
            vRayVector *= *vCameraVector[(int)(Angle / 90.0F)];
            continue;
        }

        fSq = sqrtf(fS);

        //����t1�y��t2���}�C�i�X��������n�_���~���ɂ߂荞��ł���̂ŃG���[�Ƃ���
        if ((-fDotAV - fSq) < 0.0F || (-fDotAV + fSq) < 0.0F)
        {
            vRayVector = { Angle + 15.0F * (nCounter + 1), SCREEN_HEIGHT };
            vRayVector *= *vCameraVector[(int)(Angle / 90.0F)];
        }
        else
        {
            return true;
        }
    }
    return false;

    //const D3DXVECTOR2 poVertex[3] = { { player_pos.x, player_pos.y },{ player_pos.x + 50.0F, SCREEN_HEIGHT },{ player_pos.x - 50.0F, SCREEN_HEIGHT } };
    //return false;
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
HRESULT COLLISION::Initialize(D3DXVECTOR2 position)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();
    Position[0] = { position.x, position.y };
    Position[1] = { position.x + 50.0F, SCREEN_HEIGHT };
    Position[2] = { position.x - 50.0F, SCREEN_HEIGHT };

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
        Vertex[nCounter].Position.x = Position[nCounter].x;
        Vertex[nCounter].Position.y = Position[nCounter].y;
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
//�@�\�F�J�����̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void COLLISION::Uninitialize(void)
{
    //---���---//
    SAFE_RELEASE(VertexBuffer);
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
void COLLISION::Update(void)
{

}