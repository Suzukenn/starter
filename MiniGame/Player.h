//
//	Player.h
//
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

//wb_t@CÇÝÝ//
#include "Main.h"
#include "Operation.h"

//\¢Ìè`//
typedef struct _ANIM_PAT {
	int Frame;		//p^[No
	int Count;		//t[	
} ANIM_PAT;

//NXé¾//
class PLAYER
{
	private:
		D3DXVECTOR2 Pos;						//vC[ÌÊu
		D3DXVECTOR2 Move;						//vC[ÌdÍp
        D3DXVECTOR2 Size;
		LPDIRECT3DTEXTURE9 Graphic;				//eNX`
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//¸_obt@
		VERTEX* Vertex;
		OPERATION* Operation;
		int			Anim;						// [VNo.0`7
		int			AnimPat;					// p^[No.0`2
		int			AnimCnt;					// t[0`15
        bool Hit;

	public:
		PLAYER();
		~PLAYER();

		//===vg^Cvé¾===
		HRESULT Initialize(void);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

		void SetPlayerAnimFrame(int);

        D3DXVECTOR2 GetPos(void) { return Pos; }
        bool GetHit(void) { return Hit; }
        D3DXVECTOR2 GetSize(void) { return Size; }

        void SetHit(bool hit) { Hit = hit; }
};

#endif