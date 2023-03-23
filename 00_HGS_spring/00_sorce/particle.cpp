#include "main.h"
#include "particle.h"
#include "effect.h"

//マクロ定義
#define MAX_PARTICLE (128)		//パーティクルの最大数
#define STANDERD_SPEED (1.0f)	//パーティクルの基準のスピード
#define RAND_PAI1 (17)			//角度のランダム
#define PUT_PARTICLE1 (1)		//１フレームに出すパーティクルの数
#define RAND_PAI2 (365)			//角度のランダム
#define PUT_PARTICLE2 (5)		//１フレームに出すパーティクルの数
#define RAND_PAI3 (731)			//角度のランダム
#define PUT_PARTICLE3 (3)		//１フレームに出すパーティクルの数

#define RAND_PAI5 (629)			//角度のランダム
#define PUT_PARTICLE5 (7)		//１フレームに出すパーティクルの数
#define RAND_PAI6 (629)			//角度のランダム
#define PUT_PARTICLE6 (30)		//１フレームに出すパーティクルの数

//グローバル変数
Particle g_aParticle[MAX_PARTICLE];							//パーティクルの情報
D3DXVECTOR3 move;
//====================================================================
//パーティクルの初期化処理
//====================================================================
void InitParticle(void)
{
	int nCntParticle;

	//パーティクルの情報の初期化
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].bUse = false;	//使用していない状態にする
	}
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================================================
//パーティクルの終了処理
//====================================================================
void UninitParticle(void)
{

}

//====================================================================
//パーティクルの更新処理
//====================================================================
void UpdateParticle(void)
{
	int nCntParticle;
	int nCntAppear;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			if (g_aParticle[nCntParticle].nLife > 0)
			{
				if (g_aParticle[nCntParticle].nType == 1)
				{
					//パーティクルの生成
					for (nCntAppear = 0; nCntAppear < PUT_PARTICLE1; nCntAppear++)
					{
						//移動量の設定
						move.x = sinf((float)(rand() % RAND_PAI1 - (RAND_PAI1 - 1) / 2) / 100.0f + D3DX_PI * -0.5f)*(float)((rand() % 100) / 10.0f) + STANDERD_SPEED;
						move.y = cosf((float)(rand() % RAND_PAI1 - (RAND_PAI1 - 1) / 2) / 100.0f + D3DX_PI * -0.5f)*(float)((rand() % 100) / 10.0f) + STANDERD_SPEED;
						move.z = 0.0f;

						//エフェクトを呼び出す
						SetEffect
						(
							g_aParticle[nCntParticle].pos,
							move,
							g_aParticle[nCntParticle].col,
							g_aParticle[nCntParticle].nSize / 2,
							g_aParticle[nCntParticle].nLife
						);
					}
				}
				if (g_aParticle[nCntParticle].nType == 2)
				{
					//パーティクルの生成
					for (nCntAppear = 0; nCntAppear < PUT_PARTICLE2; nCntAppear++)
					{
						//移動量の設定
						move.x = sinf((float)(rand() % RAND_PAI2 - (RAND_PAI2 - 1) / 2) / 100.0f + D3DX_PI * -0.5f)*(float)((rand() % 100) / 20.0f) + STANDERD_SPEED;
						move.y = cosf((float)(rand() % RAND_PAI2 - (RAND_PAI2 - 1) / 2) / 100.0f + D3DX_PI * -0.5f)*(float)((rand() % 100) / 20.0f) + STANDERD_SPEED;
						move.z = 0.0f;

						//エフェクトを呼び出す
						SetEffect
						(
							g_aParticle[nCntParticle].pos,
							move,
							g_aParticle[nCntParticle].col,
							g_aParticle[nCntParticle].nSize / 2,
							g_aParticle[nCntParticle].nLife
						);
					}
				}

				if (g_aParticle[nCntParticle].nType == 3)
				{
					//パーティクルの生成
					for (nCntAppear = 0; nCntAppear < PUT_PARTICLE3; nCntAppear++)
					{
						//移動量の設定
						move.x = sinf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 500.0f;
						move.y = cosf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 500.0f;
						move.z = 0.0f;

						//エフェクトを呼び出す
						SetEffect
						(
							g_aParticle[nCntParticle].pos,
							move,
							g_aParticle[nCntParticle].col,
							g_aParticle[nCntParticle].nSize,
							g_aParticle[nCntParticle].nLife
						);
					}
				}

				if (g_aParticle[nCntParticle].nType == 4)
				{
					//パーティクルの生成
					for (nCntAppear = 0; nCntAppear < PUT_PARTICLE3; nCntAppear++)
					{
						//移動量の設定
						move.x = sinf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 0.5f;
						move.y = cosf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 0.5f;
						move.z = sinf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 0.5f;

						//エフェクトを呼び出す
						SetEffect
						(
							g_aParticle[nCntParticle].pos,
							move,
							g_aParticle[nCntParticle].col,
							g_aParticle[nCntParticle].nSize,
							60
						);
					}
				}

				if (g_aParticle[nCntParticle].nType == 5)
				{
					//パーティクルの生成
					for (nCntAppear = 0; nCntAppear < PUT_PARTICLE5; nCntAppear++)
					{
						//move.x =sinf(g_camera.rot.y) * CAMERA_DISTANCE;
						//3.14 -> 6.28

						//移動量の設定
						move.x = sinf((float)(rand() % RAND_PAI5 - (RAND_PAI5 - 1) / 2) / 100.0f + D3DX_PI) * 50.0f;
						move.y = 0.0f;
						move.z = cosf((float)(rand() % RAND_PAI5 - (RAND_PAI5 - 1) / 2) / 100.0f + D3DX_PI) * 50.0f;

						D3DXVec3Normalize(&move, &move);	//ベクトルを正規化する

						//エフェクトを呼び出す
						SetEffect
						(
							D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + (move.x * 40.0f), g_aParticle[nCntParticle].pos.y + move.y, g_aParticle[nCntParticle].pos.z + (move.z * 40.0f)),
							D3DXVECTOR3(move.z * 3.0f,1.0f, -move.x * 3.0f),
							g_aParticle[nCntParticle].col,
							g_aParticle[nCntParticle].nSize,
							30
						);
					}
				}

				if (g_aParticle[nCntParticle].nType == 6)
				{
					//パーティクルの生成
					for (nCntAppear = 0; nCntAppear < PUT_PARTICLE6; nCntAppear++)
					{
						//move.x =sinf(g_camera.rot.y) * CAMERA_DISTANCE;
						//3.14 -> 6.28

						//移動量の設定
						move.x = sinf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 0.5f;
						move.y = cosf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 0.5f;
						move.z = sinf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 0.5f;

						D3DXVec3Normalize(&move, &move);	//ベクトルを正規化する

						move.x *= 5.0f;
						move.y *= 5.0f;
						move.z *= 5.0f;

						//エフェクトを呼び出す
						SetEffect
						(
							g_aParticle[nCntParticle].pos,
							D3DXVECTOR3(move.x, move.y, move.z),
							g_aParticle[nCntParticle].col,
							g_aParticle[nCntParticle].nSize,
							10
						);
					}
				}

				g_aParticle[nCntParticle].nLife--;
				if (g_aParticle[nCntParticle].nLife <= 0)
				{
					g_aParticle[nCntParticle].bUse = false;
				}
			}
		}
	}
}

//====================================================================
//パーティクルの描画処理
//====================================================================
void DrawParticle(void)
{

}

//====================================================================
//パーティクルの設定処理
//====================================================================
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, float nSize, int nType)
{
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle <MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//パーティクルが使用されていない
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].rot = rot;
			g_aParticle[nCntParticle].col = col;
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].nSize = nSize;
			g_aParticle[nCntParticle].nType = nType;

			g_aParticle[nCntParticle].bUse = true;	//パーティクルを使用している状態にする
			break;
		}
	}
}