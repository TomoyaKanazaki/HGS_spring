//======================================================================================================================
//
//	カメラヘッダー [camera.h]
//	Author：藤田勇一
//
//======================================================================================================================
#ifndef _CAMERA_H_					// このマクロ定義がされていない場合
#define _CAMERA_H_					// 二重インクルード防止のマクロを定義する

//**********************************************************************************************************************
//	マクロ定義
//**********************************************************************************************************************
#define CNT_ROT_FOLLOW	(50)		// 追従時の回り込みが始まるカウンターの値
#define VIEW_ANGLE		(D3DXToRadian(65.0f))	// 視野角

#define POS_R_PLUS		(25.0f)		// プレイヤーの位置と注視点の位置の距離 (x, z)
#define POS_R_PLUS_Y	(180.0f)	// プレイヤーの位置と注視点の位置の距離 (y)
#define POS_V_Y			(200.0f)	// 追従時の視点の位置 (y)

//**********************************************************************************************************************
//	列挙型定義 (CAMERATYPE)
//**********************************************************************************************************************
typedef enum
{
	CAMERATYPE_MAIN = 0,			// メインカメラ
	CAMERATYPE_TITLE,			    // タイトルカメラ
	CAMERATYPE_MAX,					// この列挙型の総数
} CAMERATYPE;

//**********************************************************************************************************************
//	構造体定義 (Camera)
//**********************************************************************************************************************
typedef struct
{
	D3DXVECTOR3  posV;				// 現在の視点
	D3DXVECTOR3  posVOld;			// 前回の視点
	D3DXVECTOR3  posR;				// 現在の注視点
	D3DXVECTOR3  destPosV;			// 目標の視点
	D3DXVECTOR3  destPosR;			// 目標の注視点
	D3DXVECTOR3  vecU;				// 上方向ベクトル
	D3DXVECTOR3  rot;				// 向き
	float        fDis;				// 現在の視点と注視点の距離
	float        fDestDis;			// 目標の視点と注視点の距離
	D3DXMATRIX   mtxProjection;		// プロジェクションマトリックス
	D3DXMATRIX   mtxView;			// ビューマトリックス
	D3DVIEWPORT9 viewport;			// ビューポート
} Camera;

//**********************************************************************************************************************
//	プロトタイプ宣言
//**********************************************************************************************************************
void InitCamera(void);				// カメラの初期化処理
void UninitCamera(void);			// カメラの終了処理
void UpdateCamera(void);			// カメラの更新処理
void SetCamera(int nID);			// カメラの設定処理
Camera *GetCamera(int nID);			// カメラの取得処理

void InitTitleCamera(void);				// カメラの初期化処理
void UpdateTitleCamera(void);			// カメラの更新処理

//**********************************************************************************************************************
//	プロトタイプ宣言 (デバッグ用)
//**********************************************************************************************************************
D3DXVECTOR3 GetCameraPosV(void);	// 視点座標の取得処理
D3DXVECTOR3 GetCameraPosR(void);	// 注視点座標の取得処理
D3DXVECTOR3 GetCameraRot(void);		// 向きの取得処理
float GetCameraDis(void);			// 距離の取得処理

#endif