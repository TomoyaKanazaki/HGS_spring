//==========================================
//
//  �^�C���̐���(time.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "time.h"
#include "polygon.h"
#include "texture.h"
#include "debugproc.h"
#include "pause.h"

#include "input.h"

//==========================================
//  �}�N����`
//==========================================
#define TIME_DIGIT (3) //����
#define START_TIME (60) //�Q�[������ (1/1�b)
#define TIME_SIZE (100.0f) //�^�C���|���S���̃T�C�Y
#define TIME_POS (D3DXVECTOR3((float)SCREEN_WIDTH - 10.0f, TIME_SIZE, 0.0f)) //�^�C���̕`��ʒu

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void CalcPauseTime(int nCurrentTime); //�|�[�Y���̎��Ԃ�␳����
void SetTimePolygon(void); //�|���S���𐧌䂷��֐�

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;
int g_nTime; //�c�莞�� (1/1�b)
int g_nBaseTime; //����� (1/1000�b)

//==========================================
//  ����������
//==========================================
void InitTime()
{
	//�ϐ��̏�����
	g_nTime = START_TIME;
	g_nBaseTime = timeGetTime();

	//�|���S���̐���
	g_pVtxBuffTime = Init_2D_Polygon(TIME_DIGIT);
}

//==========================================
//  �I������
//==========================================
void UninitTime()
{
	//�|���S���̔j��
	UninitPolygon(&g_pVtxBuffTime);
}

//==========================================
//  �X�V����
//==========================================
void UpdateTime()
{
	//���[�J���ϐ��錾
	int nCurrentTime = timeGetTime(); //���ݎ��Ԃ̎擾 (1/1000�b)
	int nBetweenTime = 0; //����Ԃƌ��ݎ��Ԃ̍� (1/1�b)

	//�|�[�Y���Ԃ̕␳
	CalcPauseTime(nCurrentTime);

	//����Ԃƌ��ݎ��Ԃ̍����擾 (1/1�b)
	nBetweenTime = (nCurrentTime - g_nBaseTime) / 1000;

	//�c�莞�Ԃ̍X�V
	if (GetPause() == false)
	{
		g_nTime = START_TIME - nBetweenTime;
	}

	//�|���S���̍X�V
	SetTimePolygon();

#ifdef _DEBUG
	//�f�o�b�O�L�[
	if (GetKeyboardTrigger(DIK_T))
	{
		//�ϐ��̏�����
		g_nTime = START_TIME;
		g_nBaseTime = timeGetTime();
	}
	if (GetKeyboardTrigger(DIK_UP))
	{
		g_nBaseTime += 1000;
	}
	if (GetKeyboardTrigger(DIK_DOWN))
	{
		g_nBaseTime -= 1000;
	}
	if (GetKeyboardTrigger(DIK_LEFT))
	{
		g_nBaseTime -= 10000;
	}
	if (GetKeyboardTrigger(DIK_RIGHT))
	{
		g_nBaseTime += 100000;
	}
#endif
	//�f�o�b�O�\��
	PrintDebugProc("�o�ߎ��� ( 1/1000s * 1000s = 1s ) : %d\n", nBetweenTime);
	PrintDebugProc("�c�莞�� ( 1/1000s * 1000s = 1s ) : %d\n", g_nTime);
}

//==========================================
//  �`�揈��
//==========================================
void DrawTime()
{
	//���[�J���ϐ��錾
	int nNumDigit = TIME_DIGIT;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�c�莞�Ԃ���`�悷��|���S������ω�����
	if (g_nTime < 10)
	{
		nNumDigit -= 2;
	}
	else if (g_nTime < 100)
	{
		nNumDigit -= 1;
	}

	for (int nCnt = 0; nCnt < nNumDigit; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, GetTexture(TEXTURE_NUMBER));

		//���j���[���ڂ̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}

//==========================================
//  �|�[�Y���̏���
//==========================================
void CalcPauseTime(int nCurrentTime)
{
	//�ϐ��錾
	static int nPauseStartTime = 0;
	static int nPauseEndTime = 0;
	static int nPauseTime = 0;
	static bool bOldPause = false;

	//�|�[�Y���J���ꂽ�u�Ԃ̎��Ԃ�ۑ�
	if (bOldPause == false && GetPause())
	{
		nPauseStartTime += nCurrentTime;
	}

	//�|�[�Y��������̏���
	if (bOldPause && GetPause() == false)
	{
		//�|�[�Y������ꂽ�u�Ԃ̎��Ԃ�ۑ�
		nPauseEndTime += nCurrentTime;

		//�|�[�Y���J����Ă������Ԃ��Z�o
		nPauseTime = nPauseEndTime - nPauseStartTime;

		//�|�[�Y���J����Ă������ԕ�����Ԃ����Z����
		g_nBaseTime += nPauseTime;
	}

	bOldPause = GetPause();
}

//==========================================
//  �|���S���𐧌䂷��֐�
//==========================================
void SetTimePolygon()
{
	//���[�J���ϐ��錾
	int aTex[TIME_DIGIT];
	int nCntCount, nCalc;

	//�ő吔�̎擾
	nCalc = g_nTime;

	//�e�N�X�`�����W�̌v��
	for (nCntCount = 0; nCntCount < TIME_DIGIT; nCntCount++)
	{
		aTex[nCntCount] = nCalc % 10;
		nCalc /= 10;
	}

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//�ݒ菈��
	for (nCntCount = 0; nCntCount < TIME_DIGIT; nCntCount++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(TIME_POS.x - ((float)(nCntCount + 1.0f) * (TIME_SIZE * 0.6f)), TIME_POS.y - TIME_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(TIME_POS.x - ((float)nCntCount * (TIME_SIZE * 0.6f)), TIME_POS.y - TIME_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(TIME_POS.x - ((float)(nCntCount + 1.0f) * (TIME_SIZE * 0.6f)), TIME_POS.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(TIME_POS.x - ((float)nCntCount * (TIME_SIZE * 0.6f)), TIME_POS.y, 0.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(aTex[nCntCount] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aTex[nCntCount] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aTex[nCntCount] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aTex[nCntCount] * 0.1f) + 0.1f, 1.0f);

		//���_�f�[�^�̃|�C���^��4�i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();
}

//==========================================
//  �c�莞�Ԃ̎擾
//==========================================
int GetTime()
{
	return g_nTime;
}
