#include "main.h"
#include "particle.h"
#include "effect.h"

//�}�N����`
#define MAX_PARTICLE (128)		//�p�[�e�B�N���̍ő吔
#define STANDERD_SPEED (1.0f)	//�p�[�e�B�N���̊�̃X�s�[�h
#define RAND_PAI1 (17)			//�p�x�̃����_��
#define PUT_PARTICLE1 (1)		//�P�t���[���ɏo���p�[�e�B�N���̐�
#define RAND_PAI2 (365)			//�p�x�̃����_��
#define PUT_PARTICLE2 (5)		//�P�t���[���ɏo���p�[�e�B�N���̐�
#define RAND_PAI3 (731)			//�p�x�̃����_��
#define PUT_PARTICLE3 (3)		//�P�t���[���ɏo���p�[�e�B�N���̐�

#define RAND_PAI5 (629)			//�p�x�̃����_��
#define PUT_PARTICLE5 (7)		//�P�t���[���ɏo���p�[�e�B�N���̐�
#define RAND_PAI6 (629)			//�p�x�̃����_��
#define PUT_PARTICLE6 (30)		//�P�t���[���ɏo���p�[�e�B�N���̐�

//�O���[�o���ϐ�
Particle g_aParticle[MAX_PARTICLE];							//�p�[�e�B�N���̏��
D3DXVECTOR3 move;
//====================================================================
//�p�[�e�B�N���̏���������
//====================================================================
void InitParticle(void)
{
	int nCntParticle;

	//�p�[�e�B�N���̏��̏�����
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
	}
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================================================
//�p�[�e�B�N���̏I������
//====================================================================
void UninitParticle(void)
{

}

//====================================================================
//�p�[�e�B�N���̍X�V����
//====================================================================
void UpdateParticle(void)
{
	int nCntParticle;
	int nCntAppear;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			if (g_aParticle[nCntParticle].nLife > 0)
			{
				if (g_aParticle[nCntParticle].nType == 1)
				{
					//�p�[�e�B�N���̐���
					for (nCntAppear = 0; nCntAppear < PUT_PARTICLE1; nCntAppear++)
					{
						//�ړ��ʂ̐ݒ�
						move.x = sinf((float)(rand() % RAND_PAI1 - (RAND_PAI1 - 1) / 2) / 100.0f + D3DX_PI * -0.5f)*(float)((rand() % 100) / 10.0f) + STANDERD_SPEED;
						move.y = cosf((float)(rand() % RAND_PAI1 - (RAND_PAI1 - 1) / 2) / 100.0f + D3DX_PI * -0.5f)*(float)((rand() % 100) / 10.0f) + STANDERD_SPEED;
						move.z = 0.0f;

						//�G�t�F�N�g���Ăяo��
						SetEffect
						(
							g_aParticle[nCntParticle].pos,
							move,
							g_aParticle[nCntParticle].col,
							g_aParticle[nCntParticle].nSize / 2,
							g_aParticle[nCntParticle].nLife
						);
					}
				}
				if (g_aParticle[nCntParticle].nType == 2)
				{
					//�p�[�e�B�N���̐���
					for (nCntAppear = 0; nCntAppear < PUT_PARTICLE2; nCntAppear++)
					{
						//�ړ��ʂ̐ݒ�
						move.x = sinf((float)(rand() % RAND_PAI2 - (RAND_PAI2 - 1) / 2) / 100.0f + D3DX_PI * -0.5f)*(float)((rand() % 100) / 20.0f) + STANDERD_SPEED;
						move.y = cosf((float)(rand() % RAND_PAI2 - (RAND_PAI2 - 1) / 2) / 100.0f + D3DX_PI * -0.5f)*(float)((rand() % 100) / 20.0f) + STANDERD_SPEED;
						move.z = 0.0f;

						//�G�t�F�N�g���Ăяo��
						SetEffect
						(
							g_aParticle[nCntParticle].pos,
							move,
							g_aParticle[nCntParticle].col,
							g_aParticle[nCntParticle].nSize / 2,
							g_aParticle[nCntParticle].nLife
						);
					}
				}

				if (g_aParticle[nCntParticle].nType == 3)
				{
					//�p�[�e�B�N���̐���
					for (nCntAppear = 0; nCntAppear < PUT_PARTICLE3; nCntAppear++)
					{
						//�ړ��ʂ̐ݒ�
						move.x = sinf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 500.0f;
						move.y = cosf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 500.0f;
						move.z = 0.0f;

						//�G�t�F�N�g���Ăяo��
						SetEffect
						(
							g_aParticle[nCntParticle].pos,
							move,
							g_aParticle[nCntParticle].col,
							g_aParticle[nCntParticle].nSize,
							g_aParticle[nCntParticle].nLife
						);
					}
				}

				if (g_aParticle[nCntParticle].nType == 4)
				{
					//�p�[�e�B�N���̐���
					for (nCntAppear = 0; nCntAppear < PUT_PARTICLE3; nCntAppear++)
					{
						//�ړ��ʂ̐ݒ�
						move.x = sinf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 0.5f;
						move.y = cosf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 0.5f;
						move.z = sinf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 0.5f;

						//�G�t�F�N�g���Ăяo��
						SetEffect
						(
							g_aParticle[nCntParticle].pos,
							move,
							g_aParticle[nCntParticle].col,
							g_aParticle[nCntParticle].nSize,
							60
						);
					}
				}

				if (g_aParticle[nCntParticle].nType == 5)
				{
					//�p�[�e�B�N���̐���
					for (nCntAppear = 0; nCntAppear < PUT_PARTICLE5; nCntAppear++)
					{
						//move.x =sinf(g_camera.rot.y) * CAMERA_DISTANCE;
						//3.14 -> 6.28

						//�ړ��ʂ̐ݒ�
						move.x = sinf((float)(rand() % RAND_PAI5 - (RAND_PAI5 - 1) / 2) / 100.0f + D3DX_PI) * 50.0f;
						move.y = 0.0f;
						move.z = cosf((float)(rand() % RAND_PAI5 - (RAND_PAI5 - 1) / 2) / 100.0f + D3DX_PI) * 50.0f;

						D3DXVec3Normalize(&move, &move);	//�x�N�g���𐳋K������

						//�G�t�F�N�g���Ăяo��
						SetEffect
						(
							D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + (move.x * 40.0f), g_aParticle[nCntParticle].pos.y + move.y, g_aParticle[nCntParticle].pos.z + (move.z * 40.0f)),
							D3DXVECTOR3(move.z * 3.0f,1.0f, -move.x * 3.0f),
							g_aParticle[nCntParticle].col,
							g_aParticle[nCntParticle].nSize,
							30
						);
					}
				}

				if (g_aParticle[nCntParticle].nType == 6)
				{
					//�p�[�e�B�N���̐���
					for (nCntAppear = 0; nCntAppear < PUT_PARTICLE6; nCntAppear++)
					{
						//move.x =sinf(g_camera.rot.y) * CAMERA_DISTANCE;
						//3.14 -> 6.28

						//�ړ��ʂ̐ݒ�
						move.x = sinf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 0.5f;
						move.y = cosf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 0.5f;
						move.z = sinf((float)(rand() % RAND_PAI3 - (RAND_PAI3 - 1) / 2) / 100.0f + D3DX_PI) * 0.5f;

						D3DXVec3Normalize(&move, &move);	//�x�N�g���𐳋K������

						move.x *= 5.0f;
						move.y *= 5.0f;
						move.z *= 5.0f;

						//�G�t�F�N�g���Ăяo��
						SetEffect
						(
							g_aParticle[nCntParticle].pos,
							D3DXVECTOR3(move.x, move.y, move.z),
							g_aParticle[nCntParticle].col,
							g_aParticle[nCntParticle].nSize,
							10
						);
					}
				}

				g_aParticle[nCntParticle].nLife--;
				if (g_aParticle[nCntParticle].nLife <= 0)
				{
					g_aParticle[nCntParticle].bUse = false;
				}
			}
		}
	}
}

//====================================================================
//�p�[�e�B�N���̕`�揈��
//====================================================================
void DrawParticle(void)
{

}

//====================================================================
//�p�[�e�B�N���̐ݒ菈��
//====================================================================
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, float nSize, int nType)
{
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle <MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//�p�[�e�B�N�����g�p����Ă��Ȃ�
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].rot = rot;
			g_aParticle[nCntParticle].col = col;
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].nSize = nSize;
			g_aParticle[nCntParticle].nType = nType;

			g_aParticle[nCntParticle].bUse = true;	//�p�[�e�B�N�����g�p���Ă����Ԃɂ���
			break;
		}
	}
}