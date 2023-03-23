//============================================================
//
//	カメラ処理 [camera.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "area.h"

#include "debugproc.h"

//************************************************************
//	マクロ定義
//************************************************************
// カメラ全般
#define VIEW_NEAR		(10.0f)		// モデルが見えるZ軸の最小値
#define VIEW_FAR		(8000.0f)	// モデルが見えるZ軸の最大値

// メインカメラ
#define FIRST_ROT		(1.45f)		// 開始時の視点と注視点の間の向き (x)
#define FIRST_DIS		(-500.0f)	// 開始時の視点と注視点の間の距離

#define REV_ROT_FOLLOW	(0.05f)		// 追従時の回り込みの補正係数
#define REV_POS_V		(0.225f)	// 視点の位置の補正係数 (x, z)
#define REV_POS_R		(0.25f)		// 注視点の位置の補正係数 (x, z)
#define REV_POS_V_Y		(0.045f)	// 視点の位置の補正係数 (y)
#define REV_POS_R_Y		(0.05f)		// 注視点の位置の補正係数 (y)
#define REV_DIS_CAM		(0.05f)		// 距離の補正係数

#define MOVE_CAMERA		(4.0f)		// カメラの移動量
#define MOVE_ROT_X		(0.015f)	// 向きの変更量 (x)
#define MOVE_ROT_Y		(0.03f)		// 向きの変更量 (y)
#define MOVE_DIS		(2.0f)		// 距離の変更量
#define REV_DIS			(-1.0f)		// 距離の補正値

#define REV_DIS_MOUSE	(-0.15f)	// マウス操作でのカメラの距離の補正係数
#define REV_ROT_MOUSE	(0.008f)	// マウス操作でのカメラの回転量の補正係数

#define MUL_ANGLE_PLUS	(1.8f)		// ブースト時の視野角増加の乗算量

#define LIMIT_ROT_HIGH	(D3DX_PI - 0.1f)	// 回転量 (x) の回転制限値 (上)
#define LIMIT_ROT_LOW	(0.1f)				// 回転量 (x) の回転制限値 (下)

//************************************************************
//	コンスト定義
//************************************************************
const float aDisCamera[] =	// 区域の半径
{
	-650.0f,				// セーフエリア
	-650.0f,				// 第一エリア
	-550.0f,				// 第二エリア
	-550.0f,				// 第三エリア
	-450.0f,				// 第四エリア
	-450.0f,				// レッドエリア
};

//const float aDisCamera[] =	// 区域の半径
//{
//	-2000.0f,				// セーフエリア
//	-2000.0f,				// 第一エリア
//	-2000.0f,				// 第二エリア
//	-2000.0f,				// 第三エリア
//	-2000.0f,				// 第四エリア
//	-2000.0f,				// レッドエリア
//};

//************************************************************
//	プロトタイプ宣言
//************************************************************
void MoveFollowCamera(void);		// メインカメラの位置の更新処理 (追従)

void MoveCamera(void);				// メインカメラの位置の更新処理 (操作)
void DisCamera(void);				// メインカメラの距離の更新処理 (操作)
void RotCamera(void);				// メインカメラの向きの更新処理 (操作)

void RevRotXCamera(void);			// カメラの向きの補正処理 (x)
void RevRotYCamera(void);			// カメラの向きの補正処理 (y)

//************************************************************
//	グローバル変数
//************************************************************
Camera g_aCamera[CAMERATYPE_MAX];	// カメラの情報

//============================================================
//	カメラの初期化処理
//============================================================
void InitCamera(void)
{
	// 基本情報を初期化
	g_aCamera[CAMERATYPE_MAIN].posV     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 現在の視点
	g_aCamera[CAMERATYPE_MAIN].posVOld  = g_aCamera[CAMERATYPE_MAIN].posV;		// 前回の視点
	g_aCamera[CAMERATYPE_MAIN].posR     = D3DXVECTOR3(0.0f, 800.0f, 0.0f);		// 現在の注視点
	g_aCamera[CAMERATYPE_MAIN].destPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目標の視点
	g_aCamera[CAMERATYPE_MAIN].destPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目標の注視点
	g_aCamera[CAMERATYPE_MAIN].vecU     = D3DXVECTOR3(0.0f, 0.0f, 1.0f);		// 上方向ベクトル
	g_aCamera[CAMERATYPE_MAIN].rot      = D3DXVECTOR3(FIRST_ROT, 0.0f, 0.0f);	// 向き
	g_aCamera[CAMERATYPE_MAIN].fDis     = FIRST_DIS;							// 現在の視点と注視点の距離
	g_aCamera[CAMERATYPE_MAIN].fDestDis = g_aCamera[CAMERATYPE_MAIN].fDis;		// 目標の視点と注視点の距離

	// ビューポート情報を初期化
	g_aCamera[CAMERATYPE_MAIN].viewport.X      = 0;				// 左上隅のピクセル座標 (x)
	g_aCamera[CAMERATYPE_MAIN].viewport.Y      = 0;				// 左上隅のピクセル座標 (y)
	g_aCamera[CAMERATYPE_MAIN].viewport.Width  = SCREEN_WIDTH;	// 描画する画面の横幅
	g_aCamera[CAMERATYPE_MAIN].viewport.Height = SCREEN_HEIGHT;	// 描画する画面の縦幅
	g_aCamera[CAMERATYPE_MAIN].viewport.MinZ   = 0.0f;
	g_aCamera[CAMERATYPE_MAIN].viewport.MaxZ   = 1.0f;
}

//============================================================
//	カメラの終了処理
//============================================================
void UninitCamera(void)
{

}

//============================================================
//	カメラの更新処理
//============================================================
void UpdateCamera(void)
{
#if 1
	// カメラの位置の更新 (追従)
	MoveFollowCamera();
#else
	// 上方向ベクトルを設定
	g_aCamera[CAMERATYPE_MAIN].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// カメラの位置の更新 (操作)
	MoveCamera();

	// カメラの距離の更新 (操作)
	DisCamera();

	// カメラの向きの更新 (操作)
	RotCamera();
#endif

#ifdef _DEBUG	// デバッグ処理
	// 視点と注視点の表示
	PrintDebugProc("\n");
	PrintDebugProc("【 視点 】%f %f %f\n", g_aCamera[CAMERATYPE_MAIN].posV.x, g_aCamera[CAMERATYPE_MAIN].posV.y, g_aCamera[CAMERATYPE_MAIN].posV.z);
	PrintDebugProc("【注視点】%f %f %f\n", g_aCamera[CAMERATYPE_MAIN].posR.x, g_aCamera[CAMERATYPE_MAIN].posR.y, g_aCamera[CAMERATYPE_MAIN].posR.z);
#endif
}

//============================================================
//	カメラの設定処理
//============================================================
void SetCamera(int nID)
{
	// ポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスへのポインタ

	// ビューポートの設定
	pDevice->SetViewport(&g_aCamera[nID].viewport);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_aCamera[nID].mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH
	( // 引数
		&g_aCamera[nID].mtxProjection,													// プロジェクションマトリックス
		VIEW_ANGLE,																		// 視野角
		(float)g_aCamera[nID].viewport.Width / (float)g_aCamera[nID].viewport.Height,	// 画面のアスペクト比
		VIEW_NEAR,																		// Z軸の最小値
		VIEW_FAR																		// Z軸の最大値
	);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_aCamera[nID].mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_aCamera[nID].mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH
	( // 引数
		&g_aCamera[nID].mtxView,	// ビューマトリックス
		&g_aCamera[nID].posV,		// 視点
		&g_aCamera[nID].posR,		// 注視点
		&g_aCamera[nID].vecU		// 上方向ベクトル
	);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_aCamera[nID].mtxView);
}

//======================================================================================================================
//	メインカメラの位置の更新処理 (追従)
//======================================================================================================================
void MoveFollowCamera(void)
{
	// 変数を宣言
	float fDiffDis = 0.0f;	// 差分の計算用

	// 上方向ベクトルを設定
	g_aCamera[CAMERATYPE_MAIN].vecU = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	// 目標の距離を設定
	g_aCamera[CAMERATYPE_MAIN].fDestDis = aDisCamera[(int)GetCurrentArea()];

	// 差分の距離を求める
	fDiffDis = g_aCamera[CAMERATYPE_MAIN].fDestDis - g_aCamera[CAMERATYPE_MAIN].fDis;

	// 距離を設定
	g_aCamera[CAMERATYPE_MAIN].fDis += fDiffDis * REV_DIS_CAM;

	// 視点の位置を更新
	g_aCamera[CAMERATYPE_MAIN].posV = GetPosPlayer();
	g_aCamera[CAMERATYPE_MAIN].posV.y -= g_aCamera[CAMERATYPE_MAIN].fDis;

	// 注視点の位置を更新
	g_aCamera[CAMERATYPE_MAIN].posR = GetPosPlayer();
}

//============================================================
//	メインカメラの位置の更新処理 (操作)
//============================================================
void MoveCamera(void)
{
	//--------------------------------------------------------
	//	マウス操作の更新
	//--------------------------------------------------------
	if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == true)
	{ // 右クリックと左クリックが押されている場合

		// 視点を移動
		g_aCamera[CAMERATYPE_MAIN].posV.x -= sinf(g_aCamera[CAMERATYPE_MAIN].rot.y + (D3DX_PI * 0.5f)) * GetMouseMove().x;
		g_aCamera[CAMERATYPE_MAIN].posV.z -= cosf(g_aCamera[CAMERATYPE_MAIN].rot.y + (D3DX_PI * 0.5f)) * GetMouseMove().x;

		g_aCamera[CAMERATYPE_MAIN].posV.x += sinf(g_aCamera[CAMERATYPE_MAIN].rot.y) * GetMouseMove().y;
		g_aCamera[CAMERATYPE_MAIN].posV.z += cosf(g_aCamera[CAMERATYPE_MAIN].rot.y) * GetMouseMove().y;

		// 注視点を移動
		g_aCamera[CAMERATYPE_MAIN].posR.x -= sinf(g_aCamera[CAMERATYPE_MAIN].rot.y + (D3DX_PI * 0.5f)) * GetMouseMove().x;
		g_aCamera[CAMERATYPE_MAIN].posR.z -= cosf(g_aCamera[CAMERATYPE_MAIN].rot.y + (D3DX_PI * 0.5f)) * GetMouseMove().x;

		g_aCamera[CAMERATYPE_MAIN].posR.x += sinf(g_aCamera[CAMERATYPE_MAIN].rot.y) * GetMouseMove().y;
		g_aCamera[CAMERATYPE_MAIN].posR.z += cosf(g_aCamera[CAMERATYPE_MAIN].rot.y) * GetMouseMove().y;
	}
}

//============================================================
//	メインカメラの距離の更新処理 (操作)
//============================================================
void DisCamera(void)
{
	//--------------------------------------------------------
	//	マウス操作の更新
	//--------------------------------------------------------
	if (GetMouseMove().z != 0.0f)
	{ // マウスホイールの移動量が 0.0f ではない場合

		// マウスの z移動量の方向に視点を移動
		g_aCamera[CAMERATYPE_MAIN].fDis += GetMouseMove().z * REV_DIS_MOUSE;
	}

	//--------------------------------------------------------
	//	距離の補正
	//--------------------------------------------------------
	if (g_aCamera[CAMERATYPE_MAIN].fDis > REV_DIS)
	{ // 最低距離を上回った場合

		// 最低距離に補正
		g_aCamera[CAMERATYPE_MAIN].fDis = REV_DIS;
	}
}

//============================================================
//	メインカメラの向きの更新処理 (操作)
//============================================================
void RotCamera(void)
{
	//--------------------------------------------------------
	//	マウス操作の更新
	//--------------------------------------------------------
	if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == false)
	{ // 左クリックだけが押されている場合

		// マウスの x移動量の方向に y軸を回転
		g_aCamera[CAMERATYPE_MAIN].rot.y += GetMouseMove().x * REV_ROT_MOUSE;

		// マウスの y移動量の方向に x軸を回転
		g_aCamera[CAMERATYPE_MAIN].rot.x += GetMouseMove().y * REV_ROT_MOUSE;
	}

	//--------------------------------------------------------
	//	向きの補正
	//--------------------------------------------------------
	// 向きの補正 (x)
	RevRotXCamera();

	// 向きの補正 (y)
	RevRotYCamera();

	//--------------------------------------------------------
	//	視点の更新
	//--------------------------------------------------------
	g_aCamera[CAMERATYPE_MAIN].posV.x = g_aCamera[CAMERATYPE_MAIN].posR.x + ((g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * sinf(g_aCamera[CAMERATYPE_MAIN].rot.y));
	g_aCamera[CAMERATYPE_MAIN].posV.y = g_aCamera[CAMERATYPE_MAIN].posR.y + ((g_aCamera[CAMERATYPE_MAIN].fDis * cosf(g_aCamera[CAMERATYPE_MAIN].rot.x)));
	g_aCamera[CAMERATYPE_MAIN].posV.z = g_aCamera[CAMERATYPE_MAIN].posR.z + ((g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * cosf(g_aCamera[CAMERATYPE_MAIN].rot.y));

	//--------------------------------------------------------
	//	マウス操作の更新
	//--------------------------------------------------------
	if (GetMousePress(PUSH_RIGHT) == true && GetMousePress(PUSH_LEFT) == false)
	{ // 右クリックだけが押されている場合

		// マウスの x移動量の方向に y軸を回転
		g_aCamera[CAMERATYPE_MAIN].rot.y += GetMouseMove().x * REV_ROT_MOUSE;

		// マウスの y移動量の方向に x軸を回転
		g_aCamera[CAMERATYPE_MAIN].rot.x += GetMouseMove().y * REV_ROT_MOUSE;
	}

	//--------------------------------------------------------
	//	向きの補正
	//--------------------------------------------------------
	// 向きの補正 (x)
	RevRotXCamera();

	// 向きの補正 (y)
	RevRotYCamera();

	//--------------------------------------------------------
	//	注視点の更新
	//--------------------------------------------------------
	g_aCamera[CAMERATYPE_MAIN].posR.x = g_aCamera[CAMERATYPE_MAIN].posV.x + ((-g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * sinf(g_aCamera[CAMERATYPE_MAIN].rot.y));
	g_aCamera[CAMERATYPE_MAIN].posR.y = g_aCamera[CAMERATYPE_MAIN].posV.y + ((-g_aCamera[CAMERATYPE_MAIN].fDis * cosf(g_aCamera[CAMERATYPE_MAIN].rot.x)));
	g_aCamera[CAMERATYPE_MAIN].posR.z = g_aCamera[CAMERATYPE_MAIN].posV.z + ((-g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * cosf(g_aCamera[CAMERATYPE_MAIN].rot.y));
}

//============================================================
//	カメラの向きの補正処理 (x)
//============================================================
void RevRotXCamera(void)
{
	if (g_aCamera[CAMERATYPE_MAIN].rot.x > LIMIT_ROT_HIGH)
	{ // 回転量 (x) が LIMIT_ROT_HIGH を超えた場合

		// LIMIT_ROT_HIGH を代入 (制限)
		g_aCamera[CAMERATYPE_MAIN].rot.x = LIMIT_ROT_HIGH;
	}
	else if (g_aCamera[CAMERATYPE_MAIN].rot.x < LIMIT_ROT_LOW)
	{ // 回転量 (x) が LIMIT_ROT_LOW を超えた場合

		// LIMIT_ROT_LOW を代入 (制限)
		g_aCamera[CAMERATYPE_MAIN].rot.x = LIMIT_ROT_LOW;
	}
}

//============================================================
//	カメラの向きの補正処理 (y)
//============================================================
void RevRotYCamera(void)
{
	if (g_aCamera[CAMERATYPE_MAIN].rot.y > D3DX_PI)
	{ // 回転量 (y) が D3DX_PI を超えた場合

		// D3DX_PIを代入 (制限)
		g_aCamera[CAMERATYPE_MAIN].rot.y = D3DX_PI;

		// 回転量 (y) を反転させる
		g_aCamera[CAMERATYPE_MAIN].rot.y *= -1.0f;
	}
	else if (g_aCamera[CAMERATYPE_MAIN].rot.y < -D3DX_PI)
	{ // 回転量 (y) が -D3DX_PI を超えた場合

		// -D3DX_PIを代入 (制限)
		g_aCamera[CAMERATYPE_MAIN].rot.y = -D3DX_PI;

		// 回転量 (y) を反転させる
		g_aCamera[CAMERATYPE_MAIN].rot.y *= -1.0f;
	}
}

//============================================================
//	カメラの取得処理
//============================================================
Camera *GetCamera(int nID)
{
	// カメラの情報の引数の要素のアドレスを返す
	return &g_aCamera[nID];
}

#ifdef _DEBUG	// デバッグ処理
//============================================================
//	デバッグ処理一覧
//============================================================
//************************************************************
//	視点座標の取得処理
//************************************************************
D3DXVECTOR3 GetCameraPosV(void)
{
	// 視点座標を返す
	return g_aCamera[CAMERATYPE_MAIN].posV;
}

//************************************************************
//	注視点座標の取得処理
//************************************************************
D3DXVECTOR3 GetCameraPosR(void)
{
	// 注視点座標を返す
	return g_aCamera[CAMERATYPE_MAIN].posR;
}

//************************************************************
//	向きの取得処理
//************************************************************
D3DXVECTOR3 GetCameraRot(void)
{
	// 向きを返す
	return g_aCamera[CAMERATYPE_MAIN].rot;
}

//************************************************************
//	距離の取得処理
//************************************************************
float GetCameraDis(void)
{
	// 距離を返す
	return g_aCamera[CAMERATYPE_MAIN].fDis;
}
#endif