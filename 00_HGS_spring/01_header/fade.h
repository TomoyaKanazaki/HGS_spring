//==========================================
//
//  �t�F�[�h�̐���(fade.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"

//==========================================
//  �t�F�[�h��Ԃ̗񋓒�`
//==========================================
typedef enum
{
	FADE_NONE = 0, //�t�F�[�h���Ă��Ȃ����
	FADE_IN, //�t�F�[�h�C�����
	FADE_OUT, //�t�F�[�h�A�E�g���
	FADE_MAX
}FADE;

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void InitFade(MODE nextmode);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE nextmode);
FADE GetFade(void);

#endif
