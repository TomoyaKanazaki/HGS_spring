//==========================================
//
//  タイトルモードの制御(title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "title.h"
#include "fade.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "area.h"
#include "player.h"
#include "sound.h"

//==========================================
//  タイトル構造体の定義
//==========================================
typedef struct
{
	D3DXVECTOR3 pos;  //中心座標
	D3DXCOLOR col;    //色
	float fWidth;		//幅
	float fHeight;		//高さ
}TITLE;

//==========================================
//  マクロ定義
//==========================================
#define FWIDTH  (700) //幅
#define FHEIGHT (400) //高さ
#define MAX_TEX (2)   //テクスチャの最大数

//==========================================
//  グローバル変数宣言
//==========================================
LPDIRECT3DTEXTURE9 g_apTextureTitle[MAX_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点バッファへのポインタ

TITLE g_aTitle[MAX_TEX];
int g_nCntCol;

//==========================================
//  初期化処理
//==========================================
void InitTitle()
{
	InitTitleCamera();

	// ライトの初期化
	InitLight();

	// 区域の初期化
	InitArea();

	// メッシュフィールドの初期化
	InitMeshField();

	InitPlayer();

	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの所得

											 //初期化
	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		g_aTitle[nCntTex].pos = D3DXVECTOR3(250.0f, -500.0f, 0.0f);
		g_aTitle[nCntTex].fWidth = 0.0f;
		g_aTitle[nCntTex].fHeight = 0.0f;
	}

	g_aTitle[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aTitle[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"02_data\\02_TEXTURE\\escape.png",
		&g_apTextureTitle[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"02_data\\02_TEXTURE\\start.png",
		&g_apTextureTitle[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x, g_aTitle[nCntTex].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x + FWIDTH, g_aTitle[nCntTex].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x, g_aTitle[nCntTex].pos.y + FHEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x + FWIDTH, g_aTitle[nCntTex].pos.y + FHEIGHT, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);

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

	g_nCntCol = 0;

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();



	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM_TITLE);
}

//==========================================
//  終了処理
//==========================================
void UninitTitle()
{
	// 区域の初期化
	UninitArea();

	// メッシュフィールドの初期化
	UninitMeshField();

	UninitPlayer();

	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		//テクスチャの破棄
		if (g_apTextureTitle[nCntTex] != NULL)
		{
			g_apTextureTitle[nCntTex]->Release();
			g_apTextureTitle[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}



	//サウンドの停止
	StopSound();
}

//==========================================
//  更新処理
//==========================================
void UpdateTitle()
{
	UpdateTitleCamera();

	// 区域の初期化
	UpdateArea();

	// メッシュフィールドの初期化
	UpdateMeshField();

	UpdatePlayer();


	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (nCntTex == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x, g_aTitle[nCntTex].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x + FWIDTH, g_aTitle[nCntTex].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x, g_aTitle[nCntTex].pos.y + FHEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x + FWIDTH, g_aTitle[nCntTex].pos.y + FHEIGHT, 0.0f);
		}

		if (nCntTex == 1)
		{
			g_aTitle[nCntTex].pos = D3DXVECTOR3(100.0f, 500.0f, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x, g_aTitle[nCntTex].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x + 500.0f, g_aTitle[nCntTex].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x, g_aTitle[nCntTex].pos.y + 200.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x + 500.0f, g_aTitle[nCntTex].pos.y + 200.0f, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
		}

		float fDest = 160.0f;
		float fDiff = fDest - g_aTitle[nCntTex].pos.y;
		g_aTitle[nCntTex].pos.y += fDest * 0.05f;

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	if (g_aTitle[0].pos.y >= 30.0f)
	{//タイトルの位置が160以上だったら

		g_aTitle[0].pos.y = 30.0f;

		g_nCntCol++;

		if (g_nCntCol >= 100)
		{//カウントが100以下だったら

			g_aTitle[1].col.a -= 0.01f;
		}

		if (g_nCntCol <= 100)
		{//カウントが100以上だったら

			g_aTitle[1].col.a += 0.01f;
		}

		if (g_nCntCol >= 200)
		{//カウントが200以上だったら

			g_nCntCol = 0;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	//フェード
	if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadTrigger(BUTTON_START, 0) == true || GetGamepadTrigger(BUTTON_A, 0) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
	{
		SetFade(MODE_GAME);
	}
}

//==========================================
//  描画処理
//==========================================
void DrawTitle()
{
	// カメラの設定
	SetCamera(CAMERATYPE_TITLE);

	// 区域の初期化
	DrawArea();

	// メッシュフィールドの初期化
	DrawMeshField();

	DrawPlayer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTitle[nCntTex]);

		//メニュー項目の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
	}

}