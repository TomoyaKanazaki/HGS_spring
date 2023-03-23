//==========================================
//
//  ゲームモードの制御(game.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "game.h"
#include "pause.h"
#include "fade.h"
#include "input.h"
#include "load.h"

#include "area.h"
#include "camera.h"
#include "light.h"
#include "meshdome.h"
#include "meshcylinder.h"
#include "meshfield.h"
#include "meshwall.h"

//==========================================
//  初期化処理
//==========================================
void InitGame()
{
	// カメラの初期化
	InitCamera();

	// ライトの初期化
	InitLight();

	// メッシュドームの初期化
	InitMeshDome();

	// メッシュシリンダーの初期化
	InitMeshCylinder();

	// メッシュフィールドの初期化
	InitMeshField();

	// メッシュウォールの初期化
	InitMeshWall();

	// 区域の初期化
	InitArea();

	//ポーズの初期化
	InitPause();

	// ステージのセットアップ
	TxtSetStage();
}

//==========================================
//  終了処理
//==========================================
void UninitGame()
{
	// カメラの終了
	UninitCamera();

	// ライトの終了
	UninitLight();

	// メッシュドームの終了
	UninitMeshDome();

	// メッシュシリンダーの終了
	UninitMeshCylinder();

	// メッシュフィールドの終了
	UninitMeshField();

	// メッシュウォールの終了
	UninitMeshWall();

	// 区域の終了
	UninitArea();

	//ポーズの終了
	UninitPause();
}

//==========================================
//  更新処理
//==========================================
void UpdateGame()
{
	if(GetPause() == false)
	{ // ポーズ中じゃない場合

		// メッシュドームの更新
		UpdateMeshDome();

		// メッシュシリンダーの更新
		UpdateMeshCylinder();

		// メッシュフィールドの更新
		UpdateMeshField();

		// メッシュウォールの更新
		UpdateMeshWall();

		// 区域の更新
		UpdateArea();

		// カメラの更新
		UpdateCamera();
	}
	else
	{ // ポーズ中の場合

		//ポーズの更新
		UpdatePause();
	}

	//フェード
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetFade(MODE_RESULT);
	}
}

//==========================================
//  描画処理
//=========================================
void DrawGame()
{
	// カメラの設定
	SetCamera(CAMERATYPE_MAIN);

	// メッシュドームの描画
	DrawMeshDome();

	// メッシュシリンダーの描画
	DrawMeshCylinder();

	// メッシュフィールドの描画
	DrawMeshField();

	// メッシュウォールの描画
	DrawMeshWall();

	// 区域の描画
	DrawArea();

	//ポーズの描画
	DrawPause();
}
