#include "main.h"
#include "Enemy.h"
#include "Bullet.h"
#include "particle.h"
#include "player.h"
#include "area.h"

#define ENEMY00_LIFE (7)		//�G�̗̑�
#define ENWMY_MOVE (1.0f)		//�G�̈ړ���
#define BULLET_POS_XZ (20.0f)	//�e�̔��ˈʒu(���̎�)
#define BULLET_POS_Y (25.0f)	//�e�̔��ˈʒu(�c�̎�)
#define BULLET_LIFE (120)		//�e�̎���
#define BULLETCOUNTER (120)		//�e�������o
#define ENEMY_CHASE (500.0f)	//�G���ǂ������Ă��鋗��
#define ENEMY_NUM (100) // * ���ԍ� = ��������G�̐�
#define ENEMY_COLLISION (10.0f) //�G���m�̓����蔻��

//�v���g�^�C�v�錾
void UpdateSlime(int nCnt);
void UpdateCannon(int nCnt);
void RandSetEnemy(void);

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEnemy[ENEMY_MAX][64] = {};	//�e�N�X�`���̃|�C���^
LPD3DXMESH g_pMeshEnemy[ENEMY_MAX] = {};					//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatEnemy[ENEMY_MAX] = {};				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatEnemy[ENEMY_MAX] = {};						//�}�e���A���̐�

Enemy g_Enemy[MAX_ENEMY];					//�G�̏��

bool g_bHit; //�q�b�g����

//====================================================================
//�G�̏���������
//====================================================================
void InitEnemy(void)
{
	g_bHit = false;
	int nCntEnemy;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_Enemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Enemy[nCntEnemy].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Enemy[nCntEnemy].BulletCounter = 0;
		g_Enemy[nCntEnemy].bUse = false;
		g_Enemy[nCntEnemy].nType = ENEMY_NTYPE00;
		g_Enemy[nCntEnemy].State = ENEMY_STATE_WAIT;
		g_Enemy[nCntEnemy].pMatD.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("02_data\\03_MODEL\\Enemy00.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[ENEMY_NTYPE00],
		NULL,
		&g_dwNumMatEnemy[ENEMY_NTYPE00],
		&g_pMeshEnemy[ENEMY_NTYPE00]);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("02_data\\03_MODEL\\cannon.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[ENEMY_NTYPE01],
		NULL,
		&g_dwNumMatEnemy[ENEMY_NTYPE01],
		&g_pMeshEnemy[ENEMY_NTYPE01]);

	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntNumObject = 0; nCntNumObject < ENEMY_MAX; nCntNumObject++)
	{
		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[nCntNumObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy[nCntNumObject]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureEnemy[nCntNumObject][nCntMat]);
			}
		}
	}

	//�G��ݒ�
	RandSetEnemy();
}

//====================================================================
//�G�̏I������
//====================================================================
void UninitEnemy(void)
{
	for (int nCntNumObject = 0; nCntNumObject < ENEMY_MAX; nCntNumObject++)
	{
		for (int nCntTex = 0; nCntTex < 64; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_pTextureEnemy[nCntNumObject][nCntTex] != NULL)
			{
				g_pTextureEnemy[nCntNumObject][nCntTex]->Release();
				g_pTextureEnemy[nCntNumObject][nCntTex] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_pMeshEnemy[nCntNumObject] != NULL)
		{
			g_pMeshEnemy[nCntNumObject]->Release();
			g_pMeshEnemy[nCntNumObject] = NULL;
		}

		//�}�e���A���̔j��
		if (g_pBuffMatEnemy[nCntNumObject] != NULL)
		{
			g_pBuffMatEnemy[nCntNumObject]->Release();
			g_pBuffMatEnemy[nCntNumObject] = NULL;
		}
	}
}

//====================================================================
//�G�̍X�V����
//====================================================================
void UpdateEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			g_Enemy[nCntEnemy].posOld = g_Enemy[nCntEnemy].pos;

			switch (g_Enemy[nCntEnemy].nType)
			{
			case ENEMY_NTYPE00:		//�ǐՂ���G

				UpdateSlime(nCntEnemy);

				break;
			case ENEMY_NTYPE01:		//��C

				UpdateCannon(nCntEnemy);

				break;
			}

			//����
			g_bHit = GetCollisionPlayer(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].fRadius);
		}
	}
}

//====================================================================
//�ǐՂ���G�̍X�V����
//====================================================================
void UpdateSlime(int nCnt)
{
	D3DXVECTOR3 pPosPlayer = GetPosPlayer();		//�v���C���[�̏��ւ̃|�C���^

	switch (g_Enemy[nCnt].State)
	{
	case ENEMY_STATE_WAIT:
		break;
	case ENEMY_STATE_BATTLE:
		break;
	}

	if (CollisionCircle(pPosPlayer, g_Enemy[nCnt].pos, ENEMY_CHASE, 5.0f, -10.0f, 10.0f) == true)
	{
		//�ړ�����
		g_Enemy[nCnt].move = D3DXVECTOR3(-cosf(g_Enemy[nCnt].rot.y) * ENWMY_MOVE, 0.0f, sinf(g_Enemy[nCnt].rot.y) * ENWMY_MOVE);
		g_Enemy[nCnt].State = ENEMY_STATE_BATTLE;

		//�����̕␳
		RotEnemy(g_Enemy[nCnt].pos, nCnt);
	}
	else
	{
		g_Enemy[nCnt].move = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_Enemy[nCnt].State = ENEMY_STATE_WAIT;
	}

	//�ʒu�X�V(���͂ɂ�铮��)
	g_Enemy[nCnt].pos += g_Enemy[nCnt].move;

	//for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	//{
	//	if (g_Enemy[nCntEnemy].bUse == true && nCnt != nCntEnemy)
	//	{
	//		if (CollisionCircle(g_Enemy[nCnt].pos, g_Enemy[nCntEnemy].pos, ENEMY_COLLISION, 0.0f, -10.0f, 10.0f) == true)
	//		{
	//			g_Enemy[nCnt].pos = g_Enemy[nCnt].posOld;
	//		}
	//	}
	//}

	//Player *pPlayer = GetPlayer();

	////�m�b�N�o�b�N����
	//if (CollisionCircle(pPlayer->pos, g_Enemy[nCnt].pos, 120.0f, 0.0f, pPlayer->vtxMin.y, pPlayer->vtxMax.y) == true)
	//{
	//	KnoccBackPlayer(g_Enemy[nCnt].pos, KNOCCBACKPOWER);
	//}

	////�v���C���[�Ƃ̓����蔻��
	//CollisionPlayer(g_Enemy[nCnt].pos, g_Enemy[nCnt].posOld, 23.0f, g_Enemy[nCnt].vtxMax.y, g_Enemy[nCnt].vtxMin.y);
}

//====================================================================
//��C�̍X�V����
//====================================================================
void UpdateCannon(int nCnt)
{
	D3DXVECTOR3 pPosPlayer = GetPosPlayer();		//�v���C���[�̏��ւ̃|�C���^

	//�����̕␳
	RotEnemy(g_Enemy[nCnt].pos, nCnt);

	if (CollisionCircle(pPosPlayer, g_Enemy[nCnt].pos, ENEMY_CHASE, 0.0f, -10.0f, 10.0f) == true)
	{
		//�e���˂̃N�[���^�C��������������
		g_Enemy[nCnt].BulletCounter++;

		if (g_Enemy[nCnt].BulletCounter >= BULLETCOUNTER)
		{
			SetBullet(D3DXVECTOR3(
				g_Enemy[nCnt].pos.x - cosf(g_Enemy[nCnt].rot.y) * BULLET_POS_XZ,
				g_Enemy[nCnt].pos.y + BULLET_POS_Y,
				g_Enemy[nCnt].pos.z + sinf(g_Enemy[nCnt].rot.y) * BULLET_POS_XZ),
				g_Enemy[nCnt].rot.y + D3DX_PI * -0.5f,
				BULLET_LIFE,
				BULLET_NORMAL);

			SetParticle(
				D3DXVECTOR3(
					g_Enemy[nCnt].pos.x - cosf(g_Enemy[nCnt].rot.y) * 40.0f,
					g_Enemy[nCnt].pos.y + 25.0f,
					g_Enemy[nCnt].pos.z + sinf(g_Enemy[nCnt].rot.y) * 40.0f),
				g_Enemy[nCnt].rot,
				D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f),
				5,
				5.0f,
				6);

			g_Enemy[nCnt].BulletCounter = 0;
		}

		//�ʒu�X�V(���͂ɂ�铮��)
		g_Enemy[nCnt].pos += g_Enemy[nCnt].move;
	}
}

//====================================================================
//�G���v���C���[�̕���������
//====================================================================
void RotEnemy(D3DXVECTOR3 Pos, int nCnt)
{
	D3DXVECTOR3 pPosPlayer = GetPosPlayer();		//�v���C���[�̏��ւ̃|�C���^

	float fAngle = atan2f(pPosPlayer.z - Pos.z, Pos.x - pPosPlayer.x);

	g_Enemy[nCnt].rot.y = fAngle;
}

//====================================================================
//�v���C���[�̂��m�b�N�o�b�N���鏈��
//====================================================================
void KnoccBackPlayer(D3DXVECTOR3 Pos, float Power)
{
	//Player * pPlayer = GetPlayer();		//�v���C���[�̏��ւ̃|�C���^

	//float fAngle = atan2f(pPlayer->pos.z - Pos.z, Pos.x - pPlayer->pos.x);

	//pPlayer->move.x -= cosf(fAngle) * Power;
	//pPlayer->move.z += sinf(fAngle) * Power;
}

//====================================================================
//�~���̓����蔻��
//====================================================================
bool CollisionCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut, float nRadiusIn, float MinY, float MaxY)
{
	bool nHit = false;

	if (sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
		+ (pos1.z - pos2.z) * (pos1.z - pos2.z)) <= nRadiusOut
		&& sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
			+ (pos1.z - pos2.z) * (pos1.z - pos2.z)) >= nRadiusIn
		&& pos1.y + MinY < pos2.y
		&& pos1.y + MaxY > pos2.y)
	{//�~�̔��肪��������
		nHit = true;
	}

	return nHit;
}

//====================================================================
//�G�̕`�揈��
//====================================================================
void DrawEnemy(void)
{
	int nCntEnemy;

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Enemy[nCntEnemy].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].rot.y, g_Enemy[nCntEnemy].rot.x, g_Enemy[nCntEnemy].rot.z);

		D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);

		D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^����������
		pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[g_Enemy[nCntEnemy].nType]->GetBufferPointer();

		if (g_Enemy[nCntEnemy].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy[g_Enemy[nCntEnemy].nType]; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureEnemy[g_Enemy[nCntEnemy].nType][nCntMat]);

				//�G(�p�[�c)�̕`��
				g_pMeshEnemy[g_Enemy[nCntEnemy].nType]->DrawSubset(nCntMat);

			}
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//====================================================================
//�G�̐ݒ菈��
//====================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == false)
		{
			g_Enemy[nCntEnemy].pos = pos;
			g_Enemy[nCntEnemy].posOld = pos;
			g_Enemy[nCntEnemy].nType = nType;
			g_Enemy[nCntEnemy].State = ENEMY_STATE_WAIT;
			g_Enemy[nCntEnemy].bUse = true;

			int nNumVtx;		//���_��
			DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
			
			//���_��������
			nNumVtx = g_pMeshEnemy[nType]->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y������
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshEnemy[nType]->GetFVF());

			//���_�o�b�t�@�����b�N
			g_pMeshEnemy[nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				if (g_Enemy[nCntEnemy].vtxMin.x > vtx.x)
				{
					g_Enemy[nCntEnemy].vtxMin.x = vtx.x;
				}
				if (g_Enemy[nCntEnemy].vtxMin.y > vtx.y)
				{
					g_Enemy[nCntEnemy].vtxMin.y = vtx.y;
				}
				if (g_Enemy[nCntEnemy].vtxMin.z > vtx.z)
				{
					g_Enemy[nCntEnemy].vtxMin.z = vtx.z;
				}

				if (g_Enemy[nCntEnemy].vtxMax.x < vtx.x)
				{
					g_Enemy[nCntEnemy].vtxMax.x = vtx.x;
				}
				if (g_Enemy[nCntEnemy].vtxMax.y < vtx.y)
				{
					g_Enemy[nCntEnemy].vtxMax.y = vtx.y;
				}
				if (g_Enemy[nCntEnemy].vtxMax.z < vtx.z)
				{
					g_Enemy[nCntEnemy].vtxMax.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}

			//���_�o�b�t�@���A�����b�N
			g_pMeshEnemy[nType]->UnlockVertexBuffer();

			// ���f���T�C�Y�����߂�
			g_Enemy[nCntEnemy].size = g_Enemy[nCntEnemy].vtxMax - g_Enemy[nCntEnemy].vtxMin;

			// ���f���̉~�̓����蔻����쐬
			g_Enemy[nCntEnemy].fRadius = ((g_Enemy[nCntEnemy].size.x * 0.5f) + (g_Enemy[nCntEnemy].size.z * 0.5f)) * 0.5f;

			break;
		}
	}
}

//====================================================================
//�v���C���[�Ƃ̓����蔻�菈��
//====================================================================
void CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			if (
				(pPos->z + max.z >= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].vtxMin.z && pPosOld->z + max.z< g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].vtxMin.z ||
					pPos->z + min.z <= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].vtxMax.z && pPosOld->z + min.z > g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].vtxMax.z) &&
				pPos->x + max.x >= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].vtxMin.x &&
				pPos->x + min.x <= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].vtxMax.x &&
				pPos->y + max.y >= g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].vtxMin.y&&
				pPos->y + min.y <= g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].vtxMax.y
				)
			{//�ǂƃv���C���[����������(Z��)
				pPos->z = pPosOld->z;
				pMove->z = 0.0f;
			}

			if (
				(pPos->x + max.x >= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].vtxMin.x && pPosOld->x + max.x< g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].vtxMin.x ||
					pPos->x + min.x <= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].vtxMax.x && pPosOld->x + min.x > g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].vtxMax.x) &&
				pPos->z + max.z >= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].vtxMin.z &&
				pPos->z + min.z <= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].vtxMax.z &&
				pPos->y + max.y >= g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].vtxMin.y &&
				pPos->y + min.y <= g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].vtxMax.y
				)
			{//�ǂƃv���C���[����������(X��)
				pPos->x = pPosOld->x;
				pMove->x = 0.0f;
			}
		}
	}
}

//====================================================================
//�G�̏���
//====================================================================
Enemy * GetEnemy(void)
{
	return &g_Enemy[0];
}

//==========================================
//  �����蔻��̎擾
//==========================================
bool GetHit()
{
	return g_bHit;
}

//==========================================
//  �G�𔭐�
//==========================================
void RandSetEnemy()
{
	//���̐����Z�b�g���Ăяo��
	for (int nCntArea = 0; nCntArea < AREATYPE_MAX; nCntArea++)
	{
		//(���ԍ� * ENEMY_NUM)�̉񐔐ݒ肷��
		for (int nCntSet = 0; nCntSet < nCntArea * ENEMY_NUM; nCntSet++)
		{
			//�o�����W(�����_��)���Z�o����
			D3DXVECTOR3 pos = D3DXVECTOR3((float)rand(), 0.0f, (float)rand());
			D3DXVec3Normalize(&pos, &pos);
			pos.x *= 1000.0f;
			pos.z *= 1000.0f;
			pos.x += GetAreaSize(nCntArea) - 1500.0f;
			pos.z += GetAreaSize(nCntArea) - 1500.0f;
			if (rand() % 2 == 0)
			{
				pos.x *= -1.0f;
			}
			if (rand() % 2 == 0)
			{
				pos.z *= -1.0f;
			}

			//�G�̎�ނ�ݒ�
			int nType = rand() % ENEMY_MAX;

			//�G��ݒu
			SetEnemy(pos, nType);
		}
	}
}
