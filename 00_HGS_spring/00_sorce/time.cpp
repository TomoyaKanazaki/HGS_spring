//==========================================
//
//  タイムの制御(time.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "time.h"
#include "polygon.h"
#include "texture.h"
#include "debugproc.h"
#include "pause.h"

#include "input.h"

//==========================================
//  マクロ定義
//==========================================
#define TIME_DIGIT (3) //桁数
#define START_TIME (60) //ゲーム時間 (1/1秒)
#define TIME_SIZE (100.0f) //タイムポリゴンのサイズ
#define TIME_POS (D3DXVECTOR3((float)SCREEN_WIDTH - 10.0f, TIME_SIZE, 0.0f)) //タイムの描画位置

//==========================================
//  プロトタイプ宣言
//==========================================
void CalcPauseTime(int nCurrentTime); //ポーズ中の時間を補正する
void SetTimePolygon(void); //ポリゴンを制御する関数

//==========================================
//  グローバル変数宣言
//==========================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;
int g_nTime; //残り時間 (1/1秒)
int g_nBaseTime; //基準時間 (1/1000秒)

//==========================================
//  初期化処理
//==========================================
void InitTime()
{
	//変数の初期化
	g_nTime = START_TIME;
	g_nBaseTime = timeGetTime();

	//ポリゴンの生成
	g_pVtxBuffTime = Init_2D_Polygon(TIME_DIGIT);
}

//==========================================
//  終了処理
//==========================================
void UninitTime()
{
	//ポリゴンの破棄
	UninitPolygon(&g_pVtxBuffTime);
}

//==========================================
//  更新処理
//==========================================
void UpdateTime()
{
	//ローカル変数宣言
	int nCurrentTime = timeGetTime(); //現在時間の取得 (1/1000秒)
	int nBetweenTime = 0; //基準時間と現在時間の差 (1/1秒)

	//ポーズ時間の補正
	CalcPauseTime(nCurrentTime);

	//基準時間と現在時間の差を取得 (1/1秒)
	nBetweenTime = (nCurrentTime - g_nBaseTime) / 1000;

	//残り時間の更新
	if (GetPause() == false)
	{
		g_nTime = START_TIME - nBetweenTime;
	}

	//ポリゴンの更新
	SetTimePolygon();

#ifdef _DEBUG
	//デバッグキー
	if (GetKeyboardTrigger(DIK_T))
	{
		//変数の初期化
		g_nTime = START_TIME;
		g_nBaseTime = timeGetTime();
	}
	if (GetKeyboardTrigger(DIK_UP))
	{
		g_nBaseTime += 1000;
	}
	if (GetKeyboardTrigger(DIK_DOWN))
	{
		g_nBaseTime -= 1000;
	}
	if (GetKeyboardTrigger(DIK_LEFT))
	{
		g_nBaseTime -= 10000;
	}
	if (GetKeyboardTrigger(DIK_RIGHT))
	{
		g_nBaseTime += 100000;
	}
#endif
	//デバッグ表示
	PrintDebugProc("経過時間 ( 1/1000s * 1000s = 1s ) : %d\n", nBetweenTime);
	PrintDebugProc("残り時間 ( 1/1000s * 1000s = 1s ) : %d\n", g_nTime);
}

//==========================================
//  描画処理
//==========================================
void DrawTime()
{
	//ローカル変数宣言
	int nNumDigit = TIME_DIGIT;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//残り時間から描画するポリゴン数を変化する
	if (g_nTime < 10)
	{
		nNumDigit -= 2;
	}
	else if (g_nTime < 100)
	{
		nNumDigit -= 1;
	}

	for (int nCnt = 0; nCnt < nNumDigit; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, GetTexture(TEXTURE_NUMBER));

		//メニュー項目の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}

//==========================================
//  ポーズ中の処理
//==========================================
void CalcPauseTime(int nCurrentTime)
{
	//変数宣言
	static int nPauseStartTime = 0;
	static int nPauseEndTime = 0;
	static int nPauseTime = 0;
	static bool bOldPause = false;

	//ポーズが開かれた瞬間の時間を保存
	if (bOldPause == false && GetPause())
	{
		nPauseStartTime += nCurrentTime;
	}

	//ポーズを閉じた時の処理
	if (bOldPause && GetPause() == false)
	{
		//ポーズが閉じられた瞬間の時間を保存
		nPauseEndTime += nCurrentTime;

		//ポーズが開かれていた時間を算出
		nPauseTime = nPauseEndTime - nPauseStartTime;

		//ポーズが開かれていた時間分基準時間を加算する
		g_nBaseTime += nPauseTime;
	}

	bOldPause = GetPause();
}

//==========================================
//  ポリゴンを制御する関数
//==========================================
void SetTimePolygon()
{
	//ローカル変数宣言
	int aTex[TIME_DIGIT];
	int nCntCount, nCalc;

	//最大数の取得
	nCalc = g_nTime;

	//テクスチャ座標の計測
	for (nCntCount = 0; nCntCount < TIME_DIGIT; nCntCount++)
	{
		aTex[nCntCount] = nCalc % 10;
		nCalc /= 10;
	}

	//頂点バッファの呼び出し
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//設定処理
	for (nCntCount = 0; nCntCount < TIME_DIGIT; nCntCount++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(TIME_POS.x - ((float)(nCntCount + 1.0f) * (TIME_SIZE * 0.6f)), TIME_POS.y - TIME_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(TIME_POS.x - ((float)nCntCount * (TIME_SIZE * 0.6f)), TIME_POS.y - TIME_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(TIME_POS.x - ((float)(nCntCount + 1.0f) * (TIME_SIZE * 0.6f)), TIME_POS.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(TIME_POS.x - ((float)nCntCount * (TIME_SIZE * 0.6f)), TIME_POS.y, 0.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(aTex[nCntCount] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aTex[nCntCount] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aTex[nCntCount] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aTex[nCntCount] * 0.1f) + 0.1f, 1.0f);

		//頂点データのポインタを4つ進める
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffTime->Unlock();
}

//==========================================
//  残り時間の取得
//==========================================
int GetTime()
{
	return g_nTime;
}
