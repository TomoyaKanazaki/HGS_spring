#include "main.h"
#include "PlusScore.h"
#include "texture.h"

//�}�N����`
#define NUM_PLACE (3)				//�v���X�X�R�A�̌���

#define X_POS_GAME (100.0f)			//�Q�[����ʂ̎��̃v���X�X�R�A��X���W
#define Y_POS_GAME (50.0f)			//�Q�[����ʂ̎��̃v���X�X�R�A��Y���W
#define X_SIZE_GAME (20.0f)			//�Q�[����ʂ̎��̃v���X�X�R�A�̉���
#define Y_SIZE_GAME (20.0f)			//�Q�[����ʂ̎��̃v���X�X�R�A�̏c��
#define WIDE_SIZE_GAME (40.0f)		//�Q�[����ʂ̎��̃v���X�X�R�A���m�̕�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlusScore = NULL;			//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlusScore = NULL;		//���_�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_posPlusScore[NUM_PLACE];					//�v���X�X�R�A�̈ʒu
int g_nPlusScore;										//�v���X�X�R�A�̒l

//====================================================================
//�v���X�X�R�A�̏���������
//====================================================================
void InitPlusScore(void)
{
	int nCntPlusScore;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	for (nCntPlusScore = 0; nCntPlusScore < NUM_PLACE; nCntPlusScore++)
	{
		g_posPlusScore[nCntPlusScore] = D3DXVECTOR3(900.0f + nCntPlusScore * WIDE_SIZE_GAME, 50.0f, 0.0f);
	}
	g_nPlusScore = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlusScore,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffPlusScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlusScore = 0; nCntPlusScore < NUM_PLACE; nCntPlusScore++)
	{
		//���_���W�̐ݒ� 
		pVtx[0].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x - X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y - Y_SIZE_GAME, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x + X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y - Y_SIZE_GAME, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x - X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y + Y_SIZE_GAME, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x + X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y + Y_SIZE_GAME, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlusScore->Unlock();
}

//====================================================================
//�v���X�X�R�A�̏I������
//====================================================================
void UninitPlusScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlusScore != NULL)
	{
		g_pTexturePlusScore->Release();
		g_pTexturePlusScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlusScore != NULL)
	{
		g_pVtxBuffPlusScore->Release();
		g_pVtxBuffPlusScore = NULL;
	}
}

//====================================================================
//�v���X�X�R�A�̍X�V����
//====================================================================
void UpdatePlusScore(void)
{
	MODE g_Mode = GetMode();	//�Q�[�����[�h������
	int nCntPlusScore;

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffPlusScore->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_Mode)
	{
	case MODE_GAME:
		for (nCntPlusScore = 0; nCntPlusScore < NUM_PLACE; nCntPlusScore++)
		{
			g_posPlusScore[nCntPlusScore] = D3DXVECTOR3(X_POS_GAME + nCntPlusScore * WIDE_SIZE_GAME, Y_POS_GAME, 0.0f);

			//���_���W�̐ݒ� 
			pVtx[0].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x - X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y - Y_SIZE_GAME, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x + X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y - Y_SIZE_GAME, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x - X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y + Y_SIZE_GAME, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posPlusScore[nCntPlusScore].x + X_SIZE_GAME, g_posPlusScore[nCntPlusScore].y + Y_SIZE_GAME, 0.0f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�

		}
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlusScore->Unlock();
}

//====================================================================
//�v���X�X�R�A�̕`�揈��
//====================================================================
void DrawPlusScore(void)
{
	int nCntPlusScore;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

							   //�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlusScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GetTexture(TEXTURE_NUMBER));

	for (nCntPlusScore = 0; nCntPlusScore < NUM_PLACE; nCntPlusScore++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			4 * nCntPlusScore,							//�v���~�e�B�u(�|���S��)��
			2);
	}
}

//====================================================================
//�v���X�X�R�A�̐ݒ菈��
//====================================================================
void SetPlusScore(int nPlusScore)
{
	int aTexU[NUM_PLACE];
	int nCntPlusScore;

	g_nPlusScore = nPlusScore;

	aTexU[0] = g_nPlusScore % 1000 / 100;
	aTexU[1] = g_nPlusScore % 100 / 10;
	aTexU[2] = g_nPlusScore % 10 / 1;

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffPlusScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlusScore = 0; nCntPlusScore < NUM_PLACE; nCntPlusScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU[nCntPlusScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU[nCntPlusScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU[nCntPlusScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU[nCntPlusScore] * 0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlusScore->Unlock();
}

//====================================================================
//�v���X�X�R�A�̉��Z����
//====================================================================
void AddPlusScore(int nValue)
{
	int aTexU[NUM_PLACE];
	int nCntPlusScore;

	g_nPlusScore += nValue;

	aTexU[0] = g_nPlusScore % 1000 / 100;
	aTexU[1] = g_nPlusScore % 100 / 10;
	aTexU[2] = g_nPlusScore % 10 / 1;

	VERTEX_2D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffPlusScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlusScore = 0; nCntPlusScore < NUM_PLACE; nCntPlusScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU[nCntPlusScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU[nCntPlusScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU[nCntPlusScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU[nCntPlusScore] * 0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlusScore->Unlock();
}

//====================================================================
//�v���X�X�R�A�̏���
//====================================================================
int GetPlusScore(void)
{
	return g_nPlusScore;
}