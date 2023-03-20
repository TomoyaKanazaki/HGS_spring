//==========================================
//
//  フェードの制御(fade.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "fade.h"
#include "polygon.h"

//==========================================
//  マクロ定義
//==========================================
#define FADE_FRAME (30.0f) //フェードにかかる時間

//==========================================
//  グローバル変数宣言
//==========================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL; //頂点情報を格納
FADE g_fade;
MODE g_NextMode;
D3DXCOLOR g_ColorFade;

//==========================================
//  初期化処理
//==========================================
void InitFade(MODE nextmode)
{
	//各種データの初期化
	g_fade = FADE_IN;
	g_NextMode = nextmode;
	g_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//頂点バッファの生成
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL
	);

	//頂点バッファの呼び出し
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//法線ベクトルの設定
		pVtx[nCnt].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//頂点バッファをアンロック
	g_pVtxBuffFade->Unlock();

	//モードの設定
	SetMode(g_NextMode);
}

//==========================================
//  終了処理
//==========================================
void UninitFade(void)
{
	//ポリゴンの破棄
	UninitPolygon(&g_pVtxBuffFade);
}

//==========================================
//  更新処理
//==========================================
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{
		switch (g_fade)
		{
		case FADE_IN:
			//アルファ値の更新
			g_ColorFade.a -= 1.0f / FADE_FRAME;

			//フェードが完了した場合
			if (g_ColorFade.a <= 0.0f)
			{
				g_ColorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
			break;
		case FADE_OUT:
			//アルファ値の更新
			g_ColorFade.a += 1.0f / FADE_FRAME;

			//フェードが完了した場合
			if (g_ColorFade.a >= 1.0f)
			{
				g_ColorFade.a = 1.0f;
				g_fade = FADE_IN;

				//モードを設定
				SetMode(g_NextMode);
			}
		}
		//頂点バッファの呼び出し
		VERTEX_2D *pVtx;

		//頂点バッファをロック
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの更新
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].col = g_ColorFade;
		}

		//頂点バッファをアンロック
		g_pVtxBuffFade->Unlock();
	}
}

//==========================================
//  描画処理
//==========================================
void DrawFade(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==========================================
//  設定処理
//==========================================
void SetFade(MODE nextmode)
{
	//各種データの設定
	if (g_fade == FADE_NONE)
	{
		g_fade = FADE_OUT;
		g_NextMode = nextmode;
		g_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

//==========================================
//  フェード状態の取得
//==========================================
FADE GetFade(void)
{
	return g_fade;
}
