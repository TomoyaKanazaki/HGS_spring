#include "main.h"
#include "RankingUI.h"
#include "numberUI.h"
#include "player.h"
#include "game.h"
#include "time.h"

//�}�N����`
#define NUM_SSUI		(5)	//GAMEUI�̎�ސ�

#define POS_RANKING_BG_X		(640.0f)	//�u�v��X���W�̈ʒu
#define POS_RANKING_BG_Y		(360.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_RANKING_BG_X		(640.0f)	//�u�v�̕�
#define SIZE_RANKING_BG_Y		(360.0f)	//�u�v�̍���

#define POS_SCORE_BG_X			(875.0f)	//�u�v��X���W�̈ʒu
#define POS_SCORE_BG_Y			(495.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_SCORE_BG_X			(340.0f)	//�u�v�̕�
#define SIZE_SCORE_BG_Y			(400.0f)	//�u�v�̍���

#define POS_PERFECT_BG_X		(680.0f)	//�u�v��X���W�̈ʒu
#define POS_PERFECT_BG_Y		(430.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_PERFECT_BG_X		(115.0f)	//�u�v�̕�
#define SIZE_PERFECT_BG_Y		(250.0f)		//�u�v�̍���

#define POS_ALLPERFECT_BG_X		(250.0f)	//�u�v��X���W�̈ʒu
#define POS_ALLPERFECT_BG_Y		(200.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_ALLPERFECT_BG_X	(200.0f)	//�u�v�̕�
#define SIZE_ALLPERFECT_BG_Y	(100.0f)	//�u�v�̍���

#define POS_EXIT_BG_X			(250.0f)	//�u�v��X���W�̈ʒu
#define POS_EXIT_BG_Y			(450.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_EXIT_BG_X			(200.0f)	//�u�v�̕�
#define SIZE_EXIT_BG_Y			(100.0f)	//�u�v�̍���

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureRankingUI[NUM_SSUI] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingUI = NULL;		//���_�o�b�t�@�ւ̃|�C���^
bool bUseRankingUI[NUM_SSUI];		//���_�o�b�t�@�ւ̃|�C���^
bool g_bStageClear_Ranking;

//====================================================================
//�^�C�g����ʂ̏���������
//====================================================================
void InitRankingUI(void)
{
	int nCntBG;
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̏���

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\Osumi00.png",
		&g_apTextureRankingUI[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\pepepepe02.png",
		&g_apTextureRankingUI[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\RankUi.png",
		&g_apTextureRankingUI[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\pepepepe01.png",
		&g_apTextureRankingUI[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RANKING\\pepepepe03.png",
		&g_apTextureRankingUI[4]);

	//UI�̕\���ݒ�
	bUseRankingUI[0] = false;
	bUseRankingUI[1] = false;
	bUseRankingUI[2] = false;
	bUseRankingUI[3] = false;
	bUseRankingUI[4] = false;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingUI,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffRankingUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_RANKING_BG_X - SIZE_RANKING_BG_X, POS_RANKING_BG_Y - SIZE_RANKING_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_RANKING_BG_X + SIZE_RANKING_BG_X, POS_RANKING_BG_Y - SIZE_RANKING_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_RANKING_BG_X - SIZE_RANKING_BG_X, POS_RANKING_BG_Y + SIZE_RANKING_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_RANKING_BG_X + SIZE_RANKING_BG_X, POS_RANKING_BG_Y + SIZE_RANKING_BG_Y, 0.0f);
			break;

		case 1:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_SCORE_BG_X - SIZE_SCORE_BG_X, POS_SCORE_BG_Y - SIZE_SCORE_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_SCORE_BG_X + SIZE_SCORE_BG_X, POS_SCORE_BG_Y - SIZE_SCORE_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_SCORE_BG_X - SIZE_SCORE_BG_X, POS_SCORE_BG_Y + SIZE_SCORE_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_SCORE_BG_X + SIZE_SCORE_BG_X, POS_SCORE_BG_Y + SIZE_SCORE_BG_Y, 0.0f);
			break;

		case 2:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_PERFECT_BG_X - SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y - SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_PERFECT_BG_X + SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y - SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_PERFECT_BG_X - SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y + SIZE_PERFECT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_PERFECT_BG_X + SIZE_PERFECT_BG_X, POS_PERFECT_BG_Y + SIZE_PERFECT_BG_Y, 0.0f);
			break;

		case 3:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X - SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y - SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X + SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y - SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X - SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y + SIZE_ALLPERFECT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_ALLPERFECT_BG_X + SIZE_ALLPERFECT_BG_X, POS_ALLPERFECT_BG_Y + SIZE_ALLPERFECT_BG_Y, 0.0f);
			break;

		case 4:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_EXIT_BG_X - SIZE_EXIT_BG_X, POS_EXIT_BG_Y - SIZE_EXIT_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_EXIT_BG_X + SIZE_EXIT_BG_X, POS_EXIT_BG_Y - SIZE_EXIT_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_EXIT_BG_X - SIZE_EXIT_BG_X, POS_EXIT_BG_Y + SIZE_EXIT_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_EXIT_BG_X + SIZE_EXIT_BG_X, POS_EXIT_BG_Y + SIZE_EXIT_BG_Y, 0.0f);
			break;
		}

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
	g_pVtxBuffRankingUI->Unlock();
}

//====================================================================
//�^�C�g���̏I������
//====================================================================
void UninitRankingUI(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureRankingUI[nCntBG] != NULL)
		{
			g_apTextureRankingUI[nCntBG]->Release();
			g_apTextureRankingUI[nCntBG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRankingUI != NULL)
	{
		g_pVtxBuffRankingUI->Release();
		g_pVtxBuffRankingUI = NULL;
	}
}

//====================================================================
//�^�C�g����ʂ̍X�V����
//====================================================================
void UpdateRankingUI(void)
{

}

//====================================================================
//�^�C�g����ʂ̕`�揈��
//====================================================================
void DrawRankingUI(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankingUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureRankingUI[nCntBG]);

		if (bUseRankingUI[nCntBG] == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntBG,						//�v���~�e�B�u(�|���S��)��
				2);
		}
	}
}
//====================================================================
//�����L���OUI�̐ݒ菈��
//====================================================================
void SetRankingUI(RANKING SetClear, bool Clear)
{

}