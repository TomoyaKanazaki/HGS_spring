//==========================================
//
//  �v���C���[�̐���(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//==========================================
//  �v���C���[��Ԃ̗񋓒�`
//==========================================
typedef enum
{
	PLAYERSTATE_NORMAL = 0, //�ʏ���
	PLAYERSTATE_MAX
}PLAYERSTATE;

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
D3DXVECTOR3 GetPosPlayer(void);

#endif
