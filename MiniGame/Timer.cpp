//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <cmath>
#include "Main.h"
#include "Timer.h"

//�������萔�E�}�N����`������//
#define FILE_PATH L"Data/Game/Number.tga" //�p�X��
#define SIZE 50.0F					//�\���T�C�Y

//�������֐���`������//
///////////////////////////////////
//�֐����FDraw
//
//�@�\�F�X�R�A�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
///////////////////////////////////
void TIMER::Draw(void)
{
    //---�e��錾---//
    int nCounter;
    int nPosLeft;
    int nPosRight;
    float fTexLeft;
    float fTexRight;
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

///////////////////////////////////
//�֐����FEnd
//
//�@�\�F�^�C�}�[�̍폜
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
///////////////////////////////////
void TIMER::Uninitialize(void)
{
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(Graphic);
}

///////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�^�C�}�[�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
///////////////////////////////////
HRESULT TIMER::Initialize(void)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;
    D3DXVECTOR2 vecPosition;

    //---����������---//
    vecPosition = { 746.0F, 5.0F };
    Fream = 600;
    Time = 9;
    pDevice = GetDevice();

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
        Vertex[nCounter].Position.x = vecPosition.x + Vertex[nCounter].U * SIZE;
        Vertex[nCounter].Position.y = vecPosition.y + Vertex[nCounter].V * SIZE;
        Vertex[nCounter].Position.z = 0.0F;
        Vertex[nCounter].RHW = 1.0F;
        Vertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    //�o�b�t�@�̃|�C���^�̉��
    VertexBuffer->Unlock();

    Check = false;

    return hResult;
}

///////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�^�C�}�[�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
///////////////////////////////////
void TIMER::Update(void)
{
    //---�e��錾---//
    int nCounter;
    int nDigits;
    int nWork;

    //---�e�폈��---//

    //�c�t���[���J�E���g
    if (Fream)
    {
        Fream--;
    }
    nWork = Fream / 60;

    //�l���
    Time = nWork % 10;
    for (nCounter = 0; nCounter < 4; nCounter++)
    {
        Vertex[nCounter].U = (float)(Time + (nCounter & 1)) * 0.1F;
    }

    if (Check)
    {
        for (nCounter = 0; nCounter < 4; nCounter++)
        {
            Vertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 0, 0);
        }
    }
}