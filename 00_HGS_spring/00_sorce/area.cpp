//======================================================================================================================
//
//	区域処理 [area.cpp]
//	Author：藤田勇一
//
//======================================================================================================================
//**********************************************************************************************************************
//	インクルードファイル
//**********************************************************************************************************************
#include "main.h"
#include "area.h"

//**********************************************************************************************************************
//	マクロ定義
//**********************************************************************************************************************
#define MAX_AREA		(5)			// 使用するポリゴン数 (区域表示の最大数)

//**********************************************************************************************************************
//	コンスト定義
//**********************************************************************************************************************
const char *apTextureArea[] =		// テクスチャの相対パス
{
	"data\\TEXTURE\\area000.jpg",	// 区域のテクスチャの相対パス
};

const float aRadiusArea[] =	// 区域の半径
{
	500.0f,					// 第一エリア
	1000.0f,				// 第二エリア
	2000.0f,				// 第三エリア
	3000.0f,				// 第四エリア
	4000.0f,				// 第五エリア
};

//**********************************************************************************************************************
//	構造体定義 (Area)
//**********************************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXMATRIX  mtxWorld;	// ワールドマトリックス
}Area;

//**********************************************************************************************************************
//	列挙型定義 (TEXTURE_AREA)
//**********************************************************************************************************************
typedef enum
{
	TEXTURE_AREA_NORMAL = 0,		// 区域 (通常)
	TEXTURE_AREA_MAX,				// この列挙型の総数
} TEXTURE_AREA;

//**********************************************************************************************************************
//	グローバル変数
//**********************************************************************************************************************
LPDIRECT3DTEXTURE9      g_apTextureArea[TEXTURE_AREA_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArea = NULL;					// 頂点バッファへのポインタ

Area g_aArea[MAX_AREA];				// 区域の情報

//======================================================================================================================
//	区域の初期化処理
//======================================================================================================================
void InitArea(void)
{
	// ポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスへのポインタ
	VERTEX_3D *pVtx;							// 頂点情報へのポインタ

	// テクスチャの読み込み
	for (int nCntArea = 0; nCntArea < TEXTURE_AREA_MAX; nCntArea++)
	{ // 使用するテクスチャ数分繰り返す

		D3DXCreateTextureFromFile(pDevice, apTextureArea[nCntArea], &g_apTextureArea[nCntArea]);
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer
	( // 引数
		sizeof(VERTEX_3D) * 4 * MAX_AREA,		// 必要頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,							// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffArea,
		NULL
	);

	// 区域の情報の初期化
	for (int nCntArea = 0; nCntArea < MAX_AREA; nCntArea++)
	{ // 区域の最大表示数分繰り返す

		g_aArea[nCntArea].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
		g_aArea[nCntArea].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	}

	//------------------------------------------------------------------------------------------------------------------
	//	頂点情報の初期化
	//------------------------------------------------------------------------------------------------------------------
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffArea->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntArea = 0; nCntArea < MAX_AREA; nCntArea++)
	{ // 区域の最大表示数分繰り返す

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-aRadiusArea[nCntArea], 0.0f, +aRadiusArea[nCntArea]);
		pVtx[1].pos = D3DXVECTOR3(+aRadiusArea[nCntArea], 0.0f, +aRadiusArea[nCntArea]);
		pVtx[2].pos = D3DXVECTOR3(-aRadiusArea[nCntArea], 0.0f, -aRadiusArea[nCntArea]);
		pVtx[3].pos = D3DXVECTOR3(+aRadiusArea[nCntArea], 0.0f, -aRadiusArea[nCntArea]);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.2f, 0.2f, 0.2f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.2f, 0.2f, 0.2f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.2f, 0.2f, 0.2f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.2f, 0.2f, 0.2f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データのポインタを 4つ分進める
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffArea->Unlock();
}

//======================================================================================================================
//	区域の終了処理
//======================================================================================================================
void UninitArea(void)
{
	// テクスチャの破棄
	for (int nCntArea = 0; nCntArea < TEXTURE_AREA_MAX; nCntArea++)
	{ // 使用するテクスチャ数分繰り返す

		if (g_apTextureArea[nCntArea] != NULL)
		{ // 変数 (g_apTextureArea) がNULLではない場合

			g_apTextureArea[nCntArea]->Release();
			g_apTextureArea[nCntArea] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffArea != NULL)
	{ // 変数 (g_pVtxBuffArea) がNULLではない場合

		g_pVtxBuffArea->Release();
		g_pVtxBuffArea = NULL;
	}
}

//======================================================================================================================
//	区域の更新処理
//======================================================================================================================
void UpdateArea(void)
{

}

//======================================================================================================================
//	区域の描画処理
//======================================================================================================================
void DrawArea(void)
{
	// 変数を宣言
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスへのポインタ

	// Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);		// Zテストの設定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			// Zバッファ更新の有効 / 無効の設定

	// αブレンディングを減算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntArea = 0; nCntArea < MAX_AREA; nCntArea++)
	{ // 区域の最大表示数分繰り返す

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aArea[nCntArea].mtxWorld);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aArea[nCntArea].rot.y, g_aArea[nCntArea].rot.x, g_aArea[nCntArea].rot.z);
		D3DXMatrixMultiply(&g_aArea[nCntArea].mtxWorld, &g_aArea[nCntArea].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aArea[nCntArea].pos.x, g_aArea[nCntArea].pos.y, g_aArea[nCntArea].pos.z);
		D3DXMatrixMultiply(&g_aArea[nCntArea].mtxWorld, &g_aArea[nCntArea].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aArea[nCntArea].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffArea, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_apTextureArea[TEXTURE_AREA_NORMAL]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntArea * 4, 2);
	}

	// Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);		// Zテストの設定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			// Zバッファ更新の有効 / 無効の設定

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}