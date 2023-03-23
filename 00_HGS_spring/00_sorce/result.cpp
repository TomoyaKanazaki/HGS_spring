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
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "meshdome.h"
#include "area.h"
#include "player.h"

//==========================================
//  ����������
//==========================================
void InitResult()
{
	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM_RANKING);

	InitTitleCamera();

	// ���C�g�̏�����
	InitLight();

	// ���̏�����
	InitArea();

	// ���b�V���h�[���̏�����
	InitMeshDome();

	// ���b�V���t�B�[���h�̏�����
	InitMeshField();

	InitPlayer();

	InitNumberUI();

	InitRankingUI();

	InitRanKingNumber();


}

//==========================================
//  �I������
//==========================================
void UninitResult()
{
	// ���̏�����
	UninitArea();

	// ���b�V���h�[���̏�����
	UninitMeshDome();

	// ���b�V���t�B�[���h�̏�����
	UninitMeshField();

	UninitPlayer();

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
	UpdateTitleCamera();

	// ���̏�����
	UpdateArea();

	// ���b�V���h�[���̏�����
	UpdateMeshDome();

	// ���b�V���t�B�[���h�̏�����
	UpdateMeshField();

	UpdatePlayer();

	UpdateRankingUI();

	UpdateRanKingNumber();

	UpdateNumberUI();

}

//==========================================
//  �`�揈��
//==========================================
void DrawResult()
{
	// �J�����̐ݒ�
	SetCamera(CAMERATYPE_TITLE);

	// ���̏�����
	DrawArea();

	// ���b�V���h�[���̏�����
	DrawMeshDome();

	// ���b�V���t�B�[���h�̏�����
	DrawMeshField();

	DrawPlayer();

	DrawRankingUI();

	DrawRanKingNumber();

	DrawNumberUI();
}
