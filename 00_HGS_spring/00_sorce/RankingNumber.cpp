#include "main.h"
#include "rankingnumber.h"
#include "NumberUI.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include <stdio.h>

//�}�N����`
#define MAX_RANK (5)			//�����N�̐�
#define NUM_PLACE (3)			//�����L���O�̌���

#define X_POS_GAME (800.0f)			//�Q�[����ʂ̎��̃����L���O��X���W
#define Y_POS_GAME (250.0f)			//�Q�[����ʂ̎��̃����L���O��Y���W
#define X_SIZE_GAME (40.0f)			//�Q�[����ʂ̎��̃����L���O�̉���
#define Y_SIZE_GAME (40.0f)			//�Q�[����ʂ̎��̃����L���O�̏c��
#define WIDE_SIZE_GAME_X (75.0f)	//�Q�[����ʂ̎��̃����L���O���m�̕�
#define WIDE_SIZE_GAME_Y (100.0f)	//�Q�[����ʂ̎��̃����L���O���m�̍���

//�����L���O�\����
typedef struct
{
	D3DXVECTOR3 pos;
	int nScore;
}RanKingNumber;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRanKingNumber = NULL;			//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanKingNumber = NULL;		//���_�o�b�t�@�̃|�C���^
RanKingNumber g_RanKingNumber[MAX_RANK];					//�����L���O�̈ʒu

int g_HighScore = -1;
int g_RankingCounter;
float g_RankingColorR = 1.0f;
float g_RankingColorG = 0.0f;
float g_RankingAR = 0.05f;
float g_RankingAG = -0.05f;
//====================================================================
//�����L���O�̏���������
//====================================================================
void InitRanKingNumber(void)
{
	int aTexU[NUM_PLACE];
	int nCntMax;
	int nCntNum;
	g_RankingCounter = 1200;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"02_data\\02_TEXTURE\\number.png",
		&g_pTextureRanKingNumber);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanKingNumber,
		NULL);

	g_RankingColorR = 0.5f;
	g_RankingColorG = 0.5f;
	g_RankingAR = 0.025f;
	g_RankingAG = -0.025f;

	SetNumberUI(D3DXVECTOR3(0.0f, 0.0f, 0.0f), X_SIZE_GAME, Y_SIZE_GAME, GetScore() % 1000 / 100, 0);
	SetNumberUI(D3DXVECTOR3(0.0f, 0.0f, 0.0f), X_SIZE_GAME, Y_SIZE_GAME, GetScore() % 100 / 10, 0);
	SetNumberUI(D3DXVECTOR3(0.0f,0.0f,0.0f), X_SIZE_GAME, Y_SIZE_GAME, GetScore() % 10 / 1, 0);

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffRanKingNumber->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMax = 0; nCntMax < MAX_RANK; nCntMax++)
	{
		aTexU[0] = g_RanKingNumber[nCntMax].nScore % 1000 / 100;
		aTexU[1] = g_RanKingNumber[nCntMax].nScore % 100 / 10;
		aTexU[2] = g_RanKingNumber[nCntMax].nScore % 10 / 1;

		for (nCntNum = 0; nCntNum < NUM_PLACE; nCntNum++)
		{
			g_RanKingNumber[nCntMax].pos = D3DXVECTOR3(X_POS_GAME + nCntNum * WIDE_SIZE_GAME_X, Y_POS_GAME + nCntMax * WIDE_SIZE_GAME_Y, 0.0f);

			//���_���W�̐ݒ� 
			pVtx[0].pos = D3DXVECTOR3(g_RanKingNumber[nCntMax].pos.x - X_SIZE_GAME, g_RanKingNumber[nCntMax].pos.y - Y_SIZE_GAME, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_RanKingNumber[nCntMax].pos.x + X_SIZE_GAME, g_RanKingNumber[nCntMax].pos.y - Y_SIZE_GAME, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_RanKingNumber[nCntMax].pos.x - X_SIZE_GAME, g_RanKingNumber[nCntMax].pos.y + Y_SIZE_GAME, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_RanKingNumber[nCntMax].pos.x + X_SIZE_GAME, g_RanKingNumber[nCntMax].pos.y + Y_SIZE_GAME, 0.0f);

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU[nCntNum] * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU[nCntNum] * 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU[nCntNum] * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU[nCntNum] * 0.1f, 1.0f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanKingNumber->Unlock();
}

//====================================================================
//�����L���O�̏I������
//====================================================================
void UninitRanKingNumber(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRanKingNumber != NULL)
	{
		g_pTextureRanKingNumber->Release();
		g_pTextureRanKingNumber = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRanKingNumber != NULL)
	{
		g_pVtxBuffRanKingNumber->Release();
		g_pVtxBuffRanKingNumber = NULL;
	}
	g_HighScore = -1;
}

//====================================================================
//�����L���O�̍X�V����
//====================================================================
void UpdateRanKingNumber(void)
{
	int nCount1;
	int nCntNum;
	MODE g_Mode = GetMode();	//�Q�[�����[�h������

	if (g_RankingCounter != -1)
	{
		g_RankingCounter--;
	}

	g_RankingColorR += g_RankingAR;
	g_RankingColorG += g_RankingAG;

	if (g_RankingColorR > 1.0f)
	{
		g_RankingColorR = 1.0f;
		g_RankingAR *= -1;
	}
	else if (g_RankingColorR < 0.0f)
	{
		g_RankingColorR = 0.0f;
		g_RankingAR *= -1;
	}

	if (g_RankingColorG > 1.0f)
	{
		g_RankingColorG = 1.0f;
		g_RankingAG *= -1;
	}
	else if (g_RankingColorG < 0.0f)
	{
		g_RankingColorG = 0.0f;
		g_RankingAG *= -1;
	}

	//��
	if (GetFade() == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadTrigger(BUTTON_START, 0) == true || GetGamepadTrigger(BUTTON_A, 0) == true || GetGamepadTrigger(BUTTON_B, 0) == true || g_RankingCounter == 0)
		{//ENTER�L�[�������ꂽ

			g_RankingCounter = -1;

			//�f�[�^���Z�[�u����
			SaveData();

			//�t�F�[�h�̏�Ԃ�ς���
			SetFade(MODE_TITLE);
		}
	}

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffRanKingNumber->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount1 = 0; nCount1 < MAX_RANK; nCount1++)
	{
		for (nCntNum = 0; nCntNum < NUM_PLACE; nCntNum++)
		{
			if (g_HighScore == g_RanKingNumber[nCount1].nScore)
			{//�����L���O�X�V���F��ύX����
			 //���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, g_RankingColorR, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, g_RankingColorR, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, g_RankingColorR, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, g_RankingColorR, 1.0f);

				//�����L���O�̒l�������̎��O��̏�̏��ʂ̐F�����ɖ߂�
				if (nCount1 != 0)
				{
					pVtx -= 4 * NUM_PLACE;	//���_�f�[�^�̃|�C���^���S���i�߂�

											//���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					pVtx += 4 * NUM_PLACE;	//���_�f�[�^�̃|�C���^���S���i�߂�
				}
			}
			pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanKingNumber->Unlock();
}

//====================================================================
//�����L���O�̕`�揈��
//====================================================================
void DrawRanKingNumber(void)
{
	int nCntMax;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanKingNumber, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanKingNumber);
	for (nCntMax = 0; nCntMax < NUM_PLACE * MAX_RANK; nCntMax++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			4 * nCntMax,							//�v���~�e�B�u(�|���S��)��
			2);
	}
}

//====================================================================
//�����L���O�̐ݒ菈��
//====================================================================
void SetRanking(int nRanKing)
{
	int nCount1;
	int nCount2;
	int nData;

	if (nRanKing > g_RanKingNumber[MAX_RANK - 1].nScore)
	{
		g_RanKingNumber[MAX_RANK - 1].nScore = nRanKing;
		g_HighScore = nRanKing;

		for (nCount1 = 0; nCount1 < MAX_RANK; nCount1++)
		{
			for (nCount2 = nCount1; nCount2 < MAX_RANK; nCount2++)
			{
				if (g_RanKingNumber[nCount1].nScore < g_RanKingNumber[nCount2].nScore)
				{
					nData = g_RanKingNumber[nCount1].nScore;
					g_RanKingNumber[nCount1].nScore = g_RanKingNumber[nCount2].nScore;
					g_RanKingNumber[nCount2].nScore = nData;
				}
			}
		}
	}
}

//====================================================================
//�����L���O��ʂ̃��Z�b�g����
//====================================================================
void ResetRanKing(void)
{
	int nCntNum;

	for (nCntNum = 0; nCntNum < MAX_RANK; nCntNum++)
	{
		g_RanKingNumber[nCntNum].nScore = 0;
	}
}

//==================================================
//�Z�[�u����
//==================================================
void SaveData(void)
{
	int nCount;
	FILE *pFile; //�t�@�C���|�C���^��錾

				 //�t�@�C�����J��
	pFile = fopen("data\\TEXT\\ranking.txt", "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		for (nCount = 0; nCount < MAX_RANK; nCount++)
		{
			fprintf(pFile, "%d\n", g_RanKingNumber[nCount].nScore);		 //&(�A���p�T���h)��t���Ȃ��I
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}

//==================================================
//���[�h����
//==================================================
void LordData(void)
{
	int nCount;
	FILE *pFile; //�t�@�C���|�C���^��錾

				 //�t�@�C�����J��
	pFile = fopen("data\\TEXT\\ranking.txt", "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
	 //�t�@�C�����當����ǂݍ���

		for (nCount = 0; nCount < MAX_RANK; nCount++)
		{
			fscanf(pFile, "%d", &g_RanKingNumber[nCount].nScore);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}

//==================================================
//�����L���O�X�^�[�g����
//==================================================
void StartRanKing(void)
{
	g_HighScore = -1;
}