#ifndef _ENEMY_H_
#define _ENEMY_H_

#define MAX_ENEMY (2048)		//オブジェクトの最大数

//モデルの構造体
typedef enum
{
	ENEMY_STATE_WAIT = 0,
	ENEMY_STATE_BATTLE,
	ENEMY_STATE_MAX,

}ENEMY_STATE;

//モデルの構造体
typedef enum
{
	ENEMY_NTYPE00 = 0,
	ENEMY_NTYPE01,
	ENEMY_MAX,

}ENEMY_NTYPE;

//モデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;							//現在の位置
	D3DXVECTOR3 posOld;							//過去の位置
	D3DXVECTOR3 move;							//移動量
	D3DXVECTOR3 rot;							//向き
	D3DXMATRIX mtxWorld;						//ワールドマトリックス
	D3DXVECTOR3 vtxMin;							//モデルの最小
	D3DXVECTOR3 vtxMax;							//モデルの最大
	D3DXVECTOR3 size; //大きさ
	int nType;							//モデルの種類
	ENEMY_STATE State;							//敵の状態
	int BulletCounter;							//大砲のカウンター
	float fRadius; //半径
	bool bUse;									//モデルが使用されているかどうか
	D3DXMATERIAL pMatD;							//マテリアルデータへのポインタ
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void RotEnemy(D3DXVECTOR3 Pos, int nCnt);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max);
void KnoccBackPlayer(D3DXVECTOR3 Pos, float Power);
bool CollisionCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut, float nRadiusIn, float MinY, float MaxY);
Enemy * GetEnemy(void);
bool GetHit(void);

#endif