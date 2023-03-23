//==========================================
//
//  �^�C�g�����[�h�̐���(title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "title.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//==========================================
//  ����������
//==========================================
void InitTitle()
{




	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM_TITLE);
}

//==========================================
//  �I������
//==========================================
void UninitTitle()
{




	//�T�E���h�̒�~
	StopSound();
}

//==========================================
//  �X�V����
//==========================================
void UpdateTitle()
{
	//�t�F�[�h
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadTrigger(BUTTON_START, 0) == true || GetGamepadTrigger(BUTTON_A, 0) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
	{
		SetFade(MODE_GAME);
	}
}

//==========================================
//  �`�揈��
//==========================================
void DrawTitle()
{

}
