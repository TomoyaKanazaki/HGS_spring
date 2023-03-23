#include "main.h"
#include "PlusScore.h"
#include "texture.h"

//マクロ定義
#define NUM_PLACE (3)				//プラススコアの桁数

#define X_POS_GAME (100.0f)			//ゲーム画面の時のプラススコアのX座標
#define Y_POS_GAME (50.0f)			//ゲーム画面の時のプラススコアのY座標
#define X_SIZE_GAME (20.0f)			//ゲーム画面の時のプラススコアの横幅
#define Y_SIZE_GAME (20.0f)			//ゲーム画面の時のプラススコアの縦幅
#define WIDE_SIZE_GAME (40.0f)		//ゲーム画面の時のプラススコア同士の幅

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlusScore = NULL;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlusScore = NULL;		//頂点バッファのポインタ
D3DXVECTOR3 g_posPlusScore[NUM_PLACE];					//プラススコアの位置
int g_nPlusScore;										//プラススコアの値

//====================================================================
//プラススコアの初期化処理
//====================================================================
void InitPlusScore(void)
{
	int nCntPlusScore;
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	for (nCntPlusScore = 0; nCntPlusScore < NUM_PLACE; nCntPlusScore++)
	{
		g_posPlusScore[nCntPlusScore] = D3DXVECTOR3(900.0f + nCntPlusScore * WIDE_SIZE_GAME, 50.0f, 0.0f);
	}
	g_nPlusScore = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlusScore,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffPlusScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlusScore = 0; nCntPlusScore < NUM_PLACE; nCntPlusScore++)
	{
		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x - X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y - Y_SIZE_GAME, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x + X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y - Y_SIZE_GAME, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x - X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y + Y_SIZE_GAME, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x + X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y + Y_SIZE_GAME, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlusScore->Unlock();
}

//====================================================================
//プラススコアの終了処理
//====================================================================
void UninitPlusScore(void)
{
	//テクスチャの破棄
	if (g_pTexturePlusScore != NULL)
	{
		g_pTexturePlusScore->Release();
		g_pTexturePlusScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlusScore != NULL)
	{
		g_pVtxBuffPlusScore->Release();
		g_pVtxBuffPlusScore = NULL;
	}
}

//====================================================================
//プラススコアの更新処理
//====================================================================
void UpdatePlusScore(void)
{
	MODE g_Mode = GetMode();	//ゲームモードを所得
	int nCntPlusScore;

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffPlusScore->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_Mode)
	{
	case MODE_GAME:
		for (nCntPlusScore = 0; nCntPlusScore < NUM_PLACE; nCntPlusScore++)
		{
			g_posPlusScore[nCntPlusScore] = D3DXVECTOR3(X_POS_GAME + nCntPlusScore * WIDE_SIZE_GAME, Y_POS_GAME, 0.0f);

			//頂点座標の設定 
			pVtx[0].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x - X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y - Y_SIZE_GAME, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x + X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y - Y_SIZE_GAME, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x - X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y + Y_SIZE_GAME, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x + X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y + Y_SIZE_GAME, 0.0f);

			pVtx += 4;	//頂点データのポインタを４つ分進める

		}
		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlusScore->Unlock();
}

//====================================================================
//プラススコアの描画処理
//====================================================================
void DrawPlusScore(void)
{
	int nCntPlusScore;
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlusScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, GetTexture(TEXTURE_NUMBER));

	for (nCntPlusScore = 0; nCntPlusScore < NUM_PLACE; nCntPlusScore++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			4 * nCntPlusScore,							//プリミティブ(ポリゴン)数
			2);
	}
}

//====================================================================
//プラススコアの設定処理
//====================================================================
void SetPlusScore(int nPlusScore)
{
	int aTexU[NUM_PLACE];
	int nCntPlusScore;

	g_nPlusScore = nPlusScore;

	aTexU[0] = g_nPlusScore % 1000 / 100;
	aTexU[1] = g_nPlusScore % 100 / 10;
	aTexU[2] = g_nPlusScore % 10 / 1;

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffPlusScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlusScore = 0; nCntPlusScore < NUM_PLACE; nCntPlusScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU[nCntPlusScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU[nCntPlusScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU[nCntPlusScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU[nCntPlusScore] * 0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlusScore->Unlock();
}

//====================================================================
//プラススコアの加算処理
//====================================================================
void AddPlusScore(int nValue)
{
	int aTexU[NUM_PLACE];
	int nCntPlusScore;

	g_nPlusScore += nValue;

	aTexU[0] = g_nPlusScore % 1000 / 100;
	aTexU[1] = g_nPlusScore % 100 / 10;
	aTexU[2] = g_nPlusScore % 10 / 1;

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffPlusScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlusScore = 0; nCntPlusScore < NUM_PLACE; nCntPlusScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU[nCntPlusScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU[nCntPlusScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU[nCntPlusScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU[nCntPlusScore] * 0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlusScore->Unlock();
}

//====================================================================
//プラススコアの所得
//====================================================================
int GetPlusScore(void)
{
	return g_nPlusScore;
}