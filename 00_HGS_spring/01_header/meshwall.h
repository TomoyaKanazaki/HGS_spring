//======================================================================================================================
//
//	メッシュウォールヘッダー [meshwall.h]
//	Author：藤田勇一
//
//======================================================================================================================
#ifndef _MESHWALL_H_			// このマクロ定義がされていない場合
#define _MESHWALL_H_			// 二重インクルード防止のマクロを定義する

//**********************************************************************************************************************
//	マクロ定義
//**********************************************************************************************************************
#define MAX_MESHWALL	(256)	// メッシュウォールの最大数

//**********************************************************************************************************************
//	構造体定義 (MeshWall)
//**********************************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 rot;			// 向き
	D3DXMATRIX  mtxWorld;		// ワールドマトリックス
	float       fWidth;			// 横幅
	float       fHeight;		// 縦幅
	int         nPartWidth;		// 横の分割数
	int         nPartHeight;	// 縦の分割数
	int         nNumVtx;		// 必要頂点数
	int         nNumIdx;		// 必要インデックス数
	int         nType;			// 種類
	bool        bUse;			// 使用状況
} MeshWall;

//**********************************************************************************************************************
//	プロトタイプ宣言
//**********************************************************************************************************************
void InitMeshWall(void);		// メッシュウォールの初期化処理
void UninitMeshWall(void);		// メッシュウォールの終了処理
void UpdateMeshWall(void);		// メッシュウォールの更新処理
void DrawMeshWall(void);		// メッシュウォールの描画処理
MeshWall *GetMeshWall(void);	// メッシュウォールの取得処理

#endif