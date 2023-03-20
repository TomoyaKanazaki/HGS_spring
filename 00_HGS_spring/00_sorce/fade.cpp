//==========================================
//
//  �t�F�[�h�̐���(fade.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "fade.h"
#include "polygon.h"

//==========================================
//  �}�N����`
//==========================================
#define FADE_FRAME (30.0f) //�t�F�[�h�ɂ����鎞��

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL; //���_�����i�[
FADE g_fade;
MODE g_NextMode;
D3DXCOLOR g_ColorFade;

//==========================================
//  ����������
//==========================================
void InitFade(MODE nextmode)
{
	//�e��f�[�^�̏�����
	g_fade = FADE_IN;
	g_NextMode = nextmode;
	g_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//���_�o�b�t�@�̐���
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL
	);

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//�@���x�N�g���̐ݒ�
		pVtx[nCnt].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffFade->Unlock();

	//���[�h�̐ݒ�
	SetMode(g_NextMode);
}

//==========================================
//  �I������
//==========================================
void UninitFade(void)
{
	//�|���S���̔j��
	UninitPolygon(&g_pVtxBuffFade);
}

//==========================================
//  �X�V����
//==========================================
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{
		switch (g_fade)
		{
		case FADE_IN:
			//�A���t�@�l�̍X�V
			g_ColorFade.a -= 1.0f / FADE_FRAME;

			//�t�F�[�h�����������ꍇ
			if (g_ColorFade.a <= 0.0f)
			{
				g_ColorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
			break;
		case FADE_OUT:
			//�A���t�@�l�̍X�V
			g_ColorFade.a += 1.0f / FADE_FRAME;

			//�t�F�[�h�����������ꍇ
			if (g_ColorFade.a >= 1.0f)
			{
				g_ColorFade.a = 1.0f;
				g_fade = FADE_IN;

				//���[�h��ݒ�
				SetMode(g_NextMode);
			}
		}
		//���_�o�b�t�@�̌Ăяo��
		VERTEX_2D *pVtx;

		//���_�o�b�t�@�����b�N
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̍X�V
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].col = g_ColorFade;
		}

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffFade->Unlock();
	}
}

//==========================================
//  �`�揈��
//==========================================
void DrawFade(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==========================================
//  �ݒ菈��
//==========================================
void SetFade(MODE nextmode)
{
	//�e��f�[�^�̐ݒ�
	if (g_fade == FADE_NONE)
	{
		g_fade = FADE_OUT;
		g_NextMode = nextmode;
		g_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

//==========================================
//  �t�F�[�h��Ԃ̎擾
//==========================================
FADE GetFade(void)
{
	return g_fade;
}
