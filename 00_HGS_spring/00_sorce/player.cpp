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

//==========================================
//  マクロ定義
//==========================================
#define PLAYER_MOVE (5.0f); //プレイヤーの移動量

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
void MovePlayer(void);

//==========================================
//  グローバル変数宣言
//==========================================
PLAYER g_Player; //プレイヤー情報

//==========================================
//  初期化処理
//==========================================
void InitPlayer()
{
	//変数の初期化
	ZeroMemory(&g_Player, sizeof(PLAYER));

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
	//移動処理
	MovePlayer();
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

		//モデルの描画
		g_Player.ModelData.pMesh->DrawSubset(nCntMat);
	}

	//保存しているマテリアルを復元
	pDevice->SetMaterial(&matDef);
}

//==========================================
//  プレイヤーの移動処理
//==========================================
void MovePlayer()
{
	//ローカル変数宣言
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//入力判定
	if (GetKeyboardPress(DIK_W) || GetGamepadTrigger(BUTTON_UP, 0) || GetGamepad_Stick_Left(0).y >= 0.2f) //上方向
	{
		move.z += 1.0f;
	}
	if (GetKeyboardPress(DIK_S) || GetGamepadTrigger(BUTTON_DOWN, 0) || GetGamepad_Stick_Left(0).y <= -0.2f) //下方向
	{
		move.z -= 1.0f;
	}
	if (GetKeyboardPress(DIK_D) || GetGamepadTrigger(BUTTON_RIGHT, 0) || GetGamepad_Stick_Left(0).x >= 0.2f) //右方向
	{
		move.x += 1.0f;
	}
	if (GetKeyboardPress(DIK_A) || GetGamepadTrigger(BUTTON_LEFT, 0) || GetGamepad_Stick_Left(0).x <= -0.2f) //左方向
	{
		move.x -= 1.0f;
	}

	//入力補正(正規化)
	D3DXVec3Normalize(&g_Player.move, &move);

	//移動量を決定
	g_Player.move.x *= PLAYER_MOVE;
	g_Player.move.z *= PLAYER_MOVE;

	//移動量を加算
	g_Player.pos += g_Player.move;

	//デバッグ表示
	PrintDebugProc("エスケープ君はここにいる! ( %f : %f : %f )\n", g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	PrintDebugProc("エスケープ君はこっちに向かってる! ( %f : %f : %f )", g_Player.move.x, g_Player.move.y, g_Player.move.z);
}
