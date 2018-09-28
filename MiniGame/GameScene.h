#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Base_Scene.h"
#include "Main.h"

//�������N���X�錾������//
class GAME final: public BASE_SCENE
{
    private:
        unsigned int Score;
        LPDIRECT3DTEXTURE9 Graphic;           //�e�N�X�`��
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //���_�o�b�t�@

    public:
        void Draw(void) final;
        void Uninitialize(void) final;
        HRESULT Initialize(void) final;
        void Update(void) final;
};

#endif