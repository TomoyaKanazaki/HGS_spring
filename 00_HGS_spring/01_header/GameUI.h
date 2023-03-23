#ifndef _GAMEUI_H_
#define _GAMEUI_H_

#include "main.h"

//プレイヤーの状態
typedef enum
{
	GAME_NORMAL = 0,		//通常
	GAME_PERFECT,		//パーフェクト
	GAME_ALLPERFECT,		//オールパーフェクト
	GAME_MAX
}GAME;

//プロトタイプ宣言
void InitGameUI(void);
void UninitGameUI(void);
void UpdateGameUI(void);
void DrawGameUI(void);
void SetGameUI(GAME SetClear, bool Clear);
#endif