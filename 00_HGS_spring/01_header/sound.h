#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,			// タイトル
	SOUND_LABEL_BGM_RANKING,			// ランキング
	SOUND_LABEL_BGM_GAME_01,			// ゲーム01
	SOUND_LABEL_BGM_GAME_02,			// ゲーム02
	SOUND_LABEL_BGM_GAME_03,			// ゲーム03
	SOUND_LABEL_SE_KEY_MOVE,			// 移動
	SOUND_LABEL_SE_KEY_PUSH,			// 決定
	SOUND_LABEL_SE_PLAYER_JUMP,			// ジャンプ
	SOUND_LABEL_SE_PLAYER_DAMAGE,		// ダメージ
	SOUND_LABEL_SE_TIME_NORMAL,			// 時間
	SOUND_LABEL_SE_TIME_HURRY,			// 時間
	SOUND_LABEL_SE_DAMAGEWAVE,			// ダメージウェーブ
	SOUND_LABEL_SE_SLIME_JUMP,			// ジャンプ
	SOUND_LABEL_SE_CANNON_BULLET,		// 大砲の弾
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
