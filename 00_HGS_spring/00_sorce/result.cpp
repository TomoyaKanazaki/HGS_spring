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
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "meshdome.h"
#include "area.h"
#include "player.h"

//==========================================
//  初期化処理
//==========================================
void InitResult()
{
	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM_RANKING);

	InitTitleCamera();

	// ライトの初期化
	InitLight();

	// 区域の初期化
	InitArea();

	// メッシュドームの初期化
	InitMeshDome();

	// メッシュフィールドの初期化
	InitMeshField();

	InitPlayer();

	InitNumberUI();

	InitRankingUI();

	InitRanKingNumber();


}

//==========================================
//  終了処理
//==========================================
void UninitResult()
{
	// 区域の初期化
	UninitArea();

	// メッシュドームの初期化
	UninitMeshDome();

	// メッシュフィールドの初期化
	UninitMeshField();

	UninitPlayer();

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
	UpdateTitleCamera();

	// 区域の初期化
	UpdateArea();

	// メッシュドームの初期化
	UpdateMeshDome();

	// メッシュフィールドの初期化
	UpdateMeshField();

	UpdatePlayer();

	UpdateRankingUI();

	UpdateRanKingNumber();

	UpdateNumberUI();

}

//==========================================
//  描画処理
//==========================================
void DrawResult()
{
	// カメラの設定
	SetCamera(CAMERATYPE_TITLE);

	// 区域の初期化
	DrawArea();

	// メッシュドームの初期化
	DrawMeshDome();

	// メッシュフィールドの初期化
	DrawMeshField();

	DrawPlayer();

	DrawRankingUI();

	DrawRanKingNumber();

	DrawNumberUI();
}
