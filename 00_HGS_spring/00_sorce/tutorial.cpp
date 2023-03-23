//==========================================
//
//  チュートリアルの制御(tutorial.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial.h"
#include "input.h"
#include "polygon.h"
#include "texture.h"
#include "fade.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;		//頂点バッファへのポインタ

//==========================================
//  初期化処理
//==========================================
void InitTutorial()
{
	g_pVtxBuffTutorial = Init_2D_Polygon();

	VERTEX_2D *pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();
}

void UninitTutorial()
{
	UninitPolygon(&g_pVtxBuffTutorial);
}

void UpdateTutorial()
{
	if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadTrigger(BUTTON_START, 0) == true || GetGamepadTrigger(BUTTON_A, 0) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
	{
		SetFade(MODE_GAME);
	}
}

void DrawTutorial()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, GetTexture(TEXTURE_TUTORIAL));

	//メニュー項目の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}