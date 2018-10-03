//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <fstream>
#include <string>
#include "Main.h"
#include "SoundManager.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define FILE_PATH L"Data/Sound/tracklist.txt"

//＝＝＝プロトタイプ宣言＝＝＝//
HRESULT Load(SOUND_PARAMETER*);

//＝＝＝グローバル変数＝＝＝//
IXAudio2* SOUND_MANAGER::Manager;                                   //管理オブジェクト
IXAudio2MasteringVoice* SOUND_MANAGER::MasterVoice;                 //マスターボイス
IXAudio2SourceVoice* SOUND_MANAGER::SourceVoice[SOUND_LABEL_MAX];   //ソースボイス
WAV_CONTROLLER SOUND_MANAGER::WaveSound[SOUND_LABEL_MAX];          	// WAVE 音楽データ

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：CreateSound
//
//機能：ソースボイスの作成
//
//引数：(SOUNDPARAM)元データ,(int)格納配列番号
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SOUND_MANAGER::CreateSound(SOUND_PARAMETER data, int nCounter)
{
    //---データの展開---//
    //ファイルの指定確認
    if (!data.FileName.data())
    {
        MessageBoxW(nullptr, L"開く音楽ファイルがわかりません", data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //データのロード
    if(!WaveSound[nCounter].Load(data.FileName.data()))
    {
        MessageBoxW(nullptr, L"データのロードに失敗しました", data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //ソースボイスの作成
    if (FAILED(Manager->CreateSourceVoice(&SourceVoice[nCounter], WaveSound[nCounter].GetFormat())))
    {
        MessageBoxW(nullptr, L"ソースボイスの作成に失敗しました", data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }
    
    return S_OK;
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：マネージャーの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SOUND_MANAGER::Initialize(void)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;

    SOUND_PARAMETER liList[SOUND_LABEL_MAX];

    //---オブジェクト準備---//
    //XAudio2オブジェクトの作成
    hResult = XAudio2Create(&Manager, 0);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"XAudio2オブジェクトの作成に失敗しました", L"初期化エラー", MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //マスターボイスの生成
    hResult = Manager->CreateMasteringVoice(&MasterVoice);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"マスターボイスの作成に失敗しました", L"初期化エラー", MB_ICONSTOP | MB_OK);
        SAFE_RELEASE(Manager);
        return hResult;
    }

    //ファイルの設定
    hResult = Load(liList);
    if (FAILED(hResult))
    {
        MessageBoxW(nullptr, L"トラックリストの読み込みに失敗しました", L"初期化エラー", MB_ICONSTOP | MB_OK);
        SAFE_RELEASE(Manager);
        return hResult;
    }

    //サウンドデータの作成
    for (nCounter = 0; nCounter < SOUND_LABEL_MAX; nCounter++)
    {
        if (FAILED(CreateSound(liList[nCounter], nCounter)))
        {
            MessageBoxW(nullptr, L"サウンドデータの作成に失敗しました", liList[nCounter].FileName.c_str(), MB_ICONSTOP | MB_OK);
            SAFE_RELEASE(Manager);
            return hResult;
        }
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Load
//
//機能：読み込みデータの格納
//
//引数：(SOUNDPARAM*)楽曲リスト
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT Load(SOUND_PARAMETER* list)
{
    //---各種宣言---//
    int nCounter;
    std::string szFileName;
    UINT32 nLoop;
    std::ifstream file(FILE_PATH);

    //---初期化処理---//
    nCounter = 0;

    //---ファイルの読み込み---//
    if (file.fail())
    {
        MessageBoxW(nullptr, L"トラックリストを開けませんでした", FILE_PATH, MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //---データの抽出---//
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
//関数名：Uninitialize
//
//機能：マネージャーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SOUND_MANAGER::Uninitialize(void)
{
    //---各種宣言---//
    int nCounter;

    //---解放---//
    //ソースボイスの破棄
    for (nCounter = 0; nCounter < SOUND_LABEL_MAX; nCounter++)
    {
        SourceVoice[nCounter]->Stop(0);
        SourceVoice[nCounter]->DestroyVoice();
        SourceVoice[nCounter] = nullptr;
    }

    //マスターボイスの破棄
    MasterVoice->DestroyVoice();
    MasterVoice = nullptr;

    //XAudio2オブジェクトの破棄
    SAFE_RELEASE(Manager);
}

/////////////////////////////////////////////
//関数名：Play
//
//機能：サウンドの再生
//
//引数：(SOUND_LABEL)サウンド名
//
//戻り値：なし
/////////////////////////////////////////////
void SOUND_MANAGER::Play(SOUND_LABEL label)
{
    //---各種宣言---//
    XAUDIO2_VOICE_STATE sState;
    XAUDIO2_BUFFER bBuffer;

    //---バッファの値設定---//
    memset(&bBuffer, 0, sizeof(XAUDIO2_BUFFER));
    bBuffer.AudioBytes = (UINT)WaveSound[label].GetWaveSize();
    bBuffer.pAudioData = WaveSound[label].GetWaveData();
    bBuffer.Flags = XAUDIO2_END_OF_STREAM;
    bBuffer.LoopCount = XAUDIO2_LOOP_INFINITE * WaveSound[label].GetLoop();

    //---状態取得---//
    SourceVoice[label]->GetState(&sState);

    //---再生判定---//
    if (sState.BuffersQueued)
    {
        //一時停止
        SourceVoice[label]->Stop(0);

        //オーディオバッファの削除
        SourceVoice[label]->FlushSourceBuffers();
    }

    //---オーディオバッファの登録---//
    SourceVoice[label]->SubmitSourceBuffer(&bBuffer);

    //---再生---//
    SourceVoice[label]->Start(0);
}

/////////////////////////////////////////////
//関数名：Stop
//
//機能：サウンドの一時停止
//
//引数：(SOUND_LABEL)サウンド名
//
//戻り値：なし
/////////////////////////////////////////////
void SOUND_MANAGER::Pause(SOUND_LABEL label)
{
    //---各種宣言---//
    XAUDIO2_VOICE_STATE sState;

    //---再生判定---//
    SourceVoice[label]->GetState(&sState);

    //---再生判定---//
    if (sState.BuffersQueued)
    {
        //---一時停止---//
        SourceVoice[label]->Stop(0);
    }
}

/////////////////////////////////////////////
//関数名：Stop
//
//機能：サウンドの停止
//
//引数：(SOUND_LABEL)サウンド名
//
//戻り値：なし
/////////////////////////////////////////////
void SOUND_MANAGER::Stop(SOUND_LABEL label)
{
    //---各種宣言---//
    XAUDIO2_VOICE_STATE sState;

    //状態取得
    SourceVoice[label]->GetState(&sState);

    //---再生判定---//
    if (sState.BuffersQueued)
    {
        //一時停止
        SourceVoice[label]->Stop(0);

        //オーディオバッファの削除
        SourceVoice[label]->FlushSourceBuffers();
    }
}