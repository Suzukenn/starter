#ifndef _MAIN_H_
#define _MAIN_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

//���������C�u�����̃����N������//
#if 1 //[������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "imm32.lib")
#pragma comment (lib, "winmm.lib")
#endif

//�������萔�E�}�N����`������//
#define FVF_VERTEX (D3DFVF_XYZRHW|D3DFVF_TEX1|D3DFVF_DIFFUSE)    //�e�N�X�`���̃t�H�[�}�b�g
#define SCREEN_HEIGHT 480.0F                                        //�E�C���h�E�̍���
#define SCREEN_WIDTH 854.0F  		                                //�E�C���h�E�̕�
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)                          //�E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	                        //�E�C���h�E�̒��S�x���W

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){x->Release();x = nullptr;}}
#endif

//�������\���̒�`������//
typedef struct
{
    int Frame; //�p�^�[���ԍ�
    int Count; //�t���[����
}MOTION;

typedef struct
{
    D3DVECTOR Position;	    //���_���W
    float RHW;			    //RHW(���1.0F)
    D3DCOLOR Diffuse;	    //���_�J���[(�g�U���ːF=���̖{���̐F)
    float U;                //�e�N�X�`�����WU
    float V;			    //�e�N�X�`�����WV
} VERTEX;

//�������v���g�^�C�v�錾������//
LPDIRECT3DDEVICE9 GetDevice(void);

#endif //_MAIN_H_