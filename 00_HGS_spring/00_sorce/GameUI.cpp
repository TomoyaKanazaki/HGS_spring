#include "main.h"
#include "GameUI.h"
#include "numberUI.h"
#include "player.h"
#include "game.h"
#include "time.h"

//マクロ定義
#define NUM_SSUI		(5)	//GAMEUIの種類数

#define POS_GAME_BG_X		(640.0f)	//「」のX座標の位置
#define POS_GAME_BG_Y		(360.0f)	//「」のY座標の位置
#define SIZE_GAME_BG_X		(640.0f)	//「」の幅
#define SIZE_GAME_BG_Y		(360.0f)	//「」の高さ

#define POS_SCORE_BG_X			(875.0f)	//「」のX座標の位置
#define POS_SCORE_BG_Y			(495.0f)	//「」のY座標の位置
#define SIZE_SCORE_BG_X			(340.0f)	//「」の幅
#define SIZE_SCORE_BG_Y			(400.0f)	//「」の高さ

#define POS_PERFECT_BG_X		(680.0f)	//「」のX座標の位置
#define POS_PERFECT_BG_Y		(430.0f)	//「」のY座標の位置
#define SIZE_PERFECT_BG_X		(115.0f)	//「」の幅
#define SIZE_PERFECT_BG_Y		(250.0f)		//「」の高さ

#define POS_ALLPERFECT_BG_X		(250.0f)	//「」のX座標の位置
#define POS_ALLPERFECT_BG_Y		(200.0f)	//「」のY座標の位置
#define SIZE_ALLPERFECT_BG_X	(200.0f)	//「」の幅
#define SIZE_ALLPERFECT_BG_Y	(100.0f)	//「」の高さ

#define POS_EXIT_BG_X			(250.0f)	//「」のX座標の位置
#define POS_EXIT_BG_Y			(450.0f)	//「」のY座標の位置
#define SIZE_EXIT_BG_X			(200.0f)	//「」の幅
#define SIZE_EXIT_BG_Y			(100.0f)	//「」の高さ

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureGameUI[NUM_SSUI] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameUI = NULL;		//頂点バッファへのポインタ
bool bUseGameUI[NUM_SSUI];		//頂点バッファへのポインタ
bool g_bStageClear_Game;

//====================================================================
//タイトル画面の初期化処理
//====================================================================
void InitGameUI(void)
{
	int nCntBG;
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの所得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAME\\Osumi00.png",
		&g_apTextureGameUI[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAME\\pepepepe02.png",
		&g_apTextureGameUI[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAME\\RankUi.png",
		&g_apTextureGameUI[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAME\\pepepepe01.png",
		&g_apTextureGameUI[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAME\\pepepepe03.png",
		&g_apTextureGameUI[4]);

	//UIの表示設定
	bUseGameUI[0] = false;
	bUseGameUI[1] = false;
	bUseGameUI[2] = false;
	bUseGameUI[3] = false;
	bUseGameUI[4] = false;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameUI,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_GAME_BG_X - SIZE_GAME_BG_X, POS_GAME_BG_Y - SIZE_GAME_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_GAME_BG_X + SIZE_GAME_BG_X, POS_GAME_BG_Y - SIZE_GAME_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_GAME_BG_X - SIZE_GAME_BG_X, POS_GAME_BG_Y + SIZE_GAME_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_GAME_BG_X + SIZE_GAME_BG_X, POS_GAME_BG_Y + SIZE_GAME_BG_Y, 0.0f);
			break;

		case 1:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_SCORE_BG_X - SIZE_SCORE_BG_X, POS_SCORE_BG_Y - SIZE_SCORE_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_SCORE_BG_X + SIZE_SCORE_BG_X, POS_SCORE_BG_Y - SIZE_SCORE_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_SCORE_BG_X - SIZE_SCORE_BG_X, POS_SCORE_BG_Y + SIZE_SCORE_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_SCORE_BG_X + SIZE_SCORE_BG_X, POS_SCORE_BG_Y + SIZE_SCORE_BG_Y, 0.0f);
			break;

		case 2:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_PERFECT_BG_X - SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y - SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_PERFECT_BG_X + SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y - SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_PERFECT_BG_X - SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y + SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_PERFECT_BG_X + SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y + SIZE_PERFECT_BG_Y, 0.0f);
			break;

		case 3:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X - SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y - SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X + SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y - SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X - SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y + SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X + SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y + SIZE_ALLPERFECT_BG_Y, 0.0f);
			break;

		case 4:
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(POS_EXIT_BG_X - SIZE_EXIT_BG_X, POS_EXIT_BG_Y - SIZE_EXIT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_EXIT_BG_X + SIZE_EXIT_BG_X, POS_EXIT_BG_Y - SIZE_EXIT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_EXIT_BG_X - SIZE_EXIT_BG_X, POS_EXIT_BG_Y + SIZE_EXIT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_EXIT_BG_X + SIZE_EXIT_BG_X, POS_EXIT_BG_Y + SIZE_EXIT_BG_Y, 0.0f);
			break;
		}

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
	g_pVtxBuffGameUI->Unlock();
}

//====================================================================
//タイトルの終了処理
//====================================================================
void UninitGameUI(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//テクスチャの破棄
		if (g_apTextureGameUI[nCntBG] != NULL)
		{
			g_apTextureGameUI[nCntBG]->Release();
			g_apTextureGameUI[nCntBG] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGameUI != NULL)
	{
		g_pVtxBuffGameUI->Release();
		g_pVtxBuffGameUI = NULL;
	}
}

//====================================================================
//タイトル画面の更新処理
//====================================================================
void UpdateGameUI(void)
{

}

//====================================================================
//タイトル画面の描画処理
//====================================================================
void DrawGameUI(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

							   //デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGameUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureGameUI[nCntBG]);

		if (bUseGameUI[nCntBG] == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntBG,						//プリミティブ(ポリゴン)数
				2);
		}
	}
}
//====================================================================
//ランキングUIの設定処理
//====================================================================
void SetGameUI(GAME SetClear, bool Clear)
{

}