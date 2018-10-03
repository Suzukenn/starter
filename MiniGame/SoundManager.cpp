//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <fstream>
#include <string>
#include "Main.h"
#include "SoundManager.h"

//�������萔�E�}�N����`������//
#define FILE_PATH L"Data/Sound/tracklist.txt"

//�������v���g�^�C�v�錾������//
HRESULT Load(SOUND_PARAMETER*);

//�������O���[�o���ϐ�������//
IXAudio2* SOUND_MANAGER::Manager;                                   //�Ǘ��I�u�W�F�N�g
IXAudio2MasteringVoice* SOUND_MANAGER::MasterVoice;                 //�}�X�^�[�{�C�X
IXAudio2SourceVoice* SOUND_MANAGER::SourceVoice[SOUND_LABEL_MAX];   //�\�[�X�{�C�X
WAV_CONTROLLER SOUND_MANAGER::WaveSound[SOUND_LABEL_MAX];          	// WAVE ���y�f�[�^

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FCreateSound
//
//�@�\�F�\�[�X�{�C�X�̍쐬
//
//�����F(SOUNDPARAM)���f�[�^,(int)�i�[�z��ԍ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SOUND_MANAGER::CreateSound(SOUND_PARAMETER data, int nCounter)
{
    //---�f�[�^�̓W�J---//
    //�t�@�C���̎w��m�F
    if (!data.FileName.data())
    {
        MessageBoxW(nullptr, L"�J�����y�t�@�C�����킩��܂���", data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //�f�[�^�̃��[�h
    if(!WaveSound[nCounter].Load(data.FileName.data()))
    {
        MessageBoxW(nullptr, L"�f�[�^�̃��[�h�Ɏ��s���܂���", data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //�\�[�X�{�C�X�̍쐬
    if (FAILED(Manager->CreateSourceVoice(&SourceVoice[nCounter], WaveSound[nCounter].GetFormat())))
    {
        MessageBoxW(nullptr, L"�\�[�X�{�C�X�̍쐬�Ɏ��s���܂���", data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }
    
    return S_OK;
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�}�l�[�W���[�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SOUND_MANAGER::Initialize(void)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;

    SOUND_PARAMETER liList[SOUND_LABEL_MAX];

    //---�I�u�W�F�N�g����---//
    //XAudio2�I�u�W�F�N�g�̍쐬
    hResult = XAudio2Create(&Manager, 0);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���", L"�������G���[", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�}�X�^�[�{�C�X�̐���
    hResult = Manager->CreateMasteringVoice(&MasterVoice);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"�}�X�^�[�{�C�X�̍쐬�Ɏ��s���܂���", L"�������G���[", MB_ICONSTOP | MB_OK);
        SAFE_RELEASE(Manager);
        return hResult;
    }

    //�t�@�C���̐ݒ�
    hResult = Load(liList);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"�g���b�N���X�g�̓ǂݍ��݂Ɏ��s���܂���", L"�������G���[", MB_ICONSTOP | MB_OK);
        SAFE_RELEASE(Manager);
        return hResult;
    }

    //�T�E���h�f�[�^�̍쐬
    for (nCounter = 0; nCounter < SOUND_LABEL_MAX; nCounter++)
    {
        if (FAILED(CreateSound(liList[nCounter], nCounter)))
        {
            MessageBoxW(nullptr, L"�T�E���h�f�[�^�̍쐬�Ɏ��s���܂���", liList[nCounter].FileName.c_str(), MB_ICONSTOP | MB_OK);
            SAFE_RELEASE(Manager);
            return hResult;
        }
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FLoad
//
//�@�\�F�ǂݍ��݃f�[�^�̊i�[
//
//�����F(SOUNDPARAM*)�y�ȃ��X�g
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT Load(SOUND_PARAMETER* list)
{
    //---�e��錾---//
    int nCounter;
    std::string szFileName;
    UINT32 nLoop;
    std::ifstream file(FILE_PATH);

    //---����������---//
    nCounter = 0;

    //---�t�@�C���̓ǂݍ���---//
    if (file.fail())
    {
        MessageBoxW(nullptr, L"�g���b�N���X�g���J���܂���ł���", FILE_PATH, MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //---�f�[�^�̒��o---//
    while (!file.eof())
    {
        file >> szFileName >> nLoop;
        list[nCounter].FileName.resize(szFileName.size());
        list[nCounter].FileName = std::wstring(szFileName.begin(), szFileName.end());
        list[nCounter].LoopCount = nLoop;
        ++nCounter;
    }
    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�}�l�[�W���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SOUND_MANAGER::Uninitialize(void)
{
    //---�e��錾---//
    int nCounter;

    //---���---//
    //�\�[�X�{�C�X�̔j��
    for (nCounter = 0; nCounter < SOUND_LABEL_MAX; nCounter++)
    {
        SourceVoice[nCounter]->Stop(0);
        SourceVoice[nCounter]->DestroyVoice();
        SourceVoice[nCounter] = nullptr;
    }

    //�}�X�^�[�{�C�X�̔j��
    MasterVoice->DestroyVoice();
    MasterVoice = nullptr;

    //XAudio2�I�u�W�F�N�g�̔j��
    SAFE_RELEASE(Manager);
}

/////////////////////////////////////////////
//�֐����FPlay
//
//�@�\�F�T�E���h�̍Đ�
//
//�����F(SOUND_LABEL)�T�E���h��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SOUND_MANAGER::Play(SOUND_LABEL label)
{
    //---�e��錾---//
    XAUDIO2_VOICE_STATE sState;
    XAUDIO2_BUFFER bBuffer;

    //---�o�b�t�@�̒l�ݒ�---//
    memset(&bBuffer, 0, sizeof(XAUDIO2_BUFFER));
    bBuffer.AudioBytes = (UINT)WaveSound[label].GetWaveSize();
    bBuffer.pAudioData = WaveSound[label].GetWaveData();
    bBuffer.Flags = XAUDIO2_END_OF_STREAM;
    bBuffer.LoopCount = XAUDIO2_LOOP_INFINITE * WaveSound[label].GetLoop();

    //---��Ԏ擾---//
    SourceVoice[label]->GetState(&sState);

    //---�Đ�����---//
    if (sState.BuffersQueued)
    {
        //�ꎞ��~
        SourceVoice[label]->Stop(0);

        //�I�[�f�B�I�o�b�t�@�̍폜
        SourceVoice[label]->FlushSourceBuffers();
    }

    //---�I�[�f�B�I�o�b�t�@�̓o�^---//
    SourceVoice[label]->SubmitSourceBuffer(&bBuffer);

    //---�Đ�---//
    SourceVoice[label]->Start(0);
}

/////////////////////////////////////////////
//�֐����FStop
//
//�@�\�F�T�E���h�̈ꎞ��~
//
//�����F(SOUND_LABEL)�T�E���h��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SOUND_MANAGER::Pause(SOUND_LABEL label)
{
    //---�e��錾---//
    XAUDIO2_VOICE_STATE sState;

    //---�Đ�����---//
    SourceVoice[label]->GetState(&sState);

    //---�Đ�����---//
    if (sState.BuffersQueued)
    {
        //---�ꎞ��~---//
        SourceVoice[label]->Stop(0);
    }
}

/////////////////////////////////////////////
//�֐����FStop
//
//�@�\�F�T�E���h�̒�~
//
//�����F(SOUND_LABEL)�T�E���h��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SOUND_MANAGER::Stop(SOUND_LABEL label)
{
    //---�e��錾---//
    XAUDIO2_VOICE_STATE sState;

    //��Ԏ擾
    SourceVoice[label]->GetState(&sState);

    //---�Đ�����---//
    if (sState.BuffersQueued)
    {
        //�ꎞ��~
        SourceVoice[label]->Stop(0);

        //�I�[�f�B�I�o�b�t�@�̍폜
        SourceVoice[label]->FlushSourceBuffers();
    }
}