#include "main.h"
#include "Enemy.h"
#include "Bullet.h"
#include "particle.h"
#include "player.h"

#define ENEMY00_LIFE (7)		//敵の体力
#define ENWMY_MOVE (1.0f)		//敵の移動量
#define BULLET_POS_XZ (20.0f)	//弾の発射位置(横の軸)
#define BULLET_POS_Y (25.0f)	//弾の発射位置(縦の軸)
#define BULLET_LIFE (120)		//弾の寿命
#define BULLETCOUNTER (120)		//弾を撃つ感覚

//プロトタイプ宣言
void UpdateSlime(int nCnt);
void UpdateCannon(int nCnt);

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureEnemy[ENEMY_MAX][64] = {};	//テクスチャのポインタ
LPD3DXMESH g_pMeshEnemy[ENEMY_MAX] = {};					//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatEnemy[ENEMY_MAX] = {};				//マテリアルへのポインタ
DWORD g_dwNumMatEnemy[ENEMY_MAX] = {};						//マテリアルの数

Enemy g_Enemy[MAX_ENEMY];					//敵の情報

//====================================================================
//敵の初期化処理
//====================================================================
void InitEnemy(void)
{
	int nCntEnemy;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_Enemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Enemy[nCntEnemy].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Enemy[nCntEnemy].BulletCounter = 0;
		g_Enemy[nCntEnemy].bUse = false;
		g_Enemy[nCntEnemy].nType = ENEMY_NTYPE00;
		g_Enemy[nCntEnemy].State = ENEMY_STATE_WAIT;
		g_Enemy[nCntEnemy].pMatD.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}

	//Xファイルの読み込み
	D3DXLoadMeshFromX("02_data\\03_MODEL\\Enemy00.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[ENEMY_NTYPE00],
		NULL,
		&g_dwNumMatEnemy[ENEMY_NTYPE00],
		&g_pMeshEnemy[ENEMY_NTYPE00]);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("02_data\\03_MODEL\\taihou00.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[ENEMY_NTYPE01],
		NULL,
		&g_dwNumMatEnemy[ENEMY_NTYPE01],
		&g_pMeshEnemy[ENEMY_NTYPE01]);

	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntNumObject = 0; nCntNumObject < ENEMY_MAX; nCntNumObject++)
	{
		//マテリアル情報に対するポインタを所得
		pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureEnemy[nCntNumObject][nCntMat]);
			}
		}
	}

	SetEnemy(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].move, g_Enemy[nCntEnemy].rot, ENEMY_NTYPE00);
	SetEnemy(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].move, g_Enemy[nCntEnemy].rot, ENEMY_NTYPE01);
}

//====================================================================
//敵の終了処理
//====================================================================
void UninitEnemy(void)
{
	for (int nCntNumObject = 0; nCntNumObject < ENEMY_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//テクスチャの破棄
			if (g_pTextureEnemy[nCntNumObject][nCntTex] != NULL)
			{
				g_pTextureEnemy[nCntNumObject][nCntTex]->Release();
				g_pTextureEnemy[nCntNumObject][nCntTex] = NULL;
			}
		}

		//メッシュの破棄
		if (g_pMeshEnemy[nCntNumObject] != NULL)
		{
			g_pMeshEnemy[nCntNumObject]->Release();
			g_pMeshEnemy[nCntNumObject] = NULL;
		}

		//マテリアルの破棄
		if (g_pBuffMatEnemy[nCntNumObject] != NULL)
		{
			g_pBuffMatEnemy[nCntNumObject]->Release();
			g_pBuffMatEnemy[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//敵の更新処理
//====================================================================
void UpdateEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			g_Enemy[nCntEnemy].posOld = g_Enemy[nCntEnemy].pos;

			switch (g_Enemy[nCntEnemy].nType)
			{
			case ENEMY_NTYPE00:		//追跡する敵

				UpdateSlime(nCntEnemy);

				break;
			case ENEMY_NTYPE01:		//大砲

				UpdateCannon(nCntEnemy);

				break;
			}
		}
	}
}

//====================================================================
//追跡する敵の更新処理
//====================================================================
void UpdateSlime(int nCnt)
{
	switch (g_Enemy[nCnt].State)
	{
	case ENEMY_STATE_WAIT:
		break;
	case ENEMY_STATE_BATTLE:
		break;
	}

	//移動処理
	g_Enemy[nCnt].move = D3DXVECTOR3(-cosf(g_Enemy[nCnt].rot.y) * ENWMY_MOVE, 0.0f, sinf(g_Enemy[nCnt].rot.y) * ENWMY_MOVE);
	g_Enemy[nCnt].State = ENEMY_STATE_BATTLE;

	//向きの補正
	RotEnemy(g_Enemy[nCnt].pos, nCnt);

	//位置更新(入力による動き)
	g_Enemy[nCnt].pos += g_Enemy[nCnt].move;

	//Player *pPlayer = GetPlayer();

	////ノックバック処理
	//if (CollisionCircle(pPlayer->pos, g_Enemy[nCnt].pos, 120.0f, 0.0f, pPlayer->vtxMin.y, pPlayer->vtxMax.y) == true)
	//{
	//	KnoccBackPlayer(g_Enemy[nCnt].pos, KNOCCBACKPOWER);
	//}

	////プレイヤーとの当たり判定
	//CollisionPlayer(g_Enemy[nCnt].pos, g_Enemy[nCnt].posOld, 23.0f, g_Enemy[nCnt].vtxMax.y, g_Enemy[nCnt].vtxMin.y);
}

//====================================================================
//大砲の更新処理
//====================================================================
void UpdateCannon(int nCnt)
{
	//向きの補正
	RotEnemy(g_Enemy[nCnt].pos, nCnt);

	//弾発射のクールタイムを減少させる
	g_Enemy[nCnt].BulletCounter++;

	if (g_Enemy[nCnt].BulletCounter >= BULLETCOUNTER)
	{
		SetBullet(D3DXVECTOR3(
			g_Enemy[nCnt].pos.x - cosf(g_Enemy[nCnt].rot.y) * BULLET_POS_XZ,
			g_Enemy[nCnt].pos.y + BULLET_POS_Y,
			g_Enemy[nCnt].pos.z + sinf(g_Enemy[nCnt].rot.y) * BULLET_POS_XZ),
			g_Enemy[nCnt].rot.y + D3DX_PI * -0.5f,
			BULLET_LIFE,
			BULLET_NORMAL);

		SetParticle(
			D3DXVECTOR3(
			g_Enemy[nCnt].pos.x - cosf(g_Enemy[nCnt].rot.y) * 40.0f,
			g_Enemy[nCnt].pos.y + 25.0f,
			g_Enemy[nCnt].pos.z + sinf(g_Enemy[nCnt].rot.y) * 40.0f),
			g_Enemy[nCnt].rot,
			D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f),
			5,
			5.0f,
			6);

		g_Enemy[nCnt].BulletCounter = 0;
	}

	//位置更新(入力による動き)
	g_Enemy[nCnt].pos += g_Enemy[nCnt].move;
}

//====================================================================
//敵がプレイヤーの方向を向く
//====================================================================
void RotEnemy(D3DXVECTOR3 Pos, int nCnt)
{
	D3DXVECTOR3 * pPosPlayer = GetPosPlayer();		//プレイヤーの情報へのポインタ

	float fAngle = atan2f(pPosPlayer.z - Pos.z, Pos.x - pPosPlayer.x);

	g_Enemy[nCnt].rot.y = fAngle;
}

//====================================================================
//プレイヤーのをノックバックする処理
//====================================================================
void KnoccBackPlayer(D3DXVECTOR3 Pos, float Power)
{
	//Player * pPlayer = GetPlayer();		//プレイヤーの情報へのポインタ

	//float fAngle = atan2f(pPlayer->pos.z - Pos.z, Pos.x - pPlayer->pos.x);

	//pPlayer->move.x -= cosf(fAngle) * Power;
	//pPlayer->move.z += sinf(fAngle) * Power;
}

//====================================================================
//円柱の当たり判定
//====================================================================
bool CollisionCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut, float nRadiusIn, float MinY, float MaxY)
{
	bool nHit = false;

	if (sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
		+ (pos1.z - pos2.z) * (pos1.z - pos2.z)) <= nRadiusOut
		&& sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
			+ (pos1.z - pos2.z) * (pos1.z - pos2.z)) >= nRadiusIn
		&& pos1.y + MinY < pos2.y
		&& pos1.y + MaxY > pos2.y)
	{//円の判定が当たった
		nHit = true;
	}

	return nHit;
}

//====================================================================
//敵の描画処理
//====================================================================
void DrawEnemy(void)
{
	int nCntEnemy;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[nCntEnemy].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].rot.y, g_Enemy[nCntEnemy].rot.x, g_Enemy[nCntEnemy].rot.z);

			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);

			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].mtxWorld);

			//現在のマテリアルを所得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを所得する
			pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[g_Enemy[nCntEnemy].nType]->GetBufferPointer();

			if (g_Enemy[nCntEnemy].bUse == true)
			{
				for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy[g_Enemy[nCntEnemy].nType]; nCntMat++)
				{
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの設定
					pDevice->SetTexture(0, g_pTextureEnemy[g_Enemy[nCntEnemy].nType][nCntMat]);

					//敵(パーツ)の描画
					g_pMeshEnemy[g_Enemy[nCntEnemy].nType]->DrawSubset(nCntMat);

				}
			}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//敵の設定処理
//====================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, ENEMY_NTYPE nType)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == false)
		{
			g_Enemy[nCntEnemy].pos = pos;
			g_Enemy[nCntEnemy].posOld = pos;
			g_Enemy[nCntEnemy].move = move;
			g_Enemy[nCntEnemy].rot = rot;
			g_Enemy[nCntEnemy].nType = nType;
			g_Enemy[nCntEnemy].State = ENEMY_STATE_WAIT;
			g_Enemy[nCntEnemy].bUse = true;

			int nNumVtx;		//頂点数
			DWORD dwSizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;		//頂点バッファへのポインタ
			
			//頂点数を所得
			nNumVtx = g_pMeshEnemy[nType]->GetNumVertices();

			//頂点フォーマットのサイズを所得
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshEnemy[nType]->GetFVF());

			//頂点バッファをロック
			g_pMeshEnemy[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				if (g_Enemy[nCntEnemy].vtxMin.x > vtx.x)
				{
					g_Enemy[nCntEnemy].vtxMin.x = vtx.x;
				}
				if (g_Enemy[nCntEnemy].vtxMin.y > vtx.y)
				{
					g_Enemy[nCntEnemy].vtxMin.y = vtx.y;
				}
				if (g_Enemy[nCntEnemy].vtxMin.z > vtx.z)
				{
					g_Enemy[nCntEnemy].vtxMin.z = vtx.z;
				}

				if (g_Enemy[nCntEnemy].vtxMax.x < vtx.x)
				{
					g_Enemy[nCntEnemy].vtxMax.x = vtx.x;
				}
				if (g_Enemy[nCntEnemy].vtxMax.y < vtx.y)
				{
					g_Enemy[nCntEnemy].vtxMax.y = vtx.y;
				}
				if (g_Enemy[nCntEnemy].vtxMax.z < vtx.z)
				{
					g_Enemy[nCntEnemy].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
			}

			//頂点バッファをアンロック
			g_pMeshEnemy[nType]->UnlockVertexBuffer();

			break;
		}
	}
}

//====================================================================
//プレイヤーとの当たり判定処理
//====================================================================
void CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			if (
				(pPos->z + max.z >= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].vtxMin.z && pPosOld->z + max.z< g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].vtxMin.z ||
					pPos->z + min.z <= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].vtxMax.z && pPosOld->z + min.z > g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].vtxMax.z) &&
				pPos->x + max.x >= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].vtxMin.x &&
				pPos->x + min.x <= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].vtxMax.x &&
				pPos->y + max.y >= g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].vtxMin.y&&
				pPos->y + min.y <= g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].vtxMax.y
				)
			{//壁とプレイヤーが当たった(Z軸)
				pPos->z = pPosOld->z;
				pMove->z = 0.0f;
			}

			if (
				(pPos->x + max.x >= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].vtxMin.x && pPosOld->x + max.x< g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].vtxMin.x ||
					pPos->x + min.x <= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].vtxMax.x && pPosOld->x + min.x > g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].vtxMax.x) &&
				pPos->z + max.z >= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].vtxMin.z &&
				pPos->z + min.z <= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].vtxMax.z &&
				pPos->y + max.y >= g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].vtxMin.y &&
				pPos->y + min.y <= g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].vtxMax.y
				)
			{//壁とプレイヤーが当たった(X軸)
				pPos->x = pPosOld->x;
				pMove->x = 0.0f;
			}
		}
	}
}

//====================================================================
//敵の所得
//====================================================================
Enemy * GetEnemy(void)
{
	return &g_Enemy[0];
}