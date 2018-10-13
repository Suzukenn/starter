//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "ManualButton.h"
#include "SceneManager.h"
#include "SoundManager.h"

//======�萔�E�}�N����`=====
// �p�X��
#define FILE_PATH	L"Data/Game/ManualButton.png"
//���g���C�{�^���T�C�Y
#define RETRYBUTTON_WIDTH	(120)	//��
#define RETRYBUTTON_HEIGHT	(35)	//����
//�l�p����p
#define RETRYBUTTON_HIT_WIDTH	(80)	//��
#define RETRYBUTTON_HIT_HEIGHT	(25)	//����
//�~����p
#define RETRYBUTTON_RADIUS	(30)

//=====�R���X�g���N�^=====
MANUALBUTTON::MANUALBUTTON()
{
    //���I�m��
    Operation = new OPERATION();
    //�ʒu�ݒ�
    Pos.x = SCREEN_CENTER_X;
    Pos.y = SCREEN_CENTER_Y + 200.0F;
}

//=====�f�X�g���N�^=====
MANUALBUTTON::~MANUALBUTTON()
{
    //���
    if (Operation)
    {
        delete Operation;
    }
}

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�}�j���A���{�^���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void MANUALBUTTON::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�����ݒ�---//
    pDevice->SetFVF(FVF_VERTEX);                                  //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, Graphic);                                 //�e�N�X�`���ݒ�

    //--- ���W���f ---//
    for (int i = 0; i < 4; ++i)
    {
        pVertex[i].Position.x = Pos.x + (i % 2) * RETRYBUTTON_WIDTH - RETRYBUTTON_WIDTH / 2;
        pVertex[i].Position.y = Pos.y + (i / 2) * RETRYBUTTON_HEIGHT - RETRYBUTTON_HEIGHT / 2;
    }

    // ���_�z��ɂ��|���S���`��
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(pVertex[0]));
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�}�j���A���{�^���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT MANUALBUTTON::Initialize(void)
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
        pVertex[nCounter].Position.x = pVertex[nCounter].U * RETRYBUTTON_WIDTH + Pos.x;
        pVertex[nCounter].Position.y = pVertex[nCounter].V * RETRYBUTTON_HEIGHT + Pos.y;
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
//�@�\�F�}�j���A���{�^���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void MANUALBUTTON::Uninitialize(void)
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

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�}�j���A���{�^���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void MANUALBUTTON::Update(void)
{
    //----- �e��錾 -----
    POINT* MousePos = Operation->GetMousePos();
    GetCursorPos(MousePos);										// �}�E�X���W(�X�N���[�����W)�擾
    ScreenToClient(*GethWnd(), MousePos);						// �E�B���h�E ���[�J�����W�ɕϊ�

    //���g���C�{�^���ƃ}�E�X�J�[�\���̓����蔻��
    if (INPUT_MANAGER::GetMouseButton(BUTTON_LEFT, TRIGGER) &&
        (Pos.x - RETRYBUTTON_HIT_WIDTH <= MousePos->x + OPERATION_HIT_WIDTH && MousePos->x - OPERATION_HIT_WIDTH
            <= Pos.x + RETRYBUTTON_HIT_WIDTH && Pos.y - RETRYBUTTON_HIT_HEIGHT
            <= MousePos->y + OPERATION_HIT_HEIGHT && MousePos->y - OPERATION_HIT_HEIGHT <= Pos.y + RETRYBUTTON_HIT_HEIGHT))
    {
        //�Q�[���V�[���ؑ�
        SCENE_MANAGER::SetScene(SCENE_MANUAL);

        //---���艹�Đ�---//
        SOUND_MANAGER::Play(SE_DECISION);
    }
}