#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,			// �^�C�g��
	SOUND_LABEL_BGM_RANKING,			// �����L���O
	SOUND_LABEL_BGM_GAME_01,			// �Q�[��01
	SOUND_LABEL_BGM_GAME_02,			// �Q�[��02
	SOUND_LABEL_BGM_GAME_03,			// �Q�[��03
	SOUND_LABEL_SE_KEY_MOVE,			// �ړ�
	SOUND_LABEL_SE_KEY_PUSH,			// ����
	SOUND_LABEL_SE_PLAYER_JUMP,			// �W�����v
	SOUND_LABEL_SE_PLAYER_DAMAGE,		// �_���[�W
	SOUND_LABEL_SE_TIME_NORMAL,			// ����
	SOUND_LABEL_SE_TIME_HURRY,			// ����
	SOUND_LABEL_SE_DAMAGEWAVE,			// �_���[�W�E�F�[�u
	SOUND_LABEL_SE_SLIME_JUMP,			// �W�����v
	SOUND_LABEL_SE_CANNON_BULLET,		// ��C�̒e
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
