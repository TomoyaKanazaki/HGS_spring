//==========================================
//
//  フェードの制御(fade.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"

//==========================================
//  フェード状態の列挙定義
//==========================================
typedef enum
{
	FADE_NONE = 0, //フェードしていない状態
	FADE_IN, //フェードイン状態
	FADE_OUT, //フェードアウト状態
	FADE_MAX
}FADE;

//==========================================
//  プロトタイプ宣言
//==========================================
void InitFade(MODE nextmode);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE nextmode);
FADE GetFade(void);

#endif
