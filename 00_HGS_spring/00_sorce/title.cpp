//==========================================
//
//  �^�C�g�����[�h�̐���(title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "title.h"
#include "fade.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "area.h"
#include "player.h"
#include "sound.h"

//==========================================
//  �^�C�g���\���̂̒�`
//==========================================
typedef struct
{
	D3DXVECTOR3 pos;  //���S���W
	D3DXCOLOR col;    //�F
	float fWidth;		//��
	float fHeight;		//����
}TITLE;

//==========================================
//  �}�N����`
//==========================================
#define FWIDTH  (700) //��
#define FHEIGHT (400) //����
#define MAX_TEX (2)   //�e�N�X�`���̍ő吔

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 g_apTextureTitle[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//���_�o�b�t�@�ւ̃|�C���^

TITLE g_aTitle[MAX_TEX];
int g_nCntCol;

//==========================================
//  ����������
//==========================================
void InitTitle()
{
	InitTitleCamera();

	// ���C�g�̏�����
	InitLight();

	// ���̏�����
	InitArea();

	// ���b�V���t�B�[���h�̏�����
	InitMeshField();

	InitPlayer();

	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̏���

											 //������
	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		g_aTitle[nCntTex].pos = D3DXVECTOR3(250.0f, -500.0f, 0.0f);
		g_aTitle[nCntTex].fWidth = 0.0f;
		g_aTitle[nCntTex].fHeight = 0.0f;
	}

	g_aTitle[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aTitle[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"02_data\\02_TEXTURE\\escape.png",
		&g_apTextureTitle[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"02_data\\02_TEXTURE\\start.png",
		&g_apTextureTitle[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x, g_aTitle[nCntTex].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x + FWIDTH, g_aTitle[nCntTex].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x, g_aTitle[nCntTex].pos.y + FHEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x + FWIDTH, g_aTitle[nCntTex].pos.y + FHEIGHT, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	g_nCntCol = 0;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();



	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM_TITLE);
}

//==========================================
//  �I������
//==========================================
void UninitTitle()
{
	// ���̏�����
	UninitArea();

	// ���b�V���t�B�[���h�̏�����
	UninitMeshField();

	UninitPlayer();

	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureTitle[nCntTex] != NULL)
		{
			g_apTextureTitle[nCntTex]->Release();
			g_apTextureTitle[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}



	//�T�E���h�̒�~
	StopSound();
}

//==========================================
//  �X�V����
//==========================================
void UpdateTitle()
{
	UpdateTitleCamera();

	// ���̏�����
	UpdateArea();

	// ���b�V���t�B�[���h�̏�����
	UpdateMeshField();

	UpdatePlayer();


	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (nCntTex == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x, g_aTitle[nCntTex].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x + FWIDTH, g_aTitle[nCntTex].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x, g_aTitle[nCntTex].pos.y + FHEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x + FWIDTH, g_aTitle[nCntTex].pos.y + FHEIGHT, 0.0f);
		}

		if (nCntTex == 1)
		{
			g_aTitle[nCntTex].pos = D3DXVECTOR3(100.0f, 500.0f, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x, g_aTitle[nCntTex].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x + 500.0f, g_aTitle[nCntTex].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x, g_aTitle[nCntTex].pos.y + 200.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTex].pos.x + 500.0f, g_aTitle[nCntTex].pos.y + 200.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTitle[nCntTex].col.a);
		}

		float fDest = 160.0f;
		float fDiff = fDest - g_aTitle[nCntTex].pos.y;
		g_aTitle[nCntTex].pos.y += fDest * 0.05f;

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	if (g_aTitle[0].pos.y >= 30.0f)
	{//�^�C�g���̈ʒu��160�ȏゾ������

		g_aTitle[0].pos.y = 30.0f;

		g_nCntCol++;

		if (g_nCntCol >= 100)
		{//�J�E���g��100�ȉ���������

			g_aTitle[1].col.a -= 0.01f;
		}

		if (g_nCntCol <= 100)
		{//�J�E���g��100�ȏゾ������

			g_aTitle[1].col.a += 0.01f;
		}

		if (g_nCntCol >= 200)
		{//�J�E���g��200�ȏゾ������

			g_nCntCol = 0;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	//�t�F�[�h
	if (GetKeyboardTrigger(DIK_RETURN) || GetGamepadTrigger(BUTTON_START, 0) == true || GetGamepadTrigger(BUTTON_A, 0) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
	{
		SetFade(MODE_GAME);
	}
}

//==========================================
//  �`�揈��
//==========================================
void DrawTitle()
{
	// �J�����̐ݒ�
	SetCamera(CAMERATYPE_TITLE);

	// ���̏�����
	DrawArea();

	// ���b�V���t�B�[���h�̏�����
	DrawMeshField();

	DrawPlayer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureTitle[nCntTex]);

		//���j���[���ڂ̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
	}

}