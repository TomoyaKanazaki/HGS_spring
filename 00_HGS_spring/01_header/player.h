//==========================================
//
//  プレイヤーの制御(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//==========================================
//  プレイヤー状態の列挙定義
//==========================================
typedef enum
{
	PLAYERSTATE_NORMAL = 0, //通常状態
	PLAYERSTATE_MAX
}PLAYERSTATE;

//==========================================
//  プロトタイプ宣言
//==========================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
D3DXVECTOR3 GetPosPlayer(void);

#endif
