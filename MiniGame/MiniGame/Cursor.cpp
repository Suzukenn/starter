//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <revolution.h>
#include <demo.h>
#include <math.h>
#include "button.h"
#include "cursor.h"
#include "sound.h"
#include "soundwii5.h"

//�������֐���`������//
///////////////////////////////////
//�֐����FCheckhit
//
//�@�\�F�I�𔻒�
//
//�����F(BUTTON*)�{�^�����
//
//�߂�l�F(bool)���茋��
///////////////////////////////////
bool CURSOR::CheckPush(BUTTON* button)
{
	//---�e��錾---//
	int nCounter;
	
    for (nCounter = 0; nCounter < 2; nCounter++)
    {		
	    if (Pos_X + Width > button[nCounter].D_Pos_X && Pos_X < button[nCounter].D_Pos_X + button[nCounter].D_Width)
	    {
	        if (Pos_Y + Height > button[nCounter].D_Pos_Y && Pos_Y < button[nCounter].D_Pos_Y + button[nCounter].D_Height)
	        {
	       		button[nCounter].Push = true;
	            return true;
	        }
	    }
    }
    return false;
}

///////////////////////////////////
//�֐����FDraw
//
//�@�\�F�J�[�\���̕`�揈��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
///////////////////////////////////
void CURSOR::Draw(void)
{	
    //---�e�N�X�`���̐ݒ�---//

    //�e�N�X�`���̎擾
    GXLoadTexObj(GetUITex(TEXTURE_UI_CURSOR), GX_TEXMAP0);

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
//�@�\�F�J�[�\���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CURSOR::Initialize(float x, float y, float width, float height, UI_TEX texture)
{
    Pos_X = x;
    Pos_Y = y;
    Width = width;
    Height = height;
    Texture = texture;
    Input = GetKPAD();
}

///////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�J�[�\���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
///////////////////////////////////
void CURSOR::Update(BUTTON* button)
{	
    //---�Ə�����---//
    Pos_X = Input->pos.x * SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2;
    Pos_Y = Input->pos.y * SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2;

    //---�{�^�����͔���---//
    if (Input->trig & KPAD_BUTTON_B)
    {
    	if(CheckPush(button))
    	{
    		PlaySound(SE_SHOT, FALSE);	
    	}
    }
}