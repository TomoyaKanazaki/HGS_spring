//============================================================
//
//	�Z�b�g�A�b�v���� [load.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "load.h"
#include "limit.h"

//============================================================
//	�X�e�[�W�̃Z�b�g�A�b�v����
//============================================================
void TxtSetStage(void)
{
	// �ϐ���錾
	int   nEnd;			// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	Limit limit;		// �X�e�[�W�̈ړ��͈͂̑���p

	// �ϐ��z���錾
	char aString[MAX_STRING];	// �e�L�X�g�̕�����̑���p

	// �|�C���^��錾
	FILE *pFile;		// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(STAGE_SETUP_TXT, "r");

	if (pFile != NULL)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			//------------------------------------------------
			//	�ړ��͈͂̐ݒ�
			//------------------------------------------------
			if (strcmp(&aString[0], "STAGE_LIMITSET") == 0)
			{ // �ǂݍ��񂾕����� STAGE_LIMITSET �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_STAGE_LIMITSET �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "NEAR") == 0)
					{ // �ǂݍ��񂾕����� NEAR �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);		// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f", &limit.fNear);		// ��O�̐����ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "FAR") == 0)
					{ // �ǂݍ��񂾕����� FAR �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);		// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f", &limit.fFar);		// ���̐����ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "RIGHT") == 0)
					{ // �ǂݍ��񂾕����� RIGHT �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);		// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f", &limit.fRight);		// �E�̐����ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "LEFT") == 0)
					{ // �ǂݍ��񂾕����� LEFT �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);		// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f", &limit.fLeft);		// ���̐����ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "FIELD") == 0)
					{ // �ǂݍ��񂾕����� FIELD �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);		// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f", &limit.fField);		// �n�ʂ̐����ʒu��ǂݍ���
					}
				} while (strcmp(&aString[0], "END_STAGE_LIMITSET") != 0);	// �ǂݍ��񂾕����� END_STAGE_LIMITSET �ł͂Ȃ��ꍇ���[�v

				// �ړ��͈͂̐ݒ�
				SetLimit(limit);
			}
		} while (nEnd != EOF);	// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v
		
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(NULL, "�X�e�[�W�t�@�C���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}
}