#include "main.h"
#include "score.h"

//マクロ定義
#define NUM_PLACE (3)				//スコアの桁数

#define X_POS_GAME (100.0f)			//ゲーム画面の時のスコアのX座標
#define Y_POS_GAME (100.0f)			//ゲーム画面の時のスコアのY座標
#define X_SIZE_GAME (25.0f)			//ゲーム画面の時のスコアの横幅
#define Y_SIZE_GAME (25.0f)			//ゲーム画面の時のスコアの縦幅
#define WIDE_SIZE_GAME (100.0f)		//ゲーム画面の時のスコア同士の幅

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//頂点バッファのポインタ
D3DXVECTOR3 g_posScore[NUM_PLACE];					//スコアの位置
int g_nScore;										//スコアの値

//====================================================================
//スコアの初期化処理
//====================================================================
void InitScore(void)
{
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\NUMBER002.png",
	//	&g_pTextureScore);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		g_posScore[nCntScore] = D3DXVECTOR3(900.0f + nCntScore * WIDE_SIZE_GAME, 50.0f, 0.0f);
	}
	g_nScore = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(g_posScore[nCntScore].x - X_SIZE_GAME , g_posScore[nCntScore].y - Y_SIZE_GAME, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore[nCntScore].x + X_SIZE_GAME , g_posScore[nCntScore].y - Y_SIZE_GAME, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore[nCntScore].x - X_SIZE_GAME , g_posScore[nCntScore].y + Y_SIZE_GAME, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore[nCntScore].x + X_SIZE_GAME , g_posScore[nCntScore].y + Y_SIZE_GAME, 0.0f);

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
	g_pVtxBuffScore->Unlock();
}

//====================================================================
//スコアの終了処理
//====================================================================
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//====================================================================
//スコアの更新処理
//====================================================================
void UpdateScore(void)
{
	MODE g_Mode = GetMode();	//ゲームモードを所得
	int nCntScore;

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_Mode)
	{
	case MODE_GAME:
		for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
		{
			g_posScore[nCntScore] = D3DXVECTOR3(X_POS_GAME + nCntScore * WIDE_SIZE_GAME, Y_POS_GAME, 0.0f);

			//頂点座標の設定 
			pVtx[0].pos = D3DXVECTOR3(g_posScore[nCntScore].x - X_SIZE_GAME, g_posScore[nCntScore].y - Y_SIZE_GAME, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posScore[nCntScore].x + X_SIZE_GAME, g_posScore[nCntScore].y - Y_SIZE_GAME, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posScore[nCntScore].x - X_SIZE_GAME, g_posScore[nCntScore].y + Y_SIZE_GAME, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posScore[nCntScore].x + X_SIZE_GAME, g_posScore[nCntScore].y + Y_SIZE_GAME, 0.0f);

			pVtx += 4;	//頂点データのポインタを４つ分進める

		}
		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//====================================================================
//スコアの描画処理
//====================================================================
void DrawScore(void)
{
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);
	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			4 * nCntScore,							//プリミティブ(ポリゴン)数
			2);
	}
}

//====================================================================
//スコアの設定処理
//====================================================================
void SetScore(int nScore)
{
	int aTexU[NUM_PLACE];
	int nCntScore;

	g_nScore = nScore;

	aTexU[0] = g_nScore % 1000 / 100;
	aTexU[1] = g_nScore % 100 / 10;
	aTexU[2] = g_nScore % 10 / 1;

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU[nCntScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU[nCntScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU[nCntScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU[nCntScore] * 0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//====================================================================
//スコアの加算処理
//====================================================================
void AddScore(int nValue)
{
	int aTexU[NUM_PLACE];
	int nCntScore;

	g_nScore += nValue;

	aTexU[0] = g_nScore % 1000 / 100;
	aTexU[1] = g_nScore % 100 / 10;
	aTexU[2] = g_nScore % 10 / 1;

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU[nCntScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU[nCntScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU[nCntScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU[nCntScore] * 0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//====================================================================
//スコアの所得
//====================================================================
int GetScore(void)
{
	return g_nScore;
}