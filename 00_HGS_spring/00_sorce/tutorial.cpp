//==========================================
//
//  �`���[�g���A���̐���(tutorial.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial.h"
#include "input.h"
#include "polygon.h"
#include "texture.h"
#include "fade.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;		//���_�o�b�t�@�ւ̃|�C���^

//==========================================
//  ����������
//==========================================
void InitTutorial()
{
	g_pVtxBuffTutorial = Init_2D_Polygon();

	VERTEX_2D *pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();
}

void UninitTutorial()
{
	UninitPolygon(&g_pVtxBuffTutorial);
}

void UpdateTutorial()
{
	if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadTrigger(BUTTON_START, 0) == true || GetGamepadTrigger(BUTTON_A, 0) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
	{
		SetFade(MODE_GAME);
	}
}

void DrawTutorial()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GetTexture(TEXTURE_TUTORIAL));

	//���j���[���ڂ̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}