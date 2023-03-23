//============================================================
//
//	セットアップ処理 [load.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "load.h"
#include "limit.h"

//============================================================
//	ステージのセットアップ処理
//============================================================
void TxtSetStage(void)
{
	// 変数を宣言
	int   nEnd;			// テキスト読み込み終了の確認用
	Limit limit;		// ステージの移動範囲の代入用

	// 変数配列を宣言
	char aString[MAX_STRING];	// テキストの文字列の代入用

	// ポインタを宣言
	FILE *pFile;		// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen(STAGE_SETUP_TXT, "r");

	if (pFile != NULL)
	{ // ファイルが開けた場合

		do
		{ // 読み込んだ文字列が EOF ではない場合ループ

			// ファイルから文字列を読み込む
			nEnd = fscanf(pFile, "%s", &aString[0]);	// テキストを読み込みきったら EOF を返す

			//------------------------------------------------
			//	移動範囲の設定
			//------------------------------------------------
			if (strcmp(&aString[0], "STAGE_LIMITSET") == 0)
			{ // 読み込んだ文字列が STAGE_LIMITSET の場合

				do
				{ // 読み込んだ文字列が END_STAGE_LIMITSET ではない場合ループ

					// ファイルから文字列を読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "NEAR") == 0)
					{ // 読み込んだ文字列が NEAR の場合
						fscanf(pFile, "%s", &aString[0]);		// = を読み込む (不要)
						fscanf(pFile, "%f", &limit.fNear);		// 手前の制限位置を読み込む
					}
					else if (strcmp(&aString[0], "FAR") == 0)
					{ // 読み込んだ文字列が FAR の場合
						fscanf(pFile, "%s", &aString[0]);		// = を読み込む (不要)
						fscanf(pFile, "%f", &limit.fFar);		// 奥の制限位置を読み込む
					}
					else if (strcmp(&aString[0], "RIGHT") == 0)
					{ // 読み込んだ文字列が RIGHT の場合
						fscanf(pFile, "%s", &aString[0]);		// = を読み込む (不要)
						fscanf(pFile, "%f", &limit.fRight);		// 右の制限位置を読み込む
					}
					else if (strcmp(&aString[0], "LEFT") == 0)
					{ // 読み込んだ文字列が LEFT の場合
						fscanf(pFile, "%s", &aString[0]);		// = を読み込む (不要)
						fscanf(pFile, "%f", &limit.fLeft);		// 左の制限位置を読み込む
					}
					else if (strcmp(&aString[0], "FIELD") == 0)
					{ // 読み込んだ文字列が FIELD の場合
						fscanf(pFile, "%s", &aString[0]);		// = を読み込む (不要)
						fscanf(pFile, "%f", &limit.fField);		// 地面の制限位置を読み込む
					}
				} while (strcmp(&aString[0], "END_STAGE_LIMITSET") != 0);	// 読み込んだ文字列が END_STAGE_LIMITSET ではない場合ループ

				// 移動範囲の設定
				SetLimit(limit);
			}
		} while (nEnd != EOF);	// 読み込んだ文字列が EOF ではない場合ループ
		
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(NULL, "ステージファイルの読み込みに失敗！", "警告！", MB_ICONWARNING);
	}
}