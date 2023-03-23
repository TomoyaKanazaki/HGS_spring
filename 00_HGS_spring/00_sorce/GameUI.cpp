#include "main.h"
#include "GameUI.h"
#include "numberUI.h"
#include "player.h"
#include "game.h"
#include "time.h"

//�}�N����`
#define NUM_SSUI		(5)	//GAMEUI�̎�ސ�

#define POS_GAME_BG_X		(640.0f)	//�u�v��X���W�̈ʒu
#define POS_GAME_BG_Y		(360.0f)	//�u�v��Y���W�̈ʒu
#define SIZE_GAME_BG_X		(640.0f)	//�u�v�̕�
#define SIZE_GAME_BG_Y		(360.0f)	//�u�v�̍���

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
LPDIRECT3DTEXTURE9 g_apTextureGameUI[NUM_SSUI] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameUI = NULL;		//���_�o�b�t�@�ւ̃|�C���^
bool bUseGameUI[NUM_SSUI];		//���_�o�b�t�@�ւ̃|�C���^
bool g_bStageClear_Game;

//====================================================================
//�^�C�g����ʂ̏���������
//====================================================================
void InitGameUI(void)
{
	int nCntBG;
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̏���

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAME\\Osumi00.png",
		&g_apTextureGameUI[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAME\\pepepepe02.png",
		&g_apTextureGameUI[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAME\\RankUi.png",
		&g_apTextureGameUI[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAME\\pepepepe01.png",
		&g_apTextureGameUI[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAME\\pepepepe03.png",
		&g_apTextureGameUI[4]);

	//UI�̕\���ݒ�
	bUseGameUI[0] = false;
	bUseGameUI[1] = false;
	bUseGameUI[2] = false;
	bUseGameUI[3] = false;
	bUseGameUI[4] = false;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SSUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameUI,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		switch (nCntBG)
		{
		case 0:
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(POS_GAME_BG_X - SIZE_GAME_BG_X, POS_GAME_BG_Y - SIZE_GAME_BG_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POS_GAME_BG_X + SIZE_GAME_BG_X, POS_GAME_BG_Y - SIZE_GAME_BG_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POS_GAME_BG_X - SIZE_GAME_BG_X, POS_GAME_BG_Y + SIZE_GAME_BG_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POS_GAME_BG_X + SIZE_GAME_BG_X, POS_GAME_BG_Y + SIZE_GAME_BG_Y, 0.0f);
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
	g_pVtxBuffGameUI->Unlock();
}

//====================================================================
//�^�C�g���̏I������
//====================================================================
void UninitGameUI(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureGameUI[nCntBG] != NULL)
		{
			g_apTextureGameUI[nCntBG]->Release();
			g_apTextureGameUI[nCntBG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGameUI != NULL)
	{
		g_pVtxBuffGameUI->Release();
		g_pVtxBuffGameUI = NULL;
	}
}

//====================================================================
//�^�C�g����ʂ̍X�V����
//====================================================================
void UpdateGameUI(void)
{

}

//====================================================================
//�^�C�g����ʂ̕`�揈��
//====================================================================
void DrawGameUI(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGameUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_SSUI; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureGameUI[nCntBG]);

		if (bUseGameUI[nCntBG] == true)
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
void SetGameUI(GAME SetClear, bool Clear)
{

}