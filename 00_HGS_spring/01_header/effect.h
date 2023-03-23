#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//エフェクト構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXMATRIX mtxWorld;						//ワールドマトリックス
	D3DXCOLOR col;		//色
	float fRadius;		//半径(大きさ)
	int nLifeMax;		//寿命の最大値
	int nLife;			//寿命
	bool bUse;			//使用しているかどうか
}Effect;

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife);
int GetEffectNum(void);
#endif
