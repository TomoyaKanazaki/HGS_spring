//==========================================
//
//  タイトルモードの制御(title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "title.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//==========================================
//  初期化処理
//==========================================
void InitTitle()
{




	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM_TITLE);
}

//==========================================
//  終了処理
//==========================================
void UninitTitle()
{




	//サウンドの停止
	StopSound();
}

//==========================================
//  更新処理
//==========================================
void UpdateTitle()
{
	//フェード
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadTrigger(BUTTON_START, 0) == true || GetGamepadTrigger(BUTTON_A, 0) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
	{
		SetFade(MODE_GAME);
	}
}

//==========================================
//  描画処理
//==========================================
void DrawTitle()
{

}
