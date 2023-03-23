//========================================================================================
//
// �����̃e�N�X�`�����Ăяo������[NumberUI.cpp]
// Author: ��{�@�ėB
//
//========================================================================================

#include "main.h"
#include "numberUI.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "camera.h"

//�}�N����`
#define NUMBER_MAX		(128)	//�����̍ő吔
#define NUMBER_NUM		(2)	//�����̎�ސ�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureNumberUI[NUMBER_NUM] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNumberUI = NULL;		//���_�o�b�t�@�ւ̃|�C���^
NumberUI g_NumberUI[NUMBER_MAX];

//====================================================================
//�^�C�g����ʂ̏���������
//====================================================================
void InitNumberUI(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	int nCntNUMBER;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"02_data\\02_TEXTURE\\number.png",
		&g_apTextureNumberUI[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"02_data\\02_TEXTURE\\number.png",
		&g_apTextureNumberUI[1]);

	//�e��ϐ��̏�����
	for (nCntNUMBER = 0; nCntNUMBER < NUMBER_MAX; nCntNUMBER++)
	{
		g_NumberUI[nCntNUMBER].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_NumberUI[nCntNUMBER].nNumberUI = 0;
		g_NumberUI[nCntNUMBER].nType = 0;
		g_NumberUI[nCntNUMBER].Width = 0.0f;
		g_NumberUI[nCntNUMBER].Height = 0.0f;
		g_NumberUI[nCntNUMBER].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUMBER_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffNumberUI,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffNumberUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntNUMBER = 0; nCntNUMBER < NUMBER_MAX; nCntNUMBER++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffNumberUI->Unlock();
}

//====================================================================
//�^�C�g���̏I������
//====================================================================
void UninitNumberUI(void)
{
	////�T�E���h�̒�~
	//StopSound();

	int nCntNUMBER;
	for (nCntNUMBER = 0; nCntNUMBER < NUMBER_NUM; nCntNUMBER++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureNumberUI[nCntNUMBER] != NULL)
		{
			g_apTextureNumberUI[nCntNUMBER]->Release();
			g_apTextureNumberUI[nCntNUMBER] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffNumberUI != NULL)
	{
		g_pVtxBuffNumberUI->Release();
		g_pVtxBuffNumberUI = NULL;
	}
}

//====================================================================
//�^�C�g����ʂ̍X�V����
//====================================================================
void UpdateNumberUI(void)
{
	int nCntNUMBER;

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffNumberUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntNUMBER = 0; nCntNUMBER < NUMBER_MAX; nCntNUMBER++)
	{
		if (g_NumberUI[nCntNUMBER].bUse == true)
		{
			pVtx[0].pos = D3DXVECTOR3(g_NumberUI[nCntNUMBER].pos.x - g_NumberUI[nCntNUMBER].Width, g_NumberUI[nCntNUMBER].pos.y - g_NumberUI[nCntNUMBER].Height, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_NumberUI[nCntNUMBER].pos.x + g_NumberUI[nCntNUMBER].Width, g_NumberUI[nCntNUMBER].pos.y - g_NumberUI[nCntNUMBER].Height, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_NumberUI[nCntNUMBER].pos.x - g_NumberUI[nCntNUMBER].Width, g_NumberUI[nCntNUMBER].pos.y + g_NumberUI[nCntNUMBER].Height, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_NumberUI[nCntNUMBER].pos.x + g_NumberUI[nCntNUMBER].Width, g_NumberUI[nCntNUMBER].pos.y + g_NumberUI[nCntNUMBER].Height, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + g_NumberUI[nCntNUMBER].nNumberUI * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + g_NumberUI[nCntNUMBER].nNumberUI * 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + g_NumberUI[nCntNUMBER].nNumberUI * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + g_NumberUI[nCntNUMBER].nNumberUI * 0.1f, 1.0f);
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffNumberUI->Unlock();
}

//====================================================================
//�^�C�g����ʂ̐ݒ菈��
//====================================================================
void SetNumberUI(D3DXVECTOR3 pos, float SizeX, float SizeY, int NumberUI, int nType)
{
	int nCntNUMBER;

	for (nCntNUMBER = 0; nCntNUMBER < NUMBER_MAX; nCntNUMBER++)
	{
		if (g_NumberUI[nCntNUMBER].bUse == false)
		{
			g_NumberUI[nCntNUMBER].pos = pos;
			g_NumberUI[nCntNUMBER].Width = SizeX;
			g_NumberUI[nCntNUMBER].Height = SizeY;
			g_NumberUI[nCntNUMBER].nNumberUI = NumberUI;
			g_NumberUI[nCntNUMBER].nType = nType;
			g_NumberUI[nCntNUMBER].bUse = true;
			break;
		}
	}
}

//====================================================================
//�^�C�g����ʂ̕`�揈��
//====================================================================
void DrawNumberUI(void)
{
	int nCntNUMBER;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffNumberUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntNUMBER = 0; nCntNUMBER < NUMBER_MAX; nCntNUMBER++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureNumberUI[g_NumberUI[nCntNUMBER].nType]);

		if (g_NumberUI[nCntNUMBER].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntNUMBER,						//�v���~�e�B�u(�|���S��)��
				2);
		}
	}
}