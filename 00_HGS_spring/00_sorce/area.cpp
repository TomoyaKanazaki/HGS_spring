//======================================================================================================================
//
//	��揈�� [area.cpp]
//	Author�F���c�E��
//
//======================================================================================================================
//**********************************************************************************************************************
//	�C���N���[�h�t�@�C��
//**********************************************************************************************************************
#include "main.h"
#include "area.h"
#include "player.h"

//**********************************************************************************************************************
//	�}�N����`
//**********************************************************************************************************************
#define MAX_AREA	(6)		// �g�p����|���S���� (���\���̍ő吔)

//**********************************************************************************************************************
//	�R���X�g��`
//**********************************************************************************************************************
const char *apTextureArea[] =			// �e�N�X�`���̑��΃p�X
{
	"02_data\\02_TEXTURE\\area000.png",	// ���̃e�N�X�`���̑��΃p�X
};

const float aRadiusArea[] =	// ���̔��a
{
	100.0f,					// �Z�[�t�G���A
	300.0f,				// ���G���A
	550.0f,				// ���G���A
	800.0f,				// ��O�G���A
	1050.0f,				// ��l�G���A
	10000000.0f,				// ���b�h�G���A
};

const D3DXCOLOR aColorArea[] =			// ���̐F
{
	D3DCOLOR_RGBA(0,   255, 0, 255),	// �Z�[�t�G���A
	D3DCOLOR_RGBA(50,  205, 5, 255),	// ���G���A
	D3DCOLOR_RGBA(100, 155, 4, 255),	// ���G���A
	D3DCOLOR_RGBA(155, 100, 3, 255),	// ��O�G���A
	D3DCOLOR_RGBA(205, 50,  2, 255),	// ��l�G���A
	D3DCOLOR_RGBA(255, 0,   0, 255),	// ���b�h�G���A
};

//**********************************************************************************************************************
//	�\���̒�` (Area)
//**********************************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXMATRIX  mtxWorld;	// ���[���h�}�g���b�N�X
}Area;

//**********************************************************************************************************************
//	�񋓌^��` (TEXTURE_AREA)
//**********************************************************************************************************************
typedef enum
{
	TEXTURE_AREA_NORMAL = 0,		// ��� (�ʏ�)
	TEXTURE_AREA_MAX,				// ���̗񋓌^�̑���
} TEXTURE_AREA;

//**********************************************************************************************************************
//	�O���[�o���ϐ�
//**********************************************************************************************************************
LPDIRECT3DTEXTURE9      g_apTextureArea[TEXTURE_AREA_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArea = NULL;					// ���_�o�b�t�@�ւ̃|�C���^

Area g_aArea[MAX_AREA];				// ���̏��

//======================================================================================================================
//	���̏���������
//======================================================================================================================
void InitArea(void)
{
	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�ւ̃|�C���^
	VERTEX_3D *pVtx;							// ���_���ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	for (int nCntArea = 0; nCntArea < TEXTURE_AREA_MAX; nCntArea++)
	{ // �g�p����e�N�X�`�������J��Ԃ�

		D3DXCreateTextureFromFile(pDevice, apTextureArea[nCntArea], &g_apTextureArea[nCntArea]);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	( // ����
		sizeof(VERTEX_3D) * 4 * MAX_AREA,		// �K�v���_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,							// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffArea,
		NULL
	);

	// ���̏��̏�����
	for (int nCntArea = 0; nCntArea < MAX_AREA; nCntArea++)
	{ // ���̍ő�\�������J��Ԃ�

		g_aArea[nCntArea].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_aArea[nCntArea].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	}

	//------------------------------------------------------------------------------------------------------------------
	//	���_���̏�����
	//------------------------------------------------------------------------------------------------------------------
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffArea->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntArea = MAX_AREA - 1; nCntArea >= 0; nCntArea--)
	{ // ���̍ő�\�������J��Ԃ�

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-aRadiusArea[nCntArea], 0.0f, +aRadiusArea[nCntArea]);
		pVtx[1].pos = D3DXVECTOR3(+aRadiusArea[nCntArea], 0.0f, +aRadiusArea[nCntArea]);
		pVtx[2].pos = D3DXVECTOR3(-aRadiusArea[nCntArea], 0.0f, -aRadiusArea[nCntArea]);
		pVtx[3].pos = D3DXVECTOR3(+aRadiusArea[nCntArea], 0.0f, -aRadiusArea[nCntArea]);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = aColorArea[nCntArea];
		pVtx[1].col = aColorArea[nCntArea];
		pVtx[2].col = aColorArea[nCntArea];
		pVtx[3].col = aColorArea[nCntArea];

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^�̃|�C���^�� 4���i�߂�
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffArea->Unlock();
}

//======================================================================================================================
//	���̏I������
//======================================================================================================================
void UninitArea(void)
{
	// �e�N�X�`���̔j��
	for (int nCntArea = 0; nCntArea < TEXTURE_AREA_MAX; nCntArea++)
	{ // �g�p����e�N�X�`�������J��Ԃ�

		if (g_apTextureArea[nCntArea] != NULL)
		{ // �ϐ� (g_apTextureArea) ��NULL�ł͂Ȃ��ꍇ

			g_apTextureArea[nCntArea]->Release();
			g_apTextureArea[nCntArea] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffArea != NULL)
	{ // �ϐ� (g_pVtxBuffArea) ��NULL�ł͂Ȃ��ꍇ

		g_pVtxBuffArea->Release();
		g_pVtxBuffArea = NULL;
	}
}

//======================================================================================================================
//	���̍X�V����
//======================================================================================================================
void UpdateArea(void)
{

}

//======================================================================================================================
//	���̕`�揈��
//======================================================================================================================
void DrawArea(void)
{
	// �ϐ���錾
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);		// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			// Z�o�b�t�@�X�V�̗L�� / �����̐ݒ�

	for (int nCntArea = 0; nCntArea < MAX_AREA; nCntArea++)
	{ // ���̍ő�\�������J��Ԃ�

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aArea[nCntArea].mtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aArea[nCntArea].rot.y, g_aArea[nCntArea].rot.x, g_aArea[nCntArea].rot.z);
		D3DXMatrixMultiply(&g_aArea[nCntArea].mtxWorld, &g_aArea[nCntArea].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aArea[nCntArea].pos.x, g_aArea[nCntArea].pos.y, g_aArea[nCntArea].pos.z);
		D3DXMatrixMultiply(&g_aArea[nCntArea].mtxWorld, &g_aArea[nCntArea].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aArea[nCntArea].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffArea, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureArea[TEXTURE_AREA_NORMAL]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntArea * 4, 2);
	}

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);		// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			// Z�o�b�t�@�X�V�̗L�� / �����̐ݒ�
}

//======================================================================================================================
//	���̎擾����
//======================================================================================================================
AREATYPE GetCurrentArea(void)
{
	// �ϐ���錾
	float fLength = GetPosPlayer().x * GetPosPlayer().x + GetPosPlayer().z * GetPosPlayer().z;	// �G���A�Ƃ̋���

	if (fLength < aRadiusArea[AREATYPE_SAFE] * aRadiusArea[AREATYPE_SAFE])
	{ // �Z�[�t�G���A�͈͓̔��̏ꍇ

		// ���݂̃G���A��Ԃ�
		return AREATYPE_SAFE;
	}
	else if (fLength < aRadiusArea[AREATYPE_01] * aRadiusArea[AREATYPE_01])
	{ // ���G���A�͈͓̔��̏ꍇ

		// ���݂̃G���A��Ԃ�
		return AREATYPE_01;
	}
	else if (fLength < aRadiusArea[AREATYPE_02] * aRadiusArea[AREATYPE_02])
	{ // ���G���A�͈͓̔��̏ꍇ

		// ���݂̃G���A��Ԃ�
		return AREATYPE_02;
	}
	else if (fLength < aRadiusArea[AREATYPE_03] * aRadiusArea[AREATYPE_03])
	{ // ��O�G���A�͈͓̔��̏ꍇ

		// ���݂̃G���A��Ԃ�
		return AREATYPE_03;
	}
	else if (fLength < aRadiusArea[AREATYPE_04] * aRadiusArea[AREATYPE_04])
	{ // ��l�G���A�͈͓̔��̏ꍇ

		// ���݂̃G���A��Ԃ�
		return AREATYPE_04;
	}
	else
	{ // ���b�h�G���A�͈͓̔��̏ꍇ

		// ���݂̃G���A��Ԃ�
		return AREATYPE_RED;
	}
}

//======================================================================================================================
//	���̎擾����
//======================================================================================================================
AREATYPE GetEnemyArea(D3DXVECTOR3 pos)
{
	// �ϐ���錾
	float fLength = pos.x * pos.x + pos.z * pos.z;	// �G���A�Ƃ̋���

	if (fLength < aRadiusArea[AREATYPE_SAFE] * aRadiusArea[AREATYPE_SAFE])
	{ // �Z�[�t�G���A�͈͓̔��̏ꍇ

	  // ���݂̃G���A��Ԃ�
		return AREATYPE_SAFE;
	}
	else if (fLength < aRadiusArea[AREATYPE_01] * aRadiusArea[AREATYPE_01])
	{ // ���G���A�͈͓̔��̏ꍇ

	  // ���݂̃G���A��Ԃ�
		return AREATYPE_01;
	}
	else if (fLength < aRadiusArea[AREATYPE_02] * aRadiusArea[AREATYPE_02])
	{ // ���G���A�͈͓̔��̏ꍇ

	  // ���݂̃G���A��Ԃ�
		return AREATYPE_02;
	}
	else if (fLength < aRadiusArea[AREATYPE_03] * aRadiusArea[AREATYPE_03])
	{ // ��O�G���A�͈͓̔��̏ꍇ

	  // ���݂̃G���A��Ԃ�
		return AREATYPE_03;
	}
	else if (fLength < aRadiusArea[AREATYPE_04] * aRadiusArea[AREATYPE_04])
	{ // ��l�G���A�͈͓̔��̏ꍇ

	  // ���݂̃G���A��Ԃ�
		return AREATYPE_04;
	}
	else
	{ // ���b�h�G���A�͈͓̔��̏ꍇ

	  // ���݂̃G���A��Ԃ�
		return AREATYPE_RED;
	}
}

//==========================================
//  ���͈̔͂��擾
//==========================================
float GetAreaSize(int areatype)
{
	return aRadiusArea[areatype];
}
