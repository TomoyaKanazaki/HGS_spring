#ifndef _GAMEUI_H_
#define _GAMEUI_H_

#include "main.h"

//�v���C���[�̏��
typedef enum
{
	GAME_NORMAL = 0,		//�ʏ�
	GAME_PERFECT,		//�p�[�t�F�N�g
	GAME_ALLPERFECT,		//�I�[���p�[�t�F�N�g
	GAME_MAX
}GAME;

//�v���g�^�C�v�錾
void InitGameUI(void);
void UninitGameUI(void);
void UpdateGameUI(void);
void DrawGameUI(void);
void SetGameUI(GAME SetClear, bool Clear);
#endif