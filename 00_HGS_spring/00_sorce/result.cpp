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
#include "sound.h"

//==========================================
//  ����������
//==========================================
void InitResult()
{
	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM_RANKING);

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

	//�T�E���h�̒�~
	StopSound();
}

//==========================================
//  �X�V����
//==========================================
void UpdateResult()
{
	UpdateRankingUI();

	UpdateRanKingNumber();

	UpdateNumberUI();

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
