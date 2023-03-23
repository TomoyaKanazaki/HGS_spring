//==========================================
//
//  プレイヤーの制御(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "player.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "limit.h"
#include "particle.h"

//==========================================
//  マクロ定義
//==========================================
#define PLAYER_MOVE (6.0f) //プレイヤーの移動量
#define PLAYER_ROTATE (0.1f) //プレイヤーの方向転換の慣性

//==========================================
//  プレイヤー構造体の定義
//==========================================
typedef struct
{
	D3DXVECTOR3 pos; //中心座標
	D3DXVECTOR3 rot; //向き
	D3DXVECTOR3 move; //移動量
	PLAYERSTATE state; //状態
	Model ModelData; //モデル情報
	D3DXMATRIX mtxWorld; //ワールドマトリックス
}PLAYER;

//==========================================
//  プロトタイプ宣言
//==========================================
void ChangeMovePlayer(void);
void ChangeRotPlayer(void);
void RevPosPlayer(void);

//==========================================
//  グローバル変数宣言
//==========================================
PLAYER g_Player; //プレイヤー情報
bool g_bPlayerHit; //衝突判定フラグ

//==========================================
//  初期化処理
//==========================================
void InitPlayer()
{
	//変数の初期化
	ZeroMemory(&g_Player, sizeof(PLAYER));
	g_bPlayerHit = false;

	//モデル情報の取得
	g_Player.ModelData = GetModelData(MODELTYPE_ESCAPEKUN);
}

//==========================================
//  終了処理
//==========================================
void UninitPlayer()
{

}

//==========================================
//  更新処理
//==========================================
void UpdatePlayer()
{
	if (g_Player.state != PLAYERSTATE_MAX)
	{
		if (GetMode() == MODE_TITLE)
		{
			g_Player.pos = D3DXVECTOR3(30.0f, 0.0f, 0.0f);

			g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f);
		}

		if (GetMode() != MODE_TITLE)
		{
			//移動処理
			ChangeMovePlayer();
		}

		// プレイヤーの位置補正
		RevPosPlayer();
	}
}

//==========================================
//  描画処理
//==========================================
void DrawPlayer()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef; //現在のマテリアルの保存用
	D3DXMATERIAL *pMat; //マテリアルへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_Player.ModelData.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Player.ModelData.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		switch (g_Player.state)
		{
		case PLAYERSTATE_NORMAL:
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			break;
		default:
			break;
		}

		//テクスチャの設定
		pDevice->SetTexture(0, g_Player.ModelData.pTexture[nCntMat]);
		
		if (g_Player.state != PLAYERSTATE_MAX)
		{
			//モデルの描画
			g_Player.ModelData.pMesh->DrawSubset(nCntMat);
		}
	}

	//保存しているマテリアルを復元
	pDevice->SetMaterial(&matDef);
}

//==========================================
//  プレイヤーの位置情報を取得
//==========================================
D3DXVECTOR3 GetPosPlayer()
{
	return g_Player.pos;
}

//==========================================
//  プレイヤーの移動処理
//==========================================
void ChangeMovePlayer()
{
	//ローカル変数宣言
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //演算用変数
	bool bMove = false; //入力判定フラグ

	//入力判定
	if (GetKeyboardPress(DIK_W) || GetGamepadTrigger(BUTTON_UP, 0) || GetGamepad_Stick_Left(0).y >= 0.2f) //上方向
	{
		move.z += 1.0f;
		bMove = true;
	}
	if (GetKeyboardPress(DIK_S) || GetGamepadTrigger(BUTTON_DOWN, 0) || GetGamepad_Stick_Left(0).y <= -0.2f) //下方向
	{
		move.z -= 1.0f;
		bMove = true;
	}
	if (GetKeyboardPress(DIK_D) || GetGamepadTrigger(BUTTON_RIGHT, 0) || GetGamepad_Stick_Left(0).x >= 0.2f) //右方向
	{
		move.x += 1.0f;
		bMove = true;
	}
	if (GetKeyboardPress(DIK_A) || GetGamepadTrigger(BUTTON_LEFT, 0) || GetGamepad_Stick_Left(0).x <= -0.2f) //左方向
	{
		move.x -= 1.0f;
		bMove = true;
	}

	//移動量を決定
	if (bMove)
	{
		//入力補正(正規化)
		D3DXVec3Normalize(&g_Player.move, &move);

		g_Player.move.x *= PLAYER_MOVE;
		g_Player.move.z *= PLAYER_MOVE;
	}
	else
	{
		g_Player.move.x = g_Player.move.x;
		g_Player.move.z = g_Player.move.z;
	}

	//移動量を加算
	g_Player.pos += g_Player.move;

	//方向転換
	ChangeRotPlayer();

	//デバッグ表示
	PrintDebugProc("エスケープ君はここにいる! ( %f : %f : %f )\n", g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	PrintDebugProc("エスケープ君はこっちに向かってる! ( %f : %f : %f )\n", g_Player.move.x, g_Player.move.y, g_Player.move.z);
	PrintDebugProc("エスケープ君はこっちを向いている! ( %f : %f : %f )", g_Player.rot.x, g_Player.rot.y, g_Player.rot.z);
}

//==========================================
//  プレイヤーの回転処理
//==========================================
void ChangeRotPlayer()
{
	//ローカル変数宣言
	float fRotMove = g_Player.rot.y; //現在の角度
	float fRotDest = g_Player.rot.y; //目標の角度
	float fRotDiff = g_Player.rot.y; //目標と現在の差

	//角度の更新
	fRotDest = atan2f(-g_Player.move.x, -g_Player.move.z);

	//目標角度と現在角度の差分を算出
	fRotDiff = fRotDest - fRotMove;

	//存在しない角度を補正
	if (fRotDiff > D3DX_PI || fRotDiff < -D3DX_PI)
	{//-3.14～3.14の範囲外の場合
		if (fRotDiff > D3DX_PI)
		{
			fRotDiff += (-D3DX_PI * 2);
		}
		else if (fRotDiff <= -D3DX_PI)
		{
			fRotDiff += (D3DX_PI * 2);
		}
	}

	//プレイヤーの向きを更新
	g_Player.rot.y += fRotDiff * PLAYER_ROTATE;

	//存在しない角度を補正
	if (g_Player.rot.y > D3DX_PI || g_Player.rot.y < -D3DX_PI)
	{//-3.14～3.14の範囲外の場合
		if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y += (-D3DX_PI * 2);
		}
		else if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y += (D3DX_PI * 2);
		}
	}
}

//==========================================
//  プレイヤーの位置補正処理
//==========================================
void RevPosPlayer(void)
{
	if (g_Player.pos.z > GetLimit().fNear - g_Player.ModelData.fRadius)
	{ // 範囲外の場合 (手前)

		// 手前に位置を補正
		g_Player.pos.z = GetLimit().fNear - g_Player.ModelData.fRadius;
	}
	if (g_Player.pos.z < GetLimit().fFar + g_Player.ModelData.fRadius)
	{ // 範囲外の場合 (奥)

		// 奥に位置を補正
		g_Player.pos.z = GetLimit().fFar + g_Player.ModelData.fRadius;
	}
	if (g_Player.pos.x > GetLimit().fRight - g_Player.ModelData.fRadius)
	{ // 範囲外の場合 (右)

		// 右に位置を補正
		g_Player.pos.x = GetLimit().fRight - g_Player.ModelData.fRadius;
	}
	if (g_Player.pos.x < GetLimit().fLeft + g_Player.ModelData.fRadius)
	{ // 範囲外の場合 (左)

		// 左に位置を補正
		g_Player.pos.x = GetLimit().fLeft + g_Player.ModelData.fRadius;
	}
}

//==========================================
//  当たり判定
//==========================================
bool GetCollisionPlayer(D3DXVECTOR3 pos, float fRadius)
{
	//ローカル変数宣言
	float fJudgRadius = fRadius + g_Player.ModelData.fRadius; //判定半径
	float fDistance = (g_Player.pos.x - pos.x) * (g_Player.pos.x - pos.x) + (g_Player.pos.z - pos.z) * (g_Player.pos.z - pos.z); //プレイヤーと判定対象の距離

	//判定
	if (fDistance < fJudgRadius * fJudgRadius)
	{
		g_bPlayerHit = true;
		g_Player.state = PLAYERSTATE_MAX;

		SetParticle(
				g_Player.pos,
				g_Player.rot,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			5,
			5.0f,
			6);
	}

	//返り値を設定
	return g_bPlayerHit;
}
