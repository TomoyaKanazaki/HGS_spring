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
#include "meshdome.h"
#include "meshcylinder.h"
#include "meshfield.h"
#include "meshwall.h"

#include "Enemy.h"
#include "Bullet.h"
#include "effect.h"
#include "particle.h"
#include "player.h"

//==========================================
//  ����������
//==========================================
void InitGame()
{
	// �J�����̏�����
	InitCamera();

	// ���C�g�̏�����
	InitLight();

	//�G�̏�����
	InitEnemy();

	//�e�̏�����
	InitBullet();

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

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�p�[�e�B�N���̏�����
	InitParticle();

	//�|�[�Y�̏�����
	InitPause();

	//�v���C���[�̏�����
	InitPlayer();

	// �X�e�[�W�̃Z�b�g�A�b�v
	TxtSetStage();
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

	//�G�̏I��
	UninitEnemy();

	//�e�̏I��
	UninitBullet();

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

	//�G�t�F�N�g�̏I��
	UninitEffect();

	//�p�[�e�B�N���̏I��
	UninitParticle();

	//�|�[�Y�̏I��
	UninitPause();

	//�v���C���[�̏I��
	UninitPlayer();
}

//==========================================
//  �X�V����
//==========================================
void UpdateGame()
{
	if(GetPause() == false)
	{ // �|�[�Y������Ȃ��ꍇ

		//�G�̍X�V
		UpdateEnemy();

		//�e�̍X�V
		UpdateBullet();

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

		//�G�t�F�N�g�̍X�V
		UpdateEffect();

		//�p�[�e�B�N���̍X�V
		UpdateParticle();

		// �J�����̍X�V
		UpdateCamera();

		//�v���C���[�̍X�V
		UpdatePlayer();
	}
	else
	{ // �|�[�Y���̏ꍇ

		//�|�[�Y�̍X�V
		UpdatePause();
	}

	//�t�F�[�h
	if (GetKeyboardTrigger(DIK_RETURN))
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

	//�G�̕`��
	DrawEnemy();

	//�e�̕`��
	DrawBullet();

	// ���b�V���h�[���̕`��
	DrawMeshDome();

	// ���b�V���V�����_�[�̕`��
	DrawMeshCylinder();

	// ���b�V���t�B�[���h�̕`��
	DrawMeshField();

	// ���b�V���E�H�[���̕`��
	DrawMeshWall();

	// ���̕`��
	DrawArea();

	//�G�t�F�N�g�̕`��
	DrawEffect();

	//�p�[�e�B�N���̕`��
	DrawParticle();

	//�|�[�Y�̕`��
	DrawPause();

	//�v���C���[�̕`��
	DrawPlayer();
}
