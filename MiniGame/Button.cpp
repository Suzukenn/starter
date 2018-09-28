//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <math.h>
#include "button.h"

//�������֐���`������//
///////////////////////////////////
//�֐����FDraw
//
//�@�\�F�{�^���̕`�揈��
//
//�����F(SPRITE_NORMAL*)���W�f�[�^
//
//�߂�l�F�Ȃ�
///////////////////////////////////
void BUTTON::Draw(void)
{	
    //---�e�N�X�`���̐ݒ�---//
    
    //�e�N�X�`���̎擾
    GXLoadTexObj(GetUITex(Texture), GX_TEXMAP0);

    //---�`��---//
    
	//�����`�̐���
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    
	//���_1
	GXPosition2f32(Pos_X, Pos_Y);
	GXColor4u8(255, 255, 255, 255);	
	GXTexCoord2f32(0.0F, 0.0F);
	
	//���_2
	GXPosition2f32(Pos_X + Width, Pos_Y);
	GXColor4u8(255, 255, 255, 255);	
	GXTexCoord2f32(1.0F, 0.0F);
	
	//���_3
	GXPosition2f32(Pos_X + Width, Pos_Y + Height);
	GXColor4u8(255, 255, 255, 255);	
	GXTexCoord2f32(1.0F, 1.0F);
	
	//���_4
	GXPosition2f32(Pos_X, Pos_Y + Height);
	GXColor4u8(255, 255, 255, 255);	
	GXTexCoord2f32(0.0F, 1.0F);
	
    GXEnd();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�{�^���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BUTTON::Initialize(float x, float y, float width, float height, UI_TEX texture)
{
    Pos_X = x;
    Pos_Y = y;
    Width = width;
    Height = height;
    Texture = texture;
    D_Pos_X = Pos_X;
    D_Pos_Y = Pos_Y;
    D_Width = Width;
	D_Height = Height;
	Push = false;
}

///////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�{�^���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
///////////////////////////////////
void BUTTON::Update(void)
{	
	//---�f�[�^�̌��J---//
	D_Pos_X = Pos_X;
    D_Pos_Y = Pos_Y;
    D_Width = Width;
	D_Height = Height;
	
	//---���͏�Ԃ̃��Z�b�g---//
	Push = false;
}