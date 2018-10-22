//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "Lift.h"
#include "Main.h"

//�������萔�E�}�N����`������//
#define FILE_PATH L"Data/Game/Lift.tga" //�p�X��

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FCheckDeadAngle
//
//�@�\�F�v���C���[�̎��p������
//
//�����F(D3DXVECTOR2)�v���C���[�̈ʒu,(D3DXVECTOR2)�v���C���[�̑傫��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool LIFT::CheckDeadAngle(D3DXVECTOR2 player_pos, D3DXVECTOR2 size)
{
    return DeadAngle.CheckDeadAngle(player_pos, size);
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F���t�g�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void LIFT::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�����ݒ�---//
    pDevice->SetFVF(FVF_VERTEX);        //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, Graphic);    //�e�N�X�`���ݒ�

    //---�`��---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertex, sizeof(VERTEX));

    //---���p�̕`��---//
    DeadAngle.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F���t�g�̏�����
//
//�����F(D3DXVECTOR2)�ʒu
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT LIFT::Initialize(D3DXVECTOR2 position)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();
    Position = position;
    Size = { 170.0F,20.0F };
    Center = { Position.x + Size.x / 2, Position.y + Size.y / 2 };

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = D3DXCreateTextureFromFileW(pDevice, FILE_PATH, &Graphic);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"���t�g�e�N�X�`���̎擾�Ɏ��s���܂���", FILE_PATH, MB_OK);
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
        Vertex[nCounter].Position.x = Position.x + Vertex[nCounter].U * Size.x;
        Vertex[nCounter].Position.y = Position.y + Vertex[nCounter].V * Size.y;
        Vertex[nCounter].Position.z = 0.0F;
        Vertex[nCounter].RHW = 1.0F;
        Vertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    //�o�b�t�@�̃|�C���^�̉��
    VertexBuffer->Unlock();

    DeadAngle.Initialize();

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F���t�g�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void LIFT::Uninitialize(void)
{
    //---���---//
    DeadAngle.Uninitialize();
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(Graphic);
    Vertex = nullptr;
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F���t�g�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void LIFT::Update(void)
{
    DeadAngle.SetData({ Position.x, Position.y + Size.y }, {Size.x, SCREEN_HEIGHT - (Position.y + Size.y) });
    DeadAngle.Update();
}