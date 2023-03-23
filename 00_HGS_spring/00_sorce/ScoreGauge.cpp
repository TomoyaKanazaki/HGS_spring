#include "main.h"
#include "ScoreGauge.h"
#include "player.h"
#include "game.h"
#include "time.h"

//マクロ定義
#define NUM_SSUI		(4)	//GAMEUIの種類数

#define POS_YOKO_BG_X		(0.0f)		//「よこ」のX座標の位置
#define POS_YOKO_BG_Y		(0.0f)		//「よこ」のY座標の位置
#define SIZE_YOKO_BG_X		(1280.0f)	//「よこ」の幅
#define SIZE_YOKO_BG_Y		(10.0f)		//「よこ」の高さ

#define POS_TATE_BG_X		(1270.0f)	//「たて」のX座標の位置
#define POS_TATE_BG_Y		(0.0f)		//「たて」のY座標の位置
#define SIZE_TATE_BG_X		(10.0f)		//「たて」の幅
#define SIZE_TATE_BG_Y		(720.0f)	//「たて」の高さ

#define GAUGE_SPEED			(10.0f)	//ゲージのスピード

//構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//座標
	float fWidth;		//幅
	float fHeight;		//高さ
	bool bEnd;			//ポリゴンがたっせいしているかどうか
	bool bUse;			//ポリゴンを使っているかどうか
}SCOREGAUGE;

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureScoreGauge[NUM_SSUI] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreGauge = NULL;		//頂点バッファへのポインタ
SCOREGAUGE g_aSucoreGauge[NUM_SSUI];						//構造体
int g_TimeUpNumber;		//タイムオーバー演出の段階用変数

//====================================================================
//スコアゲージの初期化処理
//====================================================================
void InitScoreGauge(void)
{
	int nCntSG;
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの所得

	//テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\sunaarasi.png",
	//	&g_apTextureScoreGauge[0]);

	//グローバル変数初期化
	g_TimeUpNumber = -1;

	//UIの表示設定
	for (int nCntSG = 0; nCntSG < NUM_SSUI; nCntSG++)
	{
		switch (nCntSG)
		{
		case 0:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case 1:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(1270.0f, 0.0f, 0.0f);
			break;
		case 2:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(1280.0f, 710.0f, 0.0f);
			break;
		case 3:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(0.0f, 710.0f, 0.0f);
			break;
		}
		g_aSucoreGauge[nCntSG].fWidth = 10.0f;
		g_aSucoreGauge[nCntSG].fHeight = 10.0f;
		g_aSucoreGauge[nCntSG].bEnd = false;
		g_aSucoreGauge[nCntSG].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScoreGauge,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffScoreGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSG = 0; nCntSG < NUM_SSUI; nCntSG++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x, g_aSucoreGauge[nCntSG].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x + g_aSucoreGauge[nCntSG].fWidth, g_aSucoreGauge[nCntSG].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x, g_aSucoreGauge[nCntSG].pos.y + g_aSucoreGauge[nCntSG].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x + g_aSucoreGauge[nCntSG].fWidth, g_aSucoreGauge[nCntSG].pos.y + g_aSucoreGauge[nCntSG].fHeight, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScoreGauge->Unlock();

	SetScoreGauge();
}

//====================================================================
//タイトルの終了処理
//====================================================================
void UninitScoreGauge(void)
{
	int nCntSG;
	for (nCntSG = 0; nCntSG < NUM_SSUI; nCntSG++)
	{
		//テクスチャの破棄
		if (g_apTextureScoreGauge[nCntSG] != NULL)
		{
			g_apTextureScoreGauge[nCntSG]->Release();
			g_apTextureScoreGauge[nCntSG] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScoreGauge != NULL)
	{
		g_pVtxBuffScoreGauge->Release();
		g_pVtxBuffScoreGauge = NULL;
	}
}

//====================================================================
//スコアゲージの更新処理
//====================================================================
void UpdateScoreGauge(void)
{
	MODE mode = GetMode();

	if (g_TimeUpNumber != -1)
	{
		switch (g_TimeUpNumber)
		{
		case 0:
			if (g_aSucoreGauge[0].fWidth < SIZE_YOKO_BG_X &&
				g_aSucoreGauge[0].bEnd == false &&
				g_aSucoreGauge[0].bUse == true)
			{
				g_aSucoreGauge[0].fWidth += GAUGE_SPEED;
			}
			else
			{
				g_aSucoreGauge[0].bEnd = true;
				g_aSucoreGauge[1].bUse = true;
				g_TimeUpNumber++;
			}
			break;

		case 1:
			if (g_aSucoreGauge[1].fHeight < SIZE_TATE_BG_Y &&
				g_aSucoreGauge[1].bEnd == false &&
				g_aSucoreGauge[1].bUse == true)
			{
				g_aSucoreGauge[1].fHeight += GAUGE_SPEED;
			}
			else
			{
				g_aSucoreGauge[1].bEnd = true;
				g_aSucoreGauge[2].bUse = true;
				g_TimeUpNumber++;
			}
			break;

		case 2:
			if (g_aSucoreGauge[2].fWidth < SIZE_YOKO_BG_X &&
				g_aSucoreGauge[2].bEnd == false &&
				g_aSucoreGauge[2].bUse == true)
			{
				g_aSucoreGauge[2].pos.x -= GAUGE_SPEED;
				g_aSucoreGauge[2].fWidth += GAUGE_SPEED;
			}
			else
			{
				g_aSucoreGauge[2].bEnd = true;
				g_aSucoreGauge[3].bUse = true;
				g_TimeUpNumber++;
			}
			break;

		case 3:
			if (g_aSucoreGauge[3].fHeight < SIZE_TATE_BG_Y &&
				g_aSucoreGauge[3].bEnd == false &&
				g_aSucoreGauge[3].bUse == true)
			{
				g_aSucoreGauge[3].pos.y -= GAUGE_SPEED;
				g_aSucoreGauge[3].fHeight += GAUGE_SPEED;
			}
			else
			{
				g_aSucoreGauge[3].bEnd = true;
				SetScoreGauge();
			}
		}
	}

		VERTEX_2D*pVtx;	//頂点ポインタを所得

		//頂点バッファをロックし、両店情報へのポインタを所得
		g_pVtxBuffScoreGauge->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntSG = 0; nCntSG < NUM_SSUI; nCntSG++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x, g_aSucoreGauge[nCntSG].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x + g_aSucoreGauge[nCntSG].fWidth, g_aSucoreGauge[nCntSG].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x, g_aSucoreGauge[nCntSG].pos.y + g_aSucoreGauge[nCntSG].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x + g_aSucoreGauge[nCntSG].fWidth, g_aSucoreGauge[nCntSG].pos.y + g_aSucoreGauge[nCntSG].fHeight, 0.0f);

			pVtx += 4;	//頂点データのポインタを４つ分進める
		}

		//頂点バッファをアンロックする
		g_pVtxBuffScoreGauge->Unlock();
}

//====================================================================
//スコアゲージの描画処理
//====================================================================
void DrawScoreGauge(void)
{
	int nCntSG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScoreGauge, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntSG = 0; nCntSG < NUM_SSUI; nCntSG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureScoreGauge[nCntSG]);

		if (g_aSucoreGauge[nCntSG].bUse == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntSG,						//プリミティブ(ポリゴン)数
				2);
		}
	}
}

//====================================================================
//スコアゲージの設定処理
//====================================================================
void SetScoreGauge(void)
{
	for (int nCntSG = 0; nCntSG < NUM_SSUI; nCntSG++)
	{
		switch (nCntSG)
		{
		case 0:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case 1:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(1270.0f, 0.0f, 0.0f);
			break;
		case 2:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(1280.0f, 710.0f, 0.0f);
			break;
		case 3:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(0.0f, 710.0f, 0.0f);
			break;
		}

		g_aSucoreGauge[nCntSG].fWidth = 10.0f;
		g_aSucoreGauge[nCntSG].fHeight = 10.0f;
		g_aSucoreGauge[nCntSG].bEnd = false;
		if (nCntSG == 0)
		{
			g_aSucoreGauge[nCntSG].bUse = true;
		}
		else
		{
			g_aSucoreGauge[nCntSG].bUse = false;
		}
	}
	g_TimeUpNumber = 0;
}