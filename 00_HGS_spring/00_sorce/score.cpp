#include "main.h"
#include "score.h"

//�}�N����`
#define NUM_PLACE (3)				//�X�R�A�̌���

#define X_POS_GAME (100.0f)			//�Q�[����ʂ̎��̃X�R�A��X���W
#define Y_POS_GAME (100.0f)			//�Q�[����ʂ̎��̃X�R�A��Y���W
#define X_SIZE_GAME (25.0f)			//�Q�[����ʂ̎��̃X�R�A�̉���
#define Y_SIZE_GAME (25.0f)			//�Q�[����ʂ̎��̃X�R�A�̏c��
#define WIDE_SIZE_GAME (100.0f)		//�Q�[����ʂ̎��̃X�R�A���m�̕�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//���_�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_posScore[NUM_PLACE];					//�X�R�A�̈ʒu
int g_nScore;										//�X�R�A�̒l

//====================================================================
//�X�R�A�̏���������
//====================================================================
void InitScore(void)
{
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\NUMBER002.png",
	//	&g_pTextureScore);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		g_posScore[nCntScore] = D3DXVECTOR3(900.0f + nCntScore * WIDE_SIZE_GAME, 50.0f, 0.0f);
	}
	g_nScore = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//���_���W�̐ݒ� 
		pVtx[0].pos = D3DXVECTOR3(g_posScore[nCntScore].x - X_SIZE_GAME , g_posScore[nCntScore].y - Y_SIZE_GAME, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore[nCntScore].x + X_SIZE_GAME , g_posScore[nCntScore].y - Y_SIZE_GAME, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore[nCntScore].x - X_SIZE_GAME , g_posScore[nCntScore].y + Y_SIZE_GAME, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore[nCntScore].x + X_SIZE_GAME , g_posScore[nCntScore].y + Y_SIZE_GAME, 0.0f);

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
	g_pVtxBuffScore->Unlock();
}

//====================================================================
//�X�R�A�̏I������
//====================================================================
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//====================================================================
//�X�R�A�̍X�V����
//====================================================================
void UpdateScore(void)
{
	MODE g_Mode = GetMode();	//�Q�[�����[�h������
	int nCntScore;

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_Mode)
	{
	case MODE_GAME:
		for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
		{
			g_posScore[nCntScore] = D3DXVECTOR3(X_POS_GAME + nCntScore * WIDE_SIZE_GAME, Y_POS_GAME, 0.0f);

			//���_���W�̐ݒ� 
			pVtx[0].pos = D3DXVECTOR3(g_posScore[nCntScore].x - X_SIZE_GAME, g_posScore[nCntScore].y - Y_SIZE_GAME, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posScore[nCntScore].x + X_SIZE_GAME, g_posScore[nCntScore].y - Y_SIZE_GAME, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posScore[nCntScore].x - X_SIZE_GAME, g_posScore[nCntScore].y + Y_SIZE_GAME, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posScore[nCntScore].x + X_SIZE_GAME, g_posScore[nCntScore].y + Y_SIZE_GAME, 0.0f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�

		}
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//====================================================================
//�X�R�A�̕`�揈��
//====================================================================
void DrawScore(void)
{
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);
	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			4 * nCntScore,							//�v���~�e�B�u(�|���S��)��
			2);
	}
}

//====================================================================
//�X�R�A�̐ݒ菈��
//====================================================================
void SetScore(int nScore)
{
	int aTexU[NUM_PLACE];
	int nCntScore;

	g_nScore = nScore;

	aTexU[0] = g_nScore % 1000 / 100;
	aTexU[1] = g_nScore % 100 / 10;
	aTexU[2] = g_nScore % 10 / 1;

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU[nCntScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU[nCntScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU[nCntScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU[nCntScore] * 0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//====================================================================
//�X�R�A�̉��Z����
//====================================================================
void AddScore(int nValue)
{
	int aTexU[NUM_PLACE];
	int nCntScore;

	g_nScore += nValue;

	aTexU[0] = g_nScore % 1000 / 100;
	aTexU[1] = g_nScore % 100 / 10;
	aTexU[2] = g_nScore % 10 / 1;

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + aTexU[nCntScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aTexU[nCntScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aTexU[nCntScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aTexU[nCntScore] * 0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//====================================================================
//�X�R�A�̏���
//====================================================================
int GetScore(void)
{
	return g_nScore;
}