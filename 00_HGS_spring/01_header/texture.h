//==========================================
//
//  �e�N�X�`���ݒ�p�t�@�C��(texture.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "main.h"

//==========================================
//  �e�N�X�`���ꗗ
//==========================================
typedef enum
{
	TEXTURE_EFFECT = 0, //�G�t�F�N�g�̃e�N�X�`��
	TEXTURE_NUMBER,
	TEXTURE_TUTORIAL,
	TEXTURE_MAX
}TEXTURE_LABEL;

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void InitTexture(void);
void UninitTexture(void);
LPDIRECT3DTEXTURE9 GetTexture(int TextureLabel);

#endif
