#ifndef _SOUND_PARAMETER_H_
#define _SOUND_PARAMETER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <string>
#include "Main.h"

//�������\���̐錾������//
typedef struct
{
    std::wstring FileName;	//�t�@�C����
    UINT32 LoopCount;		//���[�v�J�E���g
}SOUND_PARAMETER;

#endif