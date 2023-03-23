#include "main.h"
#include "Bullet.h"
#include "effect.h"
#include "player.h"

#define BULLET_SIZE (5.0f)	//弾の大きさ
#define BULLET_SPEED (10.0f)	//弾の速さ
#define EFFECT_COUNTER (1)	//エフェクトをセットする間隔

//プロトタイプ宣言

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet;				//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet;		//頂点バッファのポインタ
Bullet g_aBullet[MAX_BULLET];

//====================================================================
//ビルボードの初期化処理
//====================================================================
void InitBullet(void)
{
	int nCntBill;
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BOSS00.png",
		&g_pTextureBullet);

	for (nCntBill = 0; nCntBill < MAX_BULLET; nCntBill++)
	{
		g_aBullet[nCntBill].pos = D3DXVECTOR3(90.0f, 10.0f, 50.0f);
		g_aBullet[nCntBill].posOld = g_aBullet[nCntBill].pos;
		g_aBullet[nCntBill].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBill].bUse = false;
		g_aBullet[nCntBill].nIndex = -1;
		g_aBullet[nCntBill].nType = BULLET_NORMAL;
		g_aBullet[nCntBill].nEffectCounter = EFFECT_COUNTER;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBill = 0; nCntBill < MAX_BULLET; nCntBill++)
	{
		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, +BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+BULLET_SIZE, +BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+BULLET_SIZE, -BULLET_SIZE, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//====================================================================
//ビルボードの終了処理
//====================================================================
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//====================================================================
//ビルボードの更新処理
//====================================================================
void UpdateBullet(void)
{
	int nCntBill;

	for (nCntBill = 0; nCntBill < MAX_BULLET; nCntBill++)
	{
		if (g_aBullet[nCntBill].bUse == true)
		{
			g_aBullet[nCntBill].posOld = g_aBullet[nCntBill].pos;

			//弾の位置更新
			g_aBullet[nCntBill].pos += g_aBullet[nCntBill].move;

			//寿命を減らす
			g_aBullet[nCntBill].nLife--;

			////プレイヤーとの当たり判定
			//CollisionPlayer(&g_aBullet[nCntBill]);
			//Player *pPlayer = GetPlayer();

			g_aBullet[nCntBill].nEffectCounter--;
			if (g_aBullet[nCntBill].nEffectCounter <= 0)
			{
				//弾発射時にエフェクトを呼び出す
				SetEffect(g_aBullet[nCntBill].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8.0f, 10);
				g_aBullet[nCntBill].nEffectCounter = EFFECT_COUNTER;
			}

			//寿命がなくなった時弾を消す
			if (g_aBullet[nCntBill].nLife <= 0)
			{
				g_aBullet[nCntBill].bUse = false;
			}

			//当たり判定
			GetCollisionPlayer(g_aBullet[nCntBill].pos, BULLET_SIZE);
		}
	}

	VERTEX_3D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBill = 0; nCntBill < MAX_BULLET; nCntBill++)
	{
		if (g_aBullet[nCntBill].bUse == true)
		{
			//頂点座標の設定 
			pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, +BULLET_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+BULLET_SIZE, +BULLET_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+BULLET_SIZE, -BULLET_SIZE, 0.0f);
		}

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//====================================================================
//ビルボードの描画処理
//====================================================================
void DrawBullet(void)
{
	int nCntBill;

	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxView;	//ビューマトリックス所得用

	////Zテストを無効にする
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntBill = 0; nCntBill < MAX_BULLET; nCntBill++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBullet[nCntBill].mtxWorld);

		//ビューマトリックスを所得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラに対して正面を向ける
		D3DXMatrixInverse(&g_aBullet[nCntBill].mtxWorld, NULL, &mtxView);	//逆行列を求める
		g_aBullet[nCntBill].mtxWorld._41 = 0.0f;
		g_aBullet[nCntBill].mtxWorld._42 = 0.0f;
		g_aBullet[nCntBill].mtxWorld._43 = 0.0f;

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBill].pos.x, g_aBullet[nCntBill].pos.y, g_aBullet[nCntBill].pos.z);

		D3DXMatrixMultiply(&g_aBullet[nCntBill].mtxWorld, &g_aBullet[nCntBill].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBill].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBullet);

		if (g_aBullet[nCntBill].bUse == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntBill,										//プリミティブ(ポリゴン)数
				2);
		}
	}

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	////Zテストを有効にする
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//====================================================================
//ビルボードの設定処理
//====================================================================
void SetBullet(D3DXVECTOR3 pos, float rot, int nLife, BULLET_TYPE Type)
{
	int nCntBill;

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBill = 0; nCntBill < MAX_BULLET; nCntBill++)
	{
		if (g_aBullet[nCntBill].bUse == false)
		{
			g_aBullet[nCntBill].pos = pos;
			g_aBullet[nCntBill].posOld = pos;
			g_aBullet[nCntBill].move = D3DXVECTOR3(sinf(rot) * BULLET_SPEED, 0.0f, cosf(rot) * BULLET_SPEED);
			g_aBullet[nCntBill].rot = rot;
			g_aBullet[nCntBill].nType = Type;
			g_aBullet[nCntBill].nLife = nLife;
			g_aBullet[nCntBill].bUse = true;

			////サウンドの再生
			//PlaySound(SOUND_LABEL_SE_CANNON_BULLET);

			break;
		}
		pVtx += 4;	//頂点データのポインタを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

////====================================================================
////弾とプレイヤーの当たり判定
////====================================================================
//void CollisionPlayer(Bullet*pBullet)
//{
//	Player * pPlayer = GetPlayer();		//オブジェクトの情報へのポインタ
//
//	if (
//		pBullet->pos.z >= pPlayer->pos.z + pPlayer->vtxMin.z &&
//		pBullet->pos.z <= pPlayer->pos.z + pPlayer->vtxMax.z &&
//		pBullet->pos.x >= pPlayer->pos.x + pPlayer->vtxMin.x &&
//		pBullet->pos.x <= pPlayer->pos.x + pPlayer->vtxMax.x &&
//		pBullet->pos.y >= pPlayer->pos.y + pPlayer->vtxMin.y &&
//		pBullet->pos.y <= pPlayer->pos.y + +pPlayer->vtxMax.y
//		)
//	{//敵と攻撃が当たった
//		pBullet->bUse = false;
//		falseShadow(pBullet->nIndex);
//		SetExplosion(pBullet->pos, 0);
//		SetParticle(pBullet->pos, D3DXVECTOR3(pBullet->rot, pBullet->rot, pBullet->rot), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 5.0f, 4);
//		PlayerHit();
//	}
//}

//====================================================================
//弾の所得
//====================================================================
D3DXVECTOR3 GETAAA(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================================================
//弾の所得
//====================================================================
Bullet * GetBullet(void)
{
	return &g_aBullet[0];
}