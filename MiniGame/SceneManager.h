#ifndef _SCENE_H_
#define _SCENE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BaseScene.h"
#include "Main.h"

//�������񋓌^��`������//
typedef enum
{
    SCENE_TITLE,
    SCENE_MANUAL,
    SCENE_SELECT,
    SCENE_GAME,
    SCENE_GAME_2,
    SCENE_GAME_3,
    SCENE_GAMECLEAR,
    SCENE_GAMEOVER,
    MAX_SCENE
}SCENE;

//�������N���X�錾������//
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
    
        static void SetScene(SCENE scene) { NextScene = scene; }
};

#endif