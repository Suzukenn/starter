#ifndef _SCENE_H_
#define _SCENE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Base_Scene.h"
#include "Main.h"

//＝＝＝列挙型定義＝＝＝//
typedef enum
{
    SCENE_TITLE,
    SCENE_GAME,
	SCENE_GAME_2,
    SCENE_GAMEOVER,
    MAX_SCENE
}SCENE;

//＝＝＝クラス宣言＝＝＝//
class SCENE_MANAGER
{
    private:
        static BASE_SCENE* Scene;
        static SCENE CurrentScene;
        static SCENE NextScene;

    public:
        static void Draw(void);
        static void Uninitialize(void);
        static HRESULT Initialize(void);
        static void Update(void);
    
        static void SetScene(SCENE);

};

#endif