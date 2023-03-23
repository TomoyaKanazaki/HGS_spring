#ifndef _RANKINGNUMBER_H_
#define _RANKINGNUMBER_H_

#include "main.h"

typedef enum
{
	RANKING_TYPE_ESCAPE = 0,
	RANKING_TYPE_VILLAIN,
	RANKING_TYPE_MAX,
}RANKING_TYPE;

//�v���g�^�C�v�錾
void InitRanKingNumber(void);
void UninitRanKingNumber(void);
void UpdateRanKingNumber(void);
void DrawRanKingNumber(void);
void ResetRanKing(void);
void SaveData(void);
void LordData(void);
void SetRanking(int nRanKing);
void StartRanKing(void);
#endif