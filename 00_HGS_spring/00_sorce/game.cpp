//==========================================
//
//  �Q�[�����[�h�̐���(game.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "game.h"
#include "pause.h"
#include "fade.h"
#include "input.h"
#include "load.h"

#include "area.h"
#include "camera.h"
#include "light.h"
#include "time.h"
#include "meshdome.h"
#include "meshcylinder.h"
#include "meshfield.h"
#include "meshwall.h"

#include "Enemy.h"
#include "Bullet.h"
#include "effect.h"
#include "particle.h"
#include "player.h"
#include "ScoreGauge.h"

//==========================================
//  ����������
//==========================================
void InitGame()
{
	// �J�����̏�����
	InitCamera();

	// ���C�g�̏�����
	InitLight();

	// ���b�V���h�[���̏�����
	InitMeshDome();

	// ���b�V���V�����_�[�̏�����
	InitMeshCylinder();

	// ���b�V���t�B�[���h�̏�����
	InitMeshField();

	// ���b�V���E�H�[���̏�����
	InitMeshWall();

	// ���̏�����
	InitArea();

	//�G�̏�����
	InitEnemy();

	//�e�̏�����
	InitBullet();

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�p�[�e�B�N���̏�����
	InitParticle();

	//�|�[�Y�̏�����
	InitPause();

	//�v���C���[�̏�����
	InitPlayer();

	//�^�C���̏�����
	InitTime();

	// �X�e�[�W�̃Z�b�g�A�b�v
	TxtSetStage();

	//�X�R�A�Q�[�W�̏�����
	InitScoreGauge();
}

//==========================================
//  �I������
//==========================================
void UninitGame()
{
	// �J�����̏I��
	UninitCamera();

	// ���C�g�̏I��
	UninitLight();

	// ���b�V���h�[���̏I��
	UninitMeshDome();

	// ���b�V���V�����_�[�̏I��
	UninitMeshCylinder();

	// ���b�V���t�B�[���h�̏I��
	UninitMeshField();

	// ���b�V���E�H�[���̏I��
	UninitMeshWall();

	// ���̏I��
	UninitArea();

	//�G�̏I��
	UninitEnemy();

	//�e�̏I��
	UninitBullet();

	//�G�t�F�N�g�̏I��
	UninitEffect();

	//�p�[�e�B�N���̏I��
	UninitParticle();

	//�|�[�Y�̏I��
	UninitPause();

	//�v���C���[�̏I��
	UninitPlayer();

	//�X�R�A�Q�[�W�̏I��
	UninitScoreGauge();

	//�^�C���̏I��
	UninitTime();
}

//==========================================
//  �X�V����
//==========================================
void UpdateGame()
{
	//�|�[�Y�̍X�V
	UpdatePause();

	//�^�C���̍X�V
	UpdateTime();

	if (GetPause() == false)
	{ // �|�[�Y������Ȃ��ꍇ

		// ���b�V���h�[���̍X�V
		UpdateMeshDome();

		// ���b�V���V�����_�[�̍X�V
		UpdateMeshCylinder();

		// ���b�V���t�B�[���h�̍X�V
		UpdateMeshField();

		// ���b�V���E�H�[���̍X�V
		UpdateMeshWall();

		// ���̍X�V
		UpdateArea();

		//�G�̍X�V
		UpdateEnemy();

		//�e�̍X�V
		UpdateBullet();

		//�G�t�F�N�g�̍X�V
		UpdateEffect();

		//�p�[�e�B�N���̍X�V
		UpdateParticle();

		//�v���C���[�̍X�V
		UpdatePlayer();

		// �J�����̍X�V
		UpdateCamera();

		//�X�R�A�Q�[�W�̍X�V
		UpdateScoreGauge();
	}

	//�t�F�[�h
	if (GetTime() <= 0)
	{
		SetFade(MODE_RESULT);
	}
}

//==========================================
//  �`�揈��
//=========================================
void DrawGame()
{
	// �J�����̐ݒ�
	SetCamera(CAMERATYPE_MAIN);

	// ���b�V���h�[���̕`��
	DrawMeshDome();

	// ���b�V���V�����_�[�̕`��
	DrawMeshCylinder();

	// ���̕`��
	DrawArea();

	// ���b�V���t�B�[���h�̕`��
	DrawMeshField();

	// ���b�V���E�H�[���̕`��
	DrawMeshWall();

	//�G�̕`��
	DrawEnemy();

	//�e�̕`��
	DrawBullet();

	//�G�t�F�N�g�̕`��
	DrawEffect();

	//�p�[�e�B�N���̕`��
	DrawParticle();

	//�|�[�Y�̕`��
	DrawPause();

	//�v���C���[�̕`��
	DrawPlayer();

	//�^�C���̕`��
	DrawTime();

	//�X�R�A�Q�[�W�̕`��
	DrawScoreGauge();
}
