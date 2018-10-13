//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Stage_EasyButton.h"

//======�萔�E�}�N����`=====
// �p�X��
#define FILE_PATH	L"Data/Game/Select_EasyButton.png"
//�X�^�[�g�{�^���T�C�Y
#define STARTBUTTON_WIDTH	(170)	//��
#define STARTBUTTON_HEIGHT	(57)	//����
//�l�p����p
#define STARTBUTTON_HIT_WIDTH	(80)	//��
#define STARTBUTTON_HIT_HEIGHT	(25)	//����
//�~����p
#define STARTBUTTON_RADIUS	(30)

//=====�R���X�g���N�^=====
STAGEEASYBUTTON::STAGEEASYBUTTON()
{
    //���I�m��
    Operation = new OPERATION();
    //�ʒu�ݒ�
    Pos.x = SCREEN_CENTER_X - 200.0F;
    Pos.y = SCREEN_CENTER_Y + 160.0F;
}

//=====�f�X�g���N�^=====
STAGEEASYBUTTON::~STAGEEASYBUTTON()
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
//�@�\�F�X�^�[�g�{�^���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT STAGEEASYBUTTON::Initialize(void)
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
        pVertex[nCounter].Position.x = pVertex[nCounter].U * STARTBUTTON_WIDTH + Pos.x;
        pVertex[nCounter].Position.y = pVertex[nCounter].V * STARTBUTTON_HEIGHT + Pos.y;
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
//�@�\�F�X�^�[�g�{�^���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void STAGEEASYBUTTON::Uninitialize(void)
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

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�X�^�[�g�{�^���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void STAGEEASYBUTTON::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�����ݒ�---//
    pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX)); //���_�����ݒ�
    pDevice->SetFVF(FVF_VERTEX);                                  //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, Graphic);                                 //�e�N�X�`���ݒ�

                                                                     //--- ���W���f ---//
    for (int i = 0; i < 4; ++i)
    {
        pVertex[i].Position.x = Pos.x + (i % 2) * STARTBUTTON_WIDTH - STARTBUTTON_WIDTH / 2;
        pVertex[i].Position.y = Pos.y + (i / 2) * STARTBUTTON_HEIGHT - STARTBUTTON_HEIGHT / 2;
    }

    // ���_�z��ɂ��|���S���`��
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(pVertex[0]));
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�X�^�[�g�{�^���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void STAGEEASYBUTTON::Update(void)
{
    //----- �e��錾 -----
    POINT* MousePos = Operation->GetMousePos();
    GetCursorPos(MousePos);										// �}�E�X���W(�X�N���[�����W)�擾
    ScreenToClient(*GethWnd(), MousePos);						// �E�B���h�E ���[�J�����W�ɕϊ�

                                                                //�X�^�[�g�{�^���ƃ}�E�X�J�[�\���̓����蔻��
    if (INPUT_MANAGER::GetMouseButton(BUTTON_LEFT, TRIGGER) &&
        (Pos.x - STARTBUTTON_HIT_WIDTH <= MousePos->x + OPERATION_HIT_WIDTH && MousePos->x - OPERATION_HIT_WIDTH
            <= Pos.x + STARTBUTTON_HIT_WIDTH && Pos.y - STARTBUTTON_HIT_HEIGHT
            <= MousePos->y + OPERATION_HIT_HEIGHT && MousePos->y - OPERATION_HIT_HEIGHT <= Pos.y + STARTBUTTON_HIT_HEIGHT))
    {
        //�Q�[���V�[���ؑ�
        SCENE_MANAGER::SetScene(SCENE_GAME);

        //---���艹�Đ�---//
        SOUND_MANAGER::Play(SE_DECISION);
    }
}
