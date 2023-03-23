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
#define TIME_NUM (3) //����
#define START_TIME (120) //�Q�[������ (1/1�b)

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void CalcPauseTime(int nCurrentTime); //�|�[�Y���̎��Ԃ�␳����

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
	g_pVtxBuffTime = Init_2D_Polygon(TIME_NUM);
}

//==========================================
//  �I������
//==========================================
void UninitTime()
{

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

#ifdef _DEBUG
	//�f�o�b�O�L�[
	if (GetKeyboardTrigger(DIK_T))
	{
		//�ϐ��̏�����
		g_nTime = START_TIME;
		g_nBaseTime = timeGetTime();
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
