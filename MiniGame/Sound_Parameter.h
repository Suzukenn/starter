#ifndef _SOUND_PARAMETER_H_
#define _SOUND_PARAMETER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <string>
#include "Main.h"

//＝＝＝構造体宣言＝＝＝//
typedef struct
{
    std::wstring FileName;	//ファイル名
    UINT32 LoopCount;		//ループカウント
}SOUND_PARAMETER;

#endif