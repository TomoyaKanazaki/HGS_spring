//==========================================
//
//  テクスチャ設定用ファイル(texture.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "main.h"

//==========================================
//  テクスチャ一覧
//==========================================
typedef enum
{
	TEXTURE_EFFECT = 0, //エフェクトのテクスチャ
	TEXTURE_NUMBER,
	TEXTURE_TUTORIAL,
	TEXTURE_MAX
}TEXTURE_LABEL;

//==========================================
//  プロトタイプ宣言
//==========================================
void InitTexture(void);
void UninitTexture(void);
LPDIRECT3DTEXTURE9 GetTexture(int TextureLabel);

#endif
