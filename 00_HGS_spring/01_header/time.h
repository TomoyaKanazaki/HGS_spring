//==========================================
//
//  タイマーの制御(time.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"

//==========================================
//  プロトタイプ宣言
//==========================================
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
int GetTime(void);

#endif
