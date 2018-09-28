//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Wav_Controller.h"

/////////////////////////////////////////////
//関数名：Load
//
//機能：データのロード
//
//引数：(LPCWSTR)ファイルパス
//
//戻り値：(bool)処理の成否
/////////////////////////////////////////////
bool WAV_CONTROLLER::Load(LPCWSTR filepath)
{
    //---各種宣言---//
    LONG lSize;
    MMRESULT mResult;

    //---読み取り作業---//
	//ファイルオープン
    Mmio = mmioOpenW((LPWSTR)filepath, &MmioInfo, MMIO_READ);
    if (!Mmio)
    {
        MessageBoxW(nullptr, L"音楽ファイルを開けませんでした", filepath, MB_ICONSTOP | MB_OK);
        return false;
    }

    //RIFFチャンクの検索
    RiffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    mResult = mmioDescend(Mmio, &RiffChunk, nullptr, MMIO_FINDRIFF);
    if (mResult != MMSYSERR_NOERROR)
    {
        MessageBoxW(nullptr, L"RIFFチャンクが見つかりませんでした", filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

    //フォーマットチャンク検索
    FormatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
    mResult = mmioDescend(Mmio, &FormatChunk, &RiffChunk, MMIO_FINDCHUNK);
    if (mResult != MMSYSERR_NOERROR)
    {
        MessageBoxW(nullptr, L"フォーマットチャンクが見つかりませんでした", filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

	//WAVEFORMATEX構造体にデータを読み込む
    lSize = mmioRead(Mmio, (HPSTR)&WaveFormat, FormatChunk.cksize);

    switch (lSize)
    {
        //読み込み限界
        case 0:
            MessageBoxW(nullptr, L"これ以上読み込めません", filepath, MB_ICONSTOP | MB_OK);
            break;

        //読み取り失敗
        case -1:
            MessageBoxW(nullptr, L"読み取りに失敗しました", filepath, MB_ICONSTOP | MB_OK);
            break;

        //読み取り成功
        default:
        //データサイズの確認
        if (lSize != FormatChunk.cksize)
        {
            MessageBoxW(nullptr, L"データサイズが違います", filepath, MB_ICONSTOP | MB_OK);
            mmioClose(Mmio, 0);
            return false;
        }
    }

    //読み込み位置を先頭に戻す
    mmioAscend(Mmio, &FormatChunk, 0);

    //データチャンク検索
    DataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
    mResult = mmioDescend(Mmio, &DataChunk, &RiffChunk, MMIO_FINDCHUNK);
    if (mResult != MMSYSERR_NOERROR)
    {
        MessageBoxW(nullptr, L"データチャンクが見つかりませんでした", filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

	//音声データを読み込む
    WaveData.resize(DataChunk.cksize);
    if (mmioRead(Mmio, (HPSTR)&WaveData[0], DataChunk.cksize) != DataChunk.cksize)
    {
        MessageBoxW(nullptr, L"音楽データを読み込めませんでした", filepath, MB_ICONSTOP | MB_OK);
        mmioClose(Mmio, 0);
        return false;
    }

	//ファイルを閉じる
    mmioClose(Mmio, 0);

    return true;
}

/////////////////////////////////////////////
//関数名：GetFormat
//
//機能：フォーマットの取得
//
//引数：なし
//
//戻り値：(WAVEFORMATEX*)フォーマットのアドレス
/////////////////////////////////////////////
const WAVEFORMATEX* WAV_CONTROLLER::GetFormat(void)
{
	return &WaveFormat;
}

/////////////////////////////////////////////
//関数名：GetLoop
//
//機能：ループ情報の取得
//
//引数：なし
//
//戻り値：(UINT32*)フォーマットのアドレス
/////////////////////////////////////////////
const UINT32 WAV_CONTROLLER::GetLoop(void)
{
    return LoopCount;
}

/////////////////////////////////////////////
//関数名：GetWaveData
//
//機能：Wavデータの取得
//
//引数：なし
//
//戻り値：(BYTE*)Wavデータのアドレス
/////////////////////////////////////////////
const BYTE* WAV_CONTROLLER::GetWaveData(void)
{
	return &WaveData[0];
}

/////////////////////////////////////////////
//関数名：GetWaveSize
//
//機能：データサイズの取得
//
//引数：なし
//
//戻り値：(size_t*)データサイズのアドレス
/////////////////////////////////////////////
const std::size_t WAV_CONTROLLER::GetWaveSize(void)
{
	return WaveData.size();
}