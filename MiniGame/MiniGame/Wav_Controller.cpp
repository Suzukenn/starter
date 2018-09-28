//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Wav_Controller.h"

/////////////////////////////////////////////
//�֐����FLoad
//
//�@�\�F�f�[�^�̃��[�h
//
//�����F(LPCWSTR)�t�@�C���p�X
//
//�߂�l�F(bool)�����̐���
/////////////////////////////////////////////
bool WAV_CONTROLLER::Load(LPCWSTR filepath)
{
    //---�e��錾---//
    LONG lSize;
    MMRESULT mResult;

    //---�ǂݎ����---//
	//�t�@�C���I�[�v��
    Mmio = mmioOpenW((LPWSTR)filepath, &MmioInfo, MMIO_READ);
    if (!Mmio)
    {
        MessageBoxW(nullptr, L"���y�t�@�C�����J���܂���ł���", filepath, MB_ICONSTOP | MB_OK);
        return false;
    }

    //RIFF�`�����N�̌���
    RiffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    mResult = mmioDescend(Mmio, &RiffChunk, nullptr, MMIO_FINDRIFF);
    if (mResult != MMSYSERR_NOERROR)
    {
        MessageBoxW(nullptr, L"RIFF�`�����N��������܂���ł���", filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

    //�t�H�[�}�b�g�`�����N����
    FormatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
    mResult = mmioDescend(Mmio, &FormatChunk, &RiffChunk, MMIO_FINDCHUNK);
    if (mResult != MMSYSERR_NOERROR)
    {
        MessageBoxW(nullptr, L"�t�H�[�}�b�g�`�����N��������܂���ł���", filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

	//WAVEFORMATEX�\���̂Ƀf�[�^��ǂݍ���
    lSize = mmioRead(Mmio, (HPSTR)&WaveFormat, FormatChunk.cksize);

    switch (lSize)
    {
        //�ǂݍ��݌��E
        case 0:
            MessageBoxW(nullptr, L"����ȏ�ǂݍ��߂܂���", filepath, MB_ICONSTOP | MB_OK);
            break;

        //�ǂݎ�莸�s
        case -1:
            MessageBoxW(nullptr, L"�ǂݎ��Ɏ��s���܂���", filepath, MB_ICONSTOP | MB_OK);
            break;

        //�ǂݎ�萬��
        default:
        //�f�[�^�T�C�Y�̊m�F
        if (lSize != FormatChunk.cksize)
        {
            MessageBoxW(nullptr, L"�f�[�^�T�C�Y���Ⴂ�܂�", filepath, MB_ICONSTOP | MB_OK);
            mmioClose(Mmio, 0);
            return false;
        }
    }

    //�ǂݍ��݈ʒu��擪�ɖ߂�
    mmioAscend(Mmio, &FormatChunk, 0);

    //�f�[�^�`�����N����
    DataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
    mResult = mmioDescend(Mmio, &DataChunk, &RiffChunk, MMIO_FINDCHUNK);
    if (mResult != MMSYSERR_NOERROR)
    {
        MessageBoxW(nullptr, L"�f�[�^�`�����N��������܂���ł���", filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

	//�����f�[�^��ǂݍ���
    WaveData.resize(DataChunk.cksize);
    if (mmioRead(Mmio, (HPSTR)&WaveData[0], DataChunk.cksize) != DataChunk.cksize)
    {
        MessageBoxW(nullptr, L"���y�f�[�^��ǂݍ��߂܂���ł���", filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

	//�t�@�C�������
    mmioClose(Mmio, 0);

    return true;
}

/////////////////////////////////////////////
//�֐����FGetFormat
//
//�@�\�F�t�H�[�}�b�g�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(WAVEFORMATEX*)�t�H�[�}�b�g�̃A�h���X
/////////////////////////////////////////////
const WAVEFORMATEX* WAV_CONTROLLER::GetFormat(void)
{
	return &WaveFormat;
}

/////////////////////////////////////////////
//�֐����FGetLoop
//
//�@�\�F���[�v���̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(UINT32*)�t�H�[�}�b�g�̃A�h���X
/////////////////////////////////////////////
const UINT32 WAV_CONTROLLER::GetLoop(void)
{
    return LoopCount;
}

/////////////////////////////////////////////
//�֐����FGetWaveData
//
//�@�\�FWav�f�[�^�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(BYTE*)Wav�f�[�^�̃A�h���X
/////////////////////////////////////////////
const BYTE* WAV_CONTROLLER::GetWaveData(void)
{
	return &WaveData[0];
}

/////////////////////////////////////////////
//�֐����FGetWaveSize
//
//�@�\�F�f�[�^�T�C�Y�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(size_t*)�f�[�^�T�C�Y�̃A�h���X
/////////////////////////////////////////////
const std::size_t WAV_CONTROLLER::GetWaveSize(void)
{
	return WaveData.size();
}