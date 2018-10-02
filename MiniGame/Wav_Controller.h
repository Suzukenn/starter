#ifndef _WAV_CONTROLLER_H_
#define _WAV_CONTROLLER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <vector>
#include "Main.h"

//�������N���X�錾������//
class WAV_CONTROLLER
{
	private:
		HMMIO				Mmio;		    //MMIO�n���h��
		MMIOINFO			MmioInfo;	    //MMIO���\����
		MMCKINFO			RiffChunk;	    //RIFF�`�����N
		MMCKINFO			FormatChunk;	//�t�H�[�}�b�g�`�����N
		MMCKINFO			DataChunk;	    //DATA �`�����N
		WAVEFORMATEX		WaveFormat;	    //WAV�t�H�[�}�b�g�\����	
		std::vector<BYTE>	WaveData;		//���y�f�[�^	
        UINT32			    LoopCount;		//���[�v�Đ�
		
	public:
		bool Load(LPCWSTR);

		const WAVEFORMATEX* GetFormat(void);
        const UINT32 GetLoop(void);
		const BYTE* GetWaveData(void);
		const std::size_t GetWaveSize(void);
};

#endif