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

#include "camera.h"
#include "light.h"
#include "meshdome.h"
#include "meshcylinder.h"
#include "meshfield.h"
#include "meshwall.h"

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

	// ���b�V���h�[���̏�����
	InitMeshDome();

	// ���b�V���V�����_�[�̏�����
	InitMeshCylinder();

	// ���b�V���t�B�[���h�̏�����
	InitMeshField();

	// ���b�V���E�H�[���̏�����
	InitMeshWall();

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

	// ���b�V���h�[���̏I��
	UninitMeshDome();

	// ���b�V���V�����_�[�̏I��
	UninitMeshCylinder();

	// ���b�V���t�B�[���h�̏I��
	UninitMeshField();

	// ���b�V���E�H�[���̏I��
	UninitMeshWall();

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

		// ���b�V���h�[���̍X�V
		UpdateMeshDome();

		// ���b�V���V�����_�[�̍X�V
		UpdateMeshCylinder();

		// ���b�V���t�B�[���h�̍X�V
		UpdateMeshField();

		// ���b�V���E�H�[���̍X�V
		UpdateMeshWall();

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

	// ���b�V���h�[���̕`��
	DrawMeshDome();

	// ���b�V���V�����_�[�̕`��
	DrawMeshCylinder();

	// ���b�V���t�B�[���h�̕`��
	DrawMeshField();

	// ���b�V���E�H�[���̕`��
	DrawMeshWall();

	//�|�[�Y�̕`��
	DrawPause();

	//�v���C���[�̕`��
	DrawPlayer();
}
