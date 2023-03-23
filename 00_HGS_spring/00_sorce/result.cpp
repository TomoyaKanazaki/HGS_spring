//==========================================
//
//  ���U���g���[�h�̐���(result.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "result.h"
#include "fade.h"
#include "input.h"
#include "rankingnumber.h"
#include "NumberUI.h"
#include "RAnkingUI.h"

//==========================================
//  ����������
//==========================================
void InitResult()
{
	InitNumberUI();

	InitRankingUI();

	InitRanKingNumber();
}

//==========================================
//  �I������
//==========================================
void UninitResult()
{
	UninitRankingUI();

	UninitRanKingNumber();

	UninitNumberUI();
}

//==========================================
//  �X�V����
//==========================================
void UpdateResult()
{
	UpdateRankingUI();

	UpdateRanKingNumber();

	UpdateNumberUI();

	//�t�F�[�h
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetFade(MODE_TITLE);
	}
}

//==========================================
//  �`�揈��
//==========================================
void DrawResult()
{
	DrawRankingUI();

	DrawRanKingNumber();

	DrawNumberUI();
}
