//==========================================
//
//  �v���C���[�̐���(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "player.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "limit.h"
#include "particle.h"

//==========================================
//  �}�N����`
//==========================================
#define PLAYER_MOVE (6.0f) //�v���C���[�̈ړ���
#define PLAYER_ROTATE (0.1f) //�v���C���[�̕����]���̊���

//==========================================
//  �v���C���[�\���̂̒�`
//==========================================
typedef struct
{
	D3DXVECTOR3 pos; //���S���W
	D3DXVECTOR3 rot; //����
	D3DXVECTOR3 move; //�ړ���
	PLAYERSTATE state; //���
	Model ModelData; //���f�����
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
}PLAYER;

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void ChangeMovePlayer(void);
void ChangeRotPlayer(void);
void RevPosPlayer(void);

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
PLAYER g_Player; //�v���C���[���
bool g_bPlayerHit; //�Փ˔���t���O

//==========================================
//  ����������
//==========================================
void InitPlayer()
{
	//�ϐ��̏�����
	ZeroMemory(&g_Player, sizeof(PLAYER));
	g_bPlayerHit = false;

	//���f�����̎擾
	g_Player.ModelData = GetModelData(MODELTYPE_ESCAPEKUN);
}

//==========================================
//  �I������
//==========================================
void UninitPlayer()
{

}

//==========================================
//  �X�V����
//==========================================
void UpdatePlayer()
{
	if (g_Player.state != PLAYERSTATE_MAX)
	{
		if (GetMode() == MODE_TITLE)
		{
			g_Player.pos = D3DXVECTOR3(30.0f, 0.0f, 0.0f);

			g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f);
		}

		if (GetMode() != MODE_TITLE)
		{
			//�ړ�����
			ChangeMovePlayer();
		}

		// �v���C���[�̈ʒu�␳
		RevPosPlayer();
	}
}

//==========================================
//  �`�揈��
//==========================================
void DrawPlayer()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���[�J���ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat; //�}�e���A���ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_Player.ModelData.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_Player.ModelData.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		switch (g_Player.state)
		{
		case PLAYERSTATE_NORMAL:
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			break;
		default:
			break;
		}

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_Player.ModelData.pTexture[nCntMat]);
		
		if (g_Player.state != PLAYERSTATE_MAX)
		{
			//���f���̕`��
			g_Player.ModelData.pMesh->DrawSubset(nCntMat);
		}
	}

	//�ۑ����Ă���}�e���A���𕜌�
	pDevice->SetMaterial(&matDef);
}

//==========================================
//  �v���C���[�̈ʒu�����擾
//==========================================
D3DXVECTOR3 GetPosPlayer()
{
	return g_Player.pos;
}

//==========================================
//  �v���C���[�̈ړ�����
//==========================================
void ChangeMovePlayer()
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���Z�p�ϐ�
	bool bMove = false; //���͔���t���O

	//���͔���
	if (GetKeyboardPress(DIK_W) || GetGamepadTrigger(BUTTON_UP, 0) || GetGamepad_Stick_Left(0).y >= 0.2f) //�����
	{
		move.z += 1.0f;
		bMove = true;
	}
	if (GetKeyboardPress(DIK_S) || GetGamepadTrigger(BUTTON_DOWN, 0) || GetGamepad_Stick_Left(0).y <= -0.2f) //������
	{
		move.z -= 1.0f;
		bMove = true;
	}
	if (GetKeyboardPress(DIK_D) || GetGamepadTrigger(BUTTON_RIGHT, 0) || GetGamepad_Stick_Left(0).x >= 0.2f) //�E����
	{
		move.x += 1.0f;
		bMove = true;
	}
	if (GetKeyboardPress(DIK_A) || GetGamepadTrigger(BUTTON_LEFT, 0) || GetGamepad_Stick_Left(0).x <= -0.2f) //������
	{
		move.x -= 1.0f;
		bMove = true;
	}

	//�ړ��ʂ�����
	if (bMove)
	{
		//���͕␳(���K��)
		D3DXVec3Normalize(&g_Player.move, &move);

		g_Player.move.x *= PLAYER_MOVE;
		g_Player.move.z *= PLAYER_MOVE;
	}
	else
	{
		g_Player.move.x = g_Player.move.x;
		g_Player.move.z = g_Player.move.z;
	}

	//�ړ��ʂ����Z
	g_Player.pos += g_Player.move;

	//�����]��
	ChangeRotPlayer();

	//�f�o�b�O�\��
	PrintDebugProc("�G�X�P�[�v�N�͂����ɂ���! ( %f : %f : %f )\n", g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	PrintDebugProc("�G�X�P�[�v�N�͂������Ɍ������Ă�! ( %f : %f : %f )\n", g_Player.move.x, g_Player.move.y, g_Player.move.z);
	PrintDebugProc("�G�X�P�[�v�N�͂������������Ă���! ( %f : %f : %f )", g_Player.rot.x, g_Player.rot.y, g_Player.rot.z);
}

//==========================================
//  �v���C���[�̉�]����
//==========================================
void ChangeRotPlayer()
{
	//���[�J���ϐ��錾
	float fRotMove = g_Player.rot.y; //���݂̊p�x
	float fRotDest = g_Player.rot.y; //�ڕW�̊p�x
	float fRotDiff = g_Player.rot.y; //�ڕW�ƌ��݂̍�

	//�p�x�̍X�V
	fRotDest = atan2f(-g_Player.move.x, -g_Player.move.z);

	//�ڕW�p�x�ƌ��݊p�x�̍������Z�o
	fRotDiff = fRotDest - fRotMove;

	//���݂��Ȃ��p�x��␳
	if (fRotDiff > D3DX_PI || fRotDiff < -D3DX_PI)
	{//-3.14�`3.14�͈̔͊O�̏ꍇ
		if (fRotDiff > D3DX_PI)
		{
			fRotDiff += (-D3DX_PI * 2);
		}
		else if (fRotDiff <= -D3DX_PI)
		{
			fRotDiff += (D3DX_PI * 2);
		}
	}

	//�v���C���[�̌������X�V
	g_Player.rot.y += fRotDiff * PLAYER_ROTATE;

	//���݂��Ȃ��p�x��␳
	if (g_Player.rot.y > D3DX_PI || g_Player.rot.y < -D3DX_PI)
	{//-3.14�`3.14�͈̔͊O�̏ꍇ
		if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y += (-D3DX_PI * 2);
		}
		else if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y += (D3DX_PI * 2);
		}
	}
}

//==========================================
//  �v���C���[�̈ʒu�␳����
//==========================================
void RevPosPlayer(void)
{
	if (g_Player.pos.z > GetLimit().fNear - g_Player.ModelData.fRadius)
	{ // �͈͊O�̏ꍇ (��O)

		// ��O�Ɉʒu��␳
		g_Player.pos.z = GetLimit().fNear - g_Player.ModelData.fRadius;
	}
	if (g_Player.pos.z < GetLimit().fFar + g_Player.ModelData.fRadius)
	{ // �͈͊O�̏ꍇ (��)

		// ���Ɉʒu��␳
		g_Player.pos.z = GetLimit().fFar + g_Player.ModelData.fRadius;
	}
	if (g_Player.pos.x > GetLimit().fRight - g_Player.ModelData.fRadius)
	{ // �͈͊O�̏ꍇ (�E)

		// �E�Ɉʒu��␳
		g_Player.pos.x = GetLimit().fRight - g_Player.ModelData.fRadius;
	}
	if (g_Player.pos.x < GetLimit().fLeft + g_Player.ModelData.fRadius)
	{ // �͈͊O�̏ꍇ (��)

		// ���Ɉʒu��␳
		g_Player.pos.x = GetLimit().fLeft + g_Player.ModelData.fRadius;
	}
}

//==========================================
//  �����蔻��
//==========================================
bool GetCollisionPlayer(D3DXVECTOR3 pos, float fRadius)
{
	//���[�J���ϐ��錾
	float fJudgRadius = fRadius + g_Player.ModelData.fRadius; //���蔼�a
	float fDistance = (g_Player.pos.x - pos.x) * (g_Player.pos.x - pos.x) + (g_Player.pos.z - pos.z) * (g_Player.pos.z - pos.z); //�v���C���[�Ɣ���Ώۂ̋���

	//����
	if (fDistance < fJudgRadius * fJudgRadius)
	{
		g_bPlayerHit = true;
		g_Player.state = PLAYERSTATE_MAX;

		SetParticle(
				g_Player.pos,
				g_Player.rot,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			5,
			5.0f,
			6);
	}

	//�Ԃ�l��ݒ�
	return g_bPlayerHit;
}
