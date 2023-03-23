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
#define TIME_NUM (3) //桁数
#define START_TIME (120) //ゲーム時間 (1/1秒)

//==========================================
//  プロトタイプ宣言
//==========================================
void CalcPauseTime(int nCurrentTime); //ポーズ中の時間を補正する

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
	g_pVtxBuffTime = Init_2D_Polygon(TIME_NUM);
}

//==========================================
//  終了処理
//==========================================
void UninitTime()
{

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

#ifdef _DEBUG
	//デバッグキー
	if (GetKeyboardTrigger(DIK_T))
	{
		//変数の初期化
		g_nTime = START_TIME;
		g_nBaseTime = timeGetTime();
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
