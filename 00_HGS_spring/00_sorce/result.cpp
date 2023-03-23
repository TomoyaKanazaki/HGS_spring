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
#include "sound.h"

//==========================================
//  初期化処理
//==========================================
void InitResult()
{
	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM_RANKING);

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

	//サウンドの停止
	StopSound();
}

//==========================================
//  更新処理
//==========================================
void UpdateResult()
{
	UpdateRankingUI();

	UpdateRanKingNumber();

	UpdateNumberUI();

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
