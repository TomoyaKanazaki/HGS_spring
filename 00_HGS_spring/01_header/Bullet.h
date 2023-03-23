#ifndef _BULLET_H_
#define _BULLET_H_

#define MAX_BULLET (256)		//影の最大数

//モデルの構造体
typedef enum
{
	BULLET_NORMAL = 0,
	BULLET_MIRROR,
	BULLET_MAX,

}BULLET_TYPE;

//ビルボード構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 posOld;							//位置
	D3DXVECTOR3 move;							//位置
	D3DXMATRIX mtxWorld;						//ワールドマトリックス
	BULLET_TYPE nType;						//弾の種類
	float rot;									//向き
	int nLife;									//寿命
	int nEffectCounter;							//エフェクトをセットする間隔
	int nIndex;
	bool bUse;									//使用しているかどうか
}Bullet;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, float rot, int nLife, BULLET_TYPE Type);
D3DXVECTOR3 GETAAA(void);
Bullet * GetBullet(void);
#endif