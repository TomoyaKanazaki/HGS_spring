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

//==========================================
//  �}�N����`
//==========================================
#define PLAYER_MOVE (5.0f); //�v���C���[�̈ړ���

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
void MovePlayer(void);

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
PLAYER g_Player; //�v���C���[���

//==========================================
//  ����������
//==========================================
void InitPlayer()
{
	//�ϐ��̏�����
	ZeroMemory(&g_Player, sizeof(PLAYER));

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
	//�ړ�����
	MovePlayer();
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

		//���f���̕`��
		g_Player.ModelData.pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă���}�e���A���𕜌�
	pDevice->SetMaterial(&matDef);
}

//==========================================
//  �v���C���[�̈ړ�����
//==========================================
void MovePlayer()
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���͔���
	if (GetKeyboardPress(DIK_W) || GetGamepadTrigger(BUTTON_UP, 0) || GetGamepad_Stick_Left(0).y >= 0.2f) //�����
	{
		move.z += 1.0f;
	}
	if (GetKeyboardPress(DIK_S) || GetGamepadTrigger(BUTTON_DOWN, 0) || GetGamepad_Stick_Left(0).y <= -0.2f) //������
	{
		move.z -= 1.0f;
	}
	if (GetKeyboardPress(DIK_D) || GetGamepadTrigger(BUTTON_RIGHT, 0) || GetGamepad_Stick_Left(0).x >= 0.2f) //�E����
	{
		move.x += 1.0f;
	}
	if (GetKeyboardPress(DIK_A) || GetGamepadTrigger(BUTTON_LEFT, 0) || GetGamepad_Stick_Left(0).x <= -0.2f) //������
	{
		move.x -= 1.0f;
	}

	//���͕␳(���K��)
	D3DXVec3Normalize(&g_Player.move, &move);

	//�ړ��ʂ�����
	g_Player.move.x *= PLAYER_MOVE;
	g_Player.move.z *= PLAYER_MOVE;

	//�ړ��ʂ����Z
	g_Player.pos += g_Player.move;

	//�f�o�b�O�\��
	PrintDebugProc("�G�X�P�[�v�N�͂����ɂ���! ( %f : %f : %f )\n", g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	PrintDebugProc("�G�X�P�[�v�N�͂������Ɍ������Ă�! ( %f : %f : %f )", g_Player.move.x, g_Player.move.y, g_Player.move.z);
}
