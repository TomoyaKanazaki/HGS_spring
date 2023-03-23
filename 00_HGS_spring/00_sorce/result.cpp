//==========================================
//
//  リザルトモードの制御(result.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "result.h"
#include "fade.h"
#include "input.h"
#include "rankingnumber.h"
#include "NumberUI.h"
#include "RAnkingUI.h"

//==========================================
//  初期化処理
//==========================================
void InitResult()
{
	InitNumberUI();

	InitRankingUI();

	InitRanKingNumber();
}

//==========================================
//  終了処理
//==========================================
void UninitResult()
{
	UninitRankingUI();

	UninitRanKingNumber();

	UninitNumberUI();
}

//==========================================
//  更新処理
//==========================================
void UpdateResult()
{
	UpdateRankingUI();

	UpdateRanKingNumber();

	UpdateNumberUI();

	//フェード
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetFade(MODE_TITLE);
	}
}

//==========================================
//  描画処理
//==========================================
void DrawResult()
{
	DrawRankingUI();

	DrawRanKingNumber();

	DrawNumberUI();
}
