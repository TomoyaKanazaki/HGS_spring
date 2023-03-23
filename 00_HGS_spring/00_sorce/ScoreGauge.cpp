#include "main.h"
#include "ScoreGauge.h"
#include "player.h"
#include "game.h"
#include "time.h"

//�}�N����`
#define NUM_SSUI		(4)	//GAMEUI�̎�ސ�

#define POS_YOKO_BG_X		(0.0f)		//�u�悱�v��X���W�̈ʒu
#define POS_YOKO_BG_Y		(0.0f)		//�u�悱�v��Y���W�̈ʒu
#define SIZE_YOKO_BG_X		(1280.0f)	//�u�悱�v�̕�
#define SIZE_YOKO_BG_Y		(10.0f)		//�u�悱�v�̍���

#define POS_TATE_BG_X		(1270.0f)	//�u���āv��X���W�̈ʒu
#define POS_TATE_BG_Y		(0.0f)		//�u���āv��Y���W�̈ʒu
#define SIZE_TATE_BG_X		(10.0f)		//�u���āv�̕�
#define SIZE_TATE_BG_Y		(720.0f)	//�u���āv�̍���

#define GAUGE_SPEED			(10.0f)	//�Q�[�W�̃X�s�[�h

//�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//���W
	float fWidth;		//��
	float fHeight;		//����
	bool bEnd;			//�|���S���������������Ă��邩�ǂ���
	bool bUse;			//�|���S�����g���Ă��邩�ǂ���
}SCOREGAUGE;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureScoreGauge[NUM_SSUI] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreGauge = NULL;		//���_�o�b�t�@�ւ̃|�C���^
SCOREGAUGE g_aSucoreGauge[NUM_SSUI];						//�\����
int g_TimeUpNumber;		//�^�C���I�[�o�[���o�̒i�K�p�ϐ�

//====================================================================
//�X�R�A�Q�[�W�̏���������
//====================================================================
void InitScoreGauge(void)
{
	int nCntSG;
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̏���

	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\sunaarasi.png",
	//	&g_apTextureScoreGauge[0]);

	//�O���[�o���ϐ�������
	g_TimeUpNumber = -1;

	//UI�̕\���ݒ�
	for (int nCntSG = 0; nCntSG < NUM_SSUI; nCntSG++)
	{
		switch (nCntSG)
		{
		case 0:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case 1:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(1270.0f, 0.0f, 0.0f);
			break;
		case 2:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(1280.0f, 710.0f, 0.0f);
			break;
		case 3:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(0.0f, 710.0f, 0.0f);
			break;
		}
		g_aSucoreGauge[nCntSG].fWidth = 10.0f;
		g_aSucoreGauge[nCntSG].fHeight = 10.0f;
		g_aSucoreGauge[nCntSG].bEnd = false;
		g_aSucoreGauge[nCntSG].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScoreGauge,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffScoreGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSG = 0; nCntSG < NUM_SSUI; nCntSG++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x, g_aSucoreGauge[nCntSG].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x + g_aSucoreGauge[nCntSG].fWidth, g_aSucoreGauge[nCntSG].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x, g_aSucoreGauge[nCntSG].pos.y + g_aSucoreGauge[nCntSG].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x + g_aSucoreGauge[nCntSG].fWidth, g_aSucoreGauge[nCntSG].pos.y + g_aSucoreGauge[nCntSG].fHeight, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScoreGauge->Unlock();

	SetScoreGauge();
}

//====================================================================
//�^�C�g���̏I������
//====================================================================
void UninitScoreGauge(void)
{
	int nCntSG;
	for (nCntSG = 0; nCntSG < NUM_SSUI; nCntSG++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureScoreGauge[nCntSG] != NULL)
		{
			g_apTextureScoreGauge[nCntSG]->Release();
			g_apTextureScoreGauge[nCntSG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScoreGauge != NULL)
	{
		g_pVtxBuffScoreGauge->Release();
		g_pVtxBuffScoreGauge = NULL;
	}
}

//====================================================================
//�X�R�A�Q�[�W�̍X�V����
//====================================================================
void UpdateScoreGauge(void)
{
	MODE mode = GetMode();

	if (g_TimeUpNumber != -1)
	{
		switch (g_TimeUpNumber)
		{
		case 0:
			if (g_aSucoreGauge[0].fWidth < SIZE_YOKO_BG_X &&
				g_aSucoreGauge[0].bEnd == false &&
				g_aSucoreGauge[0].bUse == true)
			{
				g_aSucoreGauge[0].fWidth += GAUGE_SPEED;
			}
			else
			{
				g_aSucoreGauge[0].bEnd = true;
				g_aSucoreGauge[1].bUse = true;
				g_TimeUpNumber++;
			}
			break;

		case 1:
			if (g_aSucoreGauge[1].fHeight < SIZE_TATE_BG_Y &&
				g_aSucoreGauge[1].bEnd == false &&
				g_aSucoreGauge[1].bUse == true)
			{
				g_aSucoreGauge[1].fHeight += GAUGE_SPEED;
			}
			else
			{
				g_aSucoreGauge[1].bEnd = true;
				g_aSucoreGauge[2].bUse = true;
				g_TimeUpNumber++;
			}
			break;

		case 2:
			if (g_aSucoreGauge[2].fWidth < SIZE_YOKO_BG_X &&
				g_aSucoreGauge[2].bEnd == false &&
				g_aSucoreGauge[2].bUse == true)
			{
				g_aSucoreGauge[2].pos.x -= GAUGE_SPEED;
				g_aSucoreGauge[2].fWidth += GAUGE_SPEED;
			}
			else
			{
				g_aSucoreGauge[2].bEnd = true;
				g_aSucoreGauge[3].bUse = true;
				g_TimeUpNumber++;
			}
			break;

		case 3:
			if (g_aSucoreGauge[3].fHeight < SIZE_TATE_BG_Y &&
				g_aSucoreGauge[3].bEnd == false &&
				g_aSucoreGauge[3].bUse == true)
			{
				g_aSucoreGauge[3].pos.y -= GAUGE_SPEED;
				g_aSucoreGauge[3].fHeight += GAUGE_SPEED;
			}
			else
			{
				g_aSucoreGauge[3].bEnd = true;
				SetScoreGauge();
			}
		}
	}

		VERTEX_2D*pVtx;	//���_�|�C���^������

		//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
		g_pVtxBuffScoreGauge->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntSG = 0; nCntSG < NUM_SSUI; nCntSG++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x, g_aSucoreGauge[nCntSG].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x + g_aSucoreGauge[nCntSG].fWidth, g_aSucoreGauge[nCntSG].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x, g_aSucoreGauge[nCntSG].pos.y + g_aSucoreGauge[nCntSG].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSucoreGauge[nCntSG].pos.x + g_aSucoreGauge[nCntSG].fWidth, g_aSucoreGauge[nCntSG].pos.y + g_aSucoreGauge[nCntSG].fHeight, 0.0f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffScoreGauge->Unlock();
}

//====================================================================
//�X�R�A�Q�[�W�̕`�揈��
//====================================================================
void DrawScoreGauge(void)
{
	int nCntSG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScoreGauge, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntSG = 0; nCntSG < NUM_SSUI; nCntSG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureScoreGauge[nCntSG]);

		if (g_aSucoreGauge[nCntSG].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntSG,						//�v���~�e�B�u(�|���S��)��
				2);
		}
	}
}

//====================================================================
//�X�R�A�Q�[�W�̐ݒ菈��
//====================================================================
void SetScoreGauge(void)
{
	for (int nCntSG = 0; nCntSG < NUM_SSUI; nCntSG++)
	{
		switch (nCntSG)
		{
		case 0:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case 1:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(1270.0f, 0.0f, 0.0f);
			break;
		case 2:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(1280.0f, 710.0f, 0.0f);
			break;
		case 3:
			g_aSucoreGauge[nCntSG].pos = D3DXVECTOR3(0.0f, 710.0f, 0.0f);
			break;
		}

		g_aSucoreGauge[nCntSG].fWidth = 10.0f;
		g_aSucoreGauge[nCntSG].fHeight = 10.0f;
		g_aSucoreGauge[nCntSG].bEnd = false;
		if (nCntSG == 0)
		{
			g_aSucoreGauge[nCntSG].bUse = true;
		}
		else
		{
			g_aSucoreGauge[nCntSG].bUse = false;
		}
	}
	g_TimeUpNumber = 0;
}