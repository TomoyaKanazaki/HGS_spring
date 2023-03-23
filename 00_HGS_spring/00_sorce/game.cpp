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

#include "Enemy.h"
#include "Bullet.h"
#include "effect.h"
#include "particle.h"
#include "player.h"

//==========================================
//  初期化処理
//==========================================
void InitGame()
{
	// カメラの初期化
	InitCamera();

	// ライトの初期化
	InitLight();

	//敵の初期化
	InitEnemy();

	//弾の初期化
	InitBullet();

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

	//エフェクトの初期化
	InitEffect();

	//パーティクルの初期化
	InitParticle();

	//ポーズの初期化
	InitPause();

	//プレイヤーの初期化
	InitPlayer();

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

	//敵の終了
	UninitEnemy();

	//弾の終了
	UninitBullet();

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

	//エフェクトの終了
	UninitEffect();

	//パーティクルの終了
	UninitParticle();

	//ポーズの終了
	UninitPause();

	//プレイヤーの終了
	UninitPlayer();
}

//==========================================
//  更新処理
//==========================================
void UpdateGame()
{
	if(GetPause() == false)
	{ // ポーズ中じゃない場合

		//敵の更新
		UpdateEnemy();

		//弾の更新
		UpdateBullet();

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

		//エフェクトの更新
		UpdateEffect();

		//パーティクルの更新
		UpdateParticle();

		// カメラの更新
		UpdateCamera();

		//プレイヤーの更新
		UpdatePlayer();
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

	//敵の描画
	DrawEnemy();

	//弾の描画
	DrawBullet();

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

	//エフェクトの描画
	DrawEffect();

	//パーティクルの描画
	DrawParticle();

	//ポーズの描画
	DrawPause();

	//プレイヤーの描画
	DrawPlayer();
}
