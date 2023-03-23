#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//パーティクル構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//発生位置
	D3DXVECTOR3 rot;	//角度
	D3DXCOLOR col;		//色
	int nLife;			//寿命(発生時間)
	float nSize;		//寿命(発生時間)
	int nType;			//種類	
	bool bUse;			//使用しているかどうか
}Particle;

//プロトタイプ宣言
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, float nSize, int nType);
#endif
