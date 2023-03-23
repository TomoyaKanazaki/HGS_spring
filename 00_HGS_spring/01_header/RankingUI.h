#ifndef _RANKINGUI_H_
#define _RANKINGUI_H_

#include "main.h"

//�v���C���[�̏��
typedef enum
{
	RANKING_NORMAL = 0,		//�ʏ�
	RANKING_PERFECT,		//�p�[�t�F�N�g
	RANKING_ALLPERFECT,		//�I�[���p�[�t�F�N�g
	RANKING_MAX
}RANKING;

//�v���g�^�C�v�錾
void InitRankingUI(void);
void UninitRankingUI(void);
void UpdateRankingUI(void);
void DrawRankingUI(void);
void SetRankingUI(RANKING SetClear, bool Clear);
#endif