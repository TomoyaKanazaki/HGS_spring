#include "main.h"
#include "Bullet.h"
#include "effect.h"
#include "player.h"

#define BULLET_SIZE (5.0f)	//�e�̑傫��
#define BULLET_SPEED (10.0f)	//�e�̑���
#define EFFECT_COUNTER (1)	//�G�t�F�N�g���Z�b�g����Ԋu

//�v���g�^�C�v�錾

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet;				//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet;		//���_�o�b�t�@�̃|�C���^
Bullet g_aBullet[MAX_BULLET];

//====================================================================
//�r���{�[�h�̏���������
//====================================================================
void InitBullet(void)
{
	int nCntBill;
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BOSS00.png",
		&g_pTextureBullet);

	for (nCntBill = 0; nCntBill < MAX_BULLET; nCntBill++)
	{
		g_aBullet[nCntBill].pos = D3DXVECTOR3(90.0f, 10.0f, 50.0f);
		g_aBullet[nCntBill].posOld = g_aBullet[nCntBill].pos;
		g_aBullet[nCntBill].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBill].bUse = false;
		g_aBullet[nCntBill].nIndex = -1;
		g_aBullet[nCntBill].nType = BULLET_NORMAL;
		g_aBullet[nCntBill].nEffectCounter = EFFECT_COUNTER;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBill = 0; nCntBill < MAX_BULLET; nCntBill++)
	{
		//���_���W�̐ݒ� 
		pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, +BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+BULLET_SIZE, +BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+BULLET_SIZE, -BULLET_SIZE, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBullet->Unlock();
}

//====================================================================
//�r���{�[�h�̏I������
//====================================================================
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//====================================================================
//�r���{�[�h�̍X�V����
//====================================================================
void UpdateBullet(void)
{
	int nCntBill;

	for (nCntBill = 0; nCntBill < MAX_BULLET; nCntBill++)
	{
		if (g_aBullet[nCntBill].bUse == true)
		{
			g_aBullet[nCntBill].posOld = g_aBullet[nCntBill].pos;

			//�e�̈ʒu�X�V
			g_aBullet[nCntBill].pos += g_aBullet[nCntBill].move;

			//���������炷
			g_aBullet[nCntBill].nLife--;

			////�v���C���[�Ƃ̓����蔻��
			//CollisionPlayer(&g_aBullet[nCntBill]);
			//Player *pPlayer = GetPlayer();

			g_aBullet[nCntBill].nEffectCounter--;
			if (g_aBullet[nCntBill].nEffectCounter <= 0)
			{
				//�e���ˎ��ɃG�t�F�N�g���Ăяo��
				SetEffect(g_aBullet[nCntBill].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8.0f, 10);
				g_aBullet[nCntBill].nEffectCounter = EFFECT_COUNTER;
			}

			//�������Ȃ��Ȃ������e������
			if (g_aBullet[nCntBill].nLife <= 0)
			{
				g_aBullet[nCntBill].bUse = false;
			}

			//�����蔻��
			GetCollisionPlayer(g_aBullet[nCntBill].pos, BULLET_SIZE);
		}
	}

	VERTEX_3D*pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBill = 0; nCntBill < MAX_BULLET; nCntBill++)
	{
		if (g_aBullet[nCntBill].bUse == true)
		{
			//���_���W�̐ݒ� 
			pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, +BULLET_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+BULLET_SIZE, +BULLET_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+BULLET_SIZE, -BULLET_SIZE, 0.0f);
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//====================================================================
//�r���{�[�h�̕`�揈��
//====================================================================
void DrawBullet(void)
{
	int nCntBill;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;	//�r���[�}�g���b�N�X�����p

	////Z�e�X�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntBill = 0; nCntBill < MAX_BULLET; nCntBill++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBullet[nCntBill].mtxWorld);

		//�r���[�}�g���b�N�X������
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂ�������
		D3DXMatrixInverse(&g_aBullet[nCntBill].mtxWorld, NULL, &mtxView);	//�t�s������߂�
		g_aBullet[nCntBill].mtxWorld._41 = 0.0f;
		g_aBullet[nCntBill].mtxWorld._42 = 0.0f;
		g_aBullet[nCntBill].mtxWorld._43 = 0.0f;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBill].pos.x, g_aBullet[nCntBill].pos.y, g_aBullet[nCntBill].pos.z);

		D3DXMatrixMultiply(&g_aBullet[nCntBill].mtxWorld, &g_aBullet[nCntBill].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBill].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBullet);

		if (g_aBullet[nCntBill].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntBill,										//�v���~�e�B�u(�|���S��)��
				2);
		}
	}

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	////Z�e�X�g��L���ɂ���
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//====================================================================
//�r���{�[�h�̐ݒ菈��
//====================================================================
void SetBullet(D3DXVECTOR3 pos, float rot, int nLife, BULLET_TYPE Type)
{
	int nCntBill;

	VERTEX_2D*pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBill = 0; nCntBill < MAX_BULLET; nCntBill++)
	{
		if (g_aBullet[nCntBill].bUse == false)
		{
			g_aBullet[nCntBill].pos = pos;
			g_aBullet[nCntBill].posOld = pos;
			g_aBullet[nCntBill].move = D3DXVECTOR3(sinf(rot) * BULLET_SPEED, 0.0f, cosf(rot) * BULLET_SPEED);
			g_aBullet[nCntBill].rot = rot;
			g_aBullet[nCntBill].nType = Type;
			g_aBullet[nCntBill].nLife = nLife;
			g_aBullet[nCntBill].bUse = true;

			////�T�E���h�̍Đ�
			//PlaySound(SOUND_LABEL_SE_CANNON_BULLET);

			break;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

////====================================================================
////�e�ƃv���C���[�̓����蔻��
////====================================================================
//void CollisionPlayer(Bullet*pBullet)
//{
//	Player * pPlayer = GetPlayer();		//�I�u�W�F�N�g�̏��ւ̃|�C���^
//
//	if (
//		pBullet->pos.z >= pPlayer->pos.z + pPlayer->vtxMin.z &&
//		pBullet->pos.z <= pPlayer->pos.z + pPlayer->vtxMax.z &&
//		pBullet->pos.x >= pPlayer->pos.x + pPlayer->vtxMin.x &&
//		pBullet->pos.x <= pPlayer->pos.x + pPlayer->vtxMax.x &&
//		pBullet->pos.y >= pPlayer->pos.y + pPlayer->vtxMin.y &&
//		pBullet->pos.y <= pPlayer->pos.y + +pPlayer->vtxMax.y
//		)
//	{//�G�ƍU������������
//		pBullet->bUse = false;
//		falseShadow(pBullet->nIndex);
//		SetExplosion(pBullet->pos, 0);
//		SetParticle(pBullet->pos, D3DXVECTOR3(pBullet->rot, pBullet->rot, pBullet->rot), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 5.0f, 4);
//		PlayerHit();
//	}
//}

//====================================================================
//�e�̏���
//====================================================================
D3DXVECTOR3 GETAAA(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================================================
//�e�̏���
//====================================================================
Bullet * GetBullet(void)
{
	return &g_aBullet[0];
}