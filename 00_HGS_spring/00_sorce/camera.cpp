//============================================================
//
//	�J�������� [camera.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "camera.h"
#include "input.h"

#ifdef _DEBUG	// �f�o�b�O����
#endif

//************************************************************
//	�}�N����`
//************************************************************
// �J�����S��
#define VIEW_NEAR		(10.0f)		// ���f����������Z���̍ŏ��l
#define VIEW_FAR		(8000.0f)	// ���f����������Z���̍ő�l

// ���C���J����
#define FIRST_ROT		(1.45f)		// �J�n���̎��_�ƒ����_�̊Ԃ̌��� (x)
#define FIRST_DIS		(-340.0f)	// �J�n���̎��_�ƒ����_�̊Ԃ̋���

#define REV_ROT_FOLLOW	(0.05f)		// �Ǐ]���̉�荞�݂̕␳�W��
#define REV_POS_V		(0.225f)	// ���_�̈ʒu�̕␳�W�� (x, z)
#define REV_POS_R		(0.25f)		// �����_�̈ʒu�̕␳�W�� (x, z)
#define REV_POS_V_Y		(0.045f)	// ���_�̈ʒu�̕␳�W�� (y)
#define REV_POS_R_Y		(0.05f)		// �����_�̈ʒu�̕␳�W�� (y)

#define MOVE_CAMERA		(4.0f)		// �J�����̈ړ���
#define MOVE_ROT_X		(0.015f)	// �����̕ύX�� (x)
#define MOVE_ROT_Y		(0.03f)		// �����̕ύX�� (y)
#define MOVE_DIS		(2.0f)		// �����̕ύX��
#define REV_DIS			(-1.0f)		// �����̕␳�l

#define REV_DIS_MOUSE	(-0.15f)	// �}�E�X����ł̃J�����̋����̕␳�W��
#define REV_ROT_MOUSE	(0.008f)	// �}�E�X����ł̃J�����̉�]�ʂ̕␳�W��

#define MUL_ANGLE_PLUS	(1.8f)		// �u�[�X�g���̎���p�����̏�Z��

#define LIMIT_ROT_HIGH	(D3DX_PI - 0.1f)	// ��]�� (x) �̉�]�����l (��)
#define LIMIT_ROT_LOW	(0.1f)				// ��]�� (x) �̉�]�����l (��)

//************************************************************
//	�v���g�^�C�v�錾
//************************************************************
void InitMapCamera(void);			// �}�b�v�J�����̏���������
void InitUiCamera(void);			// UI�J�����̏���������

void MoveFollowCamera(void);		// ���C���J�����̈ʒu�̍X�V���� (�Ǐ])

void MoveCamera(void);				// ���C���J�����̈ʒu�̍X�V���� (����)
void DisCamera(void);				// ���C���J�����̋����̍X�V���� (����)
void RotCamera(void);				// ���C���J�����̌����̍X�V���� (����)

void RevRotXCamera(void);			// �J�����̌����̕␳���� (x)
void RevRotYCamera(void);			// �J�����̌����̕␳���� (y)

//************************************************************
//	�O���[�o���ϐ�
//************************************************************
Camera g_aCamera[CAMERATYPE_MAX];	// �J�����̏��

//============================================================
//	�J�����̏���������
//============================================================
void InitCamera(void)
{
	// ��{����������
	g_aCamera[CAMERATYPE_MAIN].posV     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���݂̎��_
	g_aCamera[CAMERATYPE_MAIN].posVOld  = g_aCamera[CAMERATYPE_MAIN].posV;		// �O��̎��_
	g_aCamera[CAMERATYPE_MAIN].posR     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���݂̒����_
	g_aCamera[CAMERATYPE_MAIN].destPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ڕW�̎��_
	g_aCamera[CAMERATYPE_MAIN].destPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ڕW�̒����_
	g_aCamera[CAMERATYPE_MAIN].vecU     = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// ������x�N�g��
	g_aCamera[CAMERATYPE_MAIN].rot      = D3DXVECTOR3(FIRST_ROT, 0.0f, 0.0f);	// ����
	g_aCamera[CAMERATYPE_MAIN].fDis     = FIRST_DIS;							// ���_�ƒ����_�̋���

	// �r���[�|�[�g����������
	g_aCamera[CAMERATYPE_MAIN].viewport.X      = 0;				// ������̃s�N�Z�����W (x)
	g_aCamera[CAMERATYPE_MAIN].viewport.Y      = 0;				// ������̃s�N�Z�����W (y)
	g_aCamera[CAMERATYPE_MAIN].viewport.Width  = SCREEN_WIDTH;	// �`�悷���ʂ̉���
	g_aCamera[CAMERATYPE_MAIN].viewport.Height = SCREEN_HEIGHT;	// �`�悷���ʂ̏c��
	g_aCamera[CAMERATYPE_MAIN].viewport.MinZ   = 0.0f;
	g_aCamera[CAMERATYPE_MAIN].viewport.MaxZ   = 1.0f;

	// �}�b�v�J�����̏�����
	InitMapCamera();

	// UI�J�����̏�����
	InitUiCamera();
}

//============================================================
//	�J�����̏I������
//============================================================
void UninitCamera(void)
{

}

//============================================================
//	�J�����̍X�V����
//============================================================
void UpdateCamera(void)
{
#if 0

#else
	// �J�����̈ʒu�̍X�V (����)
	MoveCamera();

	// �J�����̋����̍X�V (����)
	DisCamera();

	// �J�����̌����̍X�V (����)
	RotCamera();
#endif
}

//============================================================
//	�J�����̐ݒ菈��
//============================================================
void SetCamera(int nID)
{
	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// �r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_aCamera[nID].viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aCamera[nID].mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH
	( // ����
		&g_aCamera[nID].mtxProjection,													// �v���W�F�N�V�����}�g���b�N�X
		VIEW_ANGLE,																		// ����p
		(float)g_aCamera[nID].viewport.Width / (float)g_aCamera[nID].viewport.Height,	// ��ʂ̃A�X�y�N�g��
		VIEW_NEAR,																		// Z���̍ŏ��l
		VIEW_FAR																		// Z���̍ő�l
	);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_aCamera[nID].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aCamera[nID].mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH
	( // ����
		&g_aCamera[nID].mtxView,	// �r���[�}�g���b�N�X
		&g_aCamera[nID].posV,		// ���_
		&g_aCamera[nID].posR,		// �����_
		&g_aCamera[nID].vecU		// ������x�N�g��
	);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_aCamera[nID].mtxView);
}

//======================================================================================================================
//	�}�b�v�J�����̏���������
//======================================================================================================================
void InitMapCamera(void)
{
	// ��{����������
	g_aCamera[CAMERATYPE_MAP].posV     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���݂̎��_
	g_aCamera[CAMERATYPE_MAP].posVOld  = g_aCamera[CAMERATYPE_MAP].posV;		// �O��̎��_
	g_aCamera[CAMERATYPE_MAP].posR     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���݂̒����_
	g_aCamera[CAMERATYPE_MAP].destPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ڕW�̎��_
	g_aCamera[CAMERATYPE_MAP].destPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ڕW�̒����_
	g_aCamera[CAMERATYPE_MAP].vecU     = D3DXVECTOR3(0.0f, 0.0f, 1.0f);			// ������x�N�g��
	g_aCamera[CAMERATYPE_MAP].rot      = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	g_aCamera[CAMERATYPE_MAP].fDis     = 0.0f;									// ���_�ƒ����_�̋���

	// �r���[�|�[�g����������
	g_aCamera[CAMERATYPE_MAP].viewport.X      = MAPCAM_X;		// ������̃s�N�Z�����W (x)
	g_aCamera[CAMERATYPE_MAP].viewport.Y      = MAPCAM_Y;		// ������̃s�N�Z�����W (y)
	g_aCamera[CAMERATYPE_MAP].viewport.Width  = MAPCAM_SIZE_X;	// �`�悷���ʂ̉���
	g_aCamera[CAMERATYPE_MAP].viewport.Height = MAPCAM_SIZE_Y;	// �`�悷���ʂ̏c��
	g_aCamera[CAMERATYPE_MAP].viewport.MinZ   = 0.0f;
	g_aCamera[CAMERATYPE_MAP].viewport.MaxZ   = 1.0f;
}

//======================================================================================================================
//	UI�J�����̏���������
//======================================================================================================================
void InitUiCamera(void)
{
	// ��{����������
	g_aCamera[CAMERATYPE_UI].posV     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���݂̎��_
	g_aCamera[CAMERATYPE_UI].posVOld  = g_aCamera[CAMERATYPE_UI].posV;		// �O��̎��_
	g_aCamera[CAMERATYPE_UI].posR     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���݂̒����_
	g_aCamera[CAMERATYPE_UI].destPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ڕW�̎��_
	g_aCamera[CAMERATYPE_UI].destPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ڕW�̒����_
	g_aCamera[CAMERATYPE_UI].vecU     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ������x�N�g��
	g_aCamera[CAMERATYPE_UI].rot      = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	g_aCamera[CAMERATYPE_UI].fDis     = 0.0f;								// ���_�ƒ����_�̋���

	// �r���[�|�[�g����������
	g_aCamera[CAMERATYPE_UI].viewport.X      = 0;				// ������̃s�N�Z�����W (x)
	g_aCamera[CAMERATYPE_UI].viewport.Y      = 0;				// ������̃s�N�Z�����W (y)
	g_aCamera[CAMERATYPE_UI].viewport.Width  = SCREEN_WIDTH;	// �`�悷���ʂ̉���
	g_aCamera[CAMERATYPE_UI].viewport.Height = SCREEN_HEIGHT;	// �`�悷���ʂ̏c��
	g_aCamera[CAMERATYPE_UI].viewport.MinZ   = 0.0f;
	g_aCamera[CAMERATYPE_UI].viewport.MaxZ   = 1.0f;
}

#if 0
//======================================================================================================================
//	���C���J�����̈ʒu�̍X�V���� (�Ǐ])
//======================================================================================================================
void MoveFollowCamera(void)
{
	// �ϐ���錾
	D3DXVECTOR3 diffPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �J�����̎��_�̈ʒu�̌v�Z����p
	D3DXVECTOR3 diffPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �J�����̒����_�̈ʒu�̌v�Z����p

	// �|�C���^��錾
	Player *pPlayer = GetPlayer();		// �v���C���[�̏��

	switch (pPlayer->nCameraState)
	{
	case PLAYCAMESTATE_NORMAL:			// �ʏ�̃J�������

		if (pPlayer->bCameraFirst == true)
		{ // ��l�̂�ON�̏ꍇ

			// �ڕW�̎��_�̈ʒu���X�V
			g_aCamera[CAMERATYPE_MAIN].posV.x = pPlayer->pos.x + sinf(pPlayer->rot.y) * CAMERA_FORWARD_SHIFT;	// �ڕW�����_���狗�������ꂽ�ʒu
			g_aCamera[CAMERATYPE_MAIN].posV.y = pPlayer->pos.y + CAMERA_UP_SHIFT;								// �Œ�̍���
			g_aCamera[CAMERATYPE_MAIN].posV.z = pPlayer->pos.z + cosf(pPlayer->rot.y) * CAMERA_FORWARD_SHIFT;	// �ڕW�����_���狗�������ꂽ�ʒu

			// �ڕW�̒��n�_���X�V����
			g_aCamera[CAMERATYPE_MAIN].posR.x = g_aCamera[CAMERATYPE_MAIN].posV.x - ((g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * sinf(g_aCamera[CAMERATYPE_MAIN].rot.y));	// �ڕW�����_���狗�������ꂽ�ʒu
			g_aCamera[CAMERATYPE_MAIN].posR.y = g_aCamera[CAMERATYPE_MAIN].posV.y;																															// ���_�Ɠ�������
			g_aCamera[CAMERATYPE_MAIN].posR.z = g_aCamera[CAMERATYPE_MAIN].posV.z - ((g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * cosf(g_aCamera[CAMERATYPE_MAIN].rot.y));	// �ڕW�����_���狗�������ꂽ�ʒu
		}
		else
		{ // ��l�̂�OFF�̏ꍇ

			// �ڕW�̒����_�̈ʒu���X�V
			g_aCamera[CAMERATYPE_MAIN].destPosR.x = pPlayer->pos.x + sinf(pPlayer->rot.y + D3DX_PI) * POS_R_PLUS;	// �v���C���[�̈ʒu��菭���O
			g_aCamera[CAMERATYPE_MAIN].destPosR.y = pPlayer->pos.y + POS_R_PLUS_Y;									// �v���C���[�̈ʒu�Ɠ���
			g_aCamera[CAMERATYPE_MAIN].destPosR.z = pPlayer->pos.z + cosf(pPlayer->rot.y + D3DX_PI) * POS_R_PLUS;	// �v���C���[�̈ʒu��菭���O

			// �ڕW�̎��_�̈ʒu���X�V
			g_aCamera[CAMERATYPE_MAIN].destPosV.x = g_aCamera[CAMERATYPE_MAIN].destPosR.x + ((g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * sinf(g_aCamera[CAMERATYPE_MAIN].rot.y));	// �ڕW�����_���狗�������ꂽ�ʒu
			g_aCamera[CAMERATYPE_MAIN].destPosV.y = POS_V_Y;																																						// �Œ�̍���
			g_aCamera[CAMERATYPE_MAIN].destPosV.z = g_aCamera[CAMERATYPE_MAIN].destPosR.z + ((g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * cosf(g_aCamera[CAMERATYPE_MAIN].rot.y));	// �ڕW�����_���狗�������ꂽ�ʒu

			// �ڕW�̈ʒu�܂ł̍������v�Z
			diffPosV = g_aCamera[CAMERATYPE_MAIN].destPosV - g_aCamera[CAMERATYPE_MAIN].posV;	// ���_
			diffPosR = g_aCamera[CAMERATYPE_MAIN].destPosR - g_aCamera[CAMERATYPE_MAIN].posR;	// �����_

			// ���_�̈ʒu���X�V
			g_aCamera[CAMERATYPE_MAIN].posV.x += diffPosV.x * REV_POS_V;
			g_aCamera[CAMERATYPE_MAIN].posV.y += diffPosV.y * REV_POS_V_Y;
			g_aCamera[CAMERATYPE_MAIN].posV.z += diffPosV.z * REV_POS_V;

			// �����_�̈ʒu���X�V
			g_aCamera[CAMERATYPE_MAIN].posR.x += diffPosR.x * REV_POS_R;
			g_aCamera[CAMERATYPE_MAIN].posR.y += diffPosR.y * REV_POS_R_Y;
			g_aCamera[CAMERATYPE_MAIN].posR.z += diffPosR.z * REV_POS_R;
		}

		break;							// �����o��

	case PLAYCAMESTATE_BACK:			// ��������J�������

		if (pPlayer->bCameraFirst == true)
		{ // ��l�̂�ON�̏ꍇ

			// �ڕW�̎��_�̈ʒu���X�V
			g_aCamera[CAMERATYPE_MAIN].posV.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * CAMERA_BACK_SHIFT;	// �ڕW�����_���狗�������ꂽ�ʒu
			g_aCamera[CAMERATYPE_MAIN].posV.y = pPlayer->pos.y + CAMERA_UP_SHIFT;							// �Œ�̍���
			g_aCamera[CAMERATYPE_MAIN].posV.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * CAMERA_BACK_SHIFT;	// �ڕW�����_���狗�������ꂽ�ʒu

			// �ڕW�̒��n�_���X�V����
			g_aCamera[CAMERATYPE_MAIN].posR.x = g_aCamera[CAMERATYPE_MAIN].posV.x + ((g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * sinf(g_aCamera[CAMERATYPE_MAIN].rot.y));	// �ڕW�����_���狗�������ꂽ�ʒu
			g_aCamera[CAMERATYPE_MAIN].posR.y = g_aCamera[CAMERATYPE_MAIN].posV.y;																															// ���_�Ɠ�������
			g_aCamera[CAMERATYPE_MAIN].posR.z = g_aCamera[CAMERATYPE_MAIN].posV.z + ((g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * cosf(g_aCamera[CAMERATYPE_MAIN].rot.y));	// �ڕW�����_���狗�������ꂽ�ʒu
		}
		else
		{ // ��l�̂�OFF�̏ꍇ

			// �ڕW�̒����_�̈ʒu���X�V
			g_aCamera[CAMERATYPE_MAIN].destPosR.x = pPlayer->pos.x + sinf(pPlayer->rot.y + D3DX_PI) * -POS_R_PLUS;	// �v���C���[�̈ʒu��菭���O
			g_aCamera[CAMERATYPE_MAIN].destPosR.y = pPlayer->pos.y + POS_R_PLUS_Y;									// �v���C���[�̈ʒu�Ɠ���
			g_aCamera[CAMERATYPE_MAIN].destPosR.z = pPlayer->pos.z + cosf(pPlayer->rot.y + D3DX_PI) * -POS_R_PLUS;	// �v���C���[�̈ʒu��菭���O

			// �ڕW�̎��_�̈ʒu���X�V
			g_aCamera[CAMERATYPE_MAIN].destPosV.x = g_aCamera[CAMERATYPE_MAIN].destPosR.x - ((g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * sinf(g_aCamera[CAMERATYPE_MAIN].rot.y));	// �ڕW�����_���狗�������ꂽ�ʒu
			g_aCamera[CAMERATYPE_MAIN].destPosV.y = POS_V_Y;																																						// �Œ�̍���
			g_aCamera[CAMERATYPE_MAIN].destPosV.z = g_aCamera[CAMERATYPE_MAIN].destPosR.z - ((g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * cosf(g_aCamera[CAMERATYPE_MAIN].rot.y));	// �ڕW�����_���狗�������ꂽ�ʒu

			// �ڕW�̈ʒu�܂ł̍������v�Z
			diffPosV = g_aCamera[CAMERATYPE_MAIN].destPosV - g_aCamera[CAMERATYPE_MAIN].posV;	// ���_
			diffPosR = g_aCamera[CAMERATYPE_MAIN].destPosR - g_aCamera[CAMERATYPE_MAIN].posR;	// �����_

			// ���_�̈ʒu���X�V
			g_aCamera[CAMERATYPE_MAIN].posV.x += diffPosV.x * REV_POS_V;
			g_aCamera[CAMERATYPE_MAIN].posV.y += diffPosV.y * REV_POS_V_Y;
			g_aCamera[CAMERATYPE_MAIN].posV.z += diffPosV.z * REV_POS_V;

			// �����_�̈ʒu���X�V
			g_aCamera[CAMERATYPE_MAIN].posR.x += diffPosR.x * REV_POS_R;
			g_aCamera[CAMERATYPE_MAIN].posR.y += diffPosR.y * REV_POS_R_Y;
			g_aCamera[CAMERATYPE_MAIN].posR.z += diffPosR.z * REV_POS_R;
		}

		break;							//�����o��
	}

	// �J�����̌������v���C���[�̌����ɍ��킹��
	g_aCamera[CAMERATYPE_MAIN].rot.y = pPlayer->rot.y;
}
#endif

#if 0
//============================================================
//	���C���J�����̈ʒu�̍X�V���� (�Œ�)
//============================================================
void MoveFixedCamera(void)
{
	// �ϐ���錾
	D3DXVECTOR3 diffPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �J�����̒����_�̈ʒu�̌v�Z����p

	// �|�C���^��錾
	Police *pPolice = GetPoliceData();		// �x�@�̏��

	// �ڕW�̒����_�̈ʒu���X�V
	g_aCamera[CAMERATYPE_MAIN].destPosR.x = pPolice->pos.x + sinf(pPolice->rot.y + D3DX_PI) * POS_R_PLUS;	// �v���C���[�̈ʒu��菭���O
	g_aCamera[CAMERATYPE_MAIN].destPosR.y = pPolice->pos.y + POS_R_PLUS_Y;									// �v���C���[�̈ʒu�Ɠ���
	g_aCamera[CAMERATYPE_MAIN].destPosR.z = pPolice->pos.z + cosf(pPolice->rot.y + D3DX_PI) * POS_R_PLUS;	// �v���C���[�̈ʒu��菭���O

	// �ڕW�̒����_�ʒu�܂ł̍������v�Z
	diffPosR = g_aCamera[CAMERATYPE_MAIN].destPosR - g_aCamera[CAMERATYPE_MAIN].posR;

	// ���_�̈ʒu���Œ�
	g_aCamera[CAMERATYPE_MAIN].posV = D3DXVECTOR3(1800.0f, 800.0f, 1000.0f);

	// �����_�̈ʒu���X�V
	g_aCamera[CAMERATYPE_MAIN].posR.x += diffPosR.x * REV_POS_R;
	g_aCamera[CAMERATYPE_MAIN].posR.y += diffPosR.y * REV_POS_R_Y;
	g_aCamera[CAMERATYPE_MAIN].posR.z += diffPosR.z * REV_POS_R;
}
#endif

//============================================================
//	���C���J�����̈ʒu�̍X�V���� (����)
//============================================================
void MoveCamera(void)
{
	//--------------------------------------------------------
	//	�}�E�X����̍X�V
	//--------------------------------------------------------
	if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == true)
	{ // �E�N���b�N�ƍ��N���b�N��������Ă���ꍇ

		// ���_���ړ�
		g_aCamera[CAMERATYPE_MAIN].posV.x -= sinf(g_aCamera[CAMERATYPE_MAIN].rot.y + (D3DX_PI * 0.5f)) * GetMouseMove().x;
		g_aCamera[CAMERATYPE_MAIN].posV.z -= cosf(g_aCamera[CAMERATYPE_MAIN].rot.y + (D3DX_PI * 0.5f)) * GetMouseMove().x;

		g_aCamera[CAMERATYPE_MAIN].posV.x += sinf(g_aCamera[CAMERATYPE_MAIN].rot.y) * GetMouseMove().y;
		g_aCamera[CAMERATYPE_MAIN].posV.z += cosf(g_aCamera[CAMERATYPE_MAIN].rot.y) * GetMouseMove().y;

		// �����_���ړ�
		g_aCamera[CAMERATYPE_MAIN].posR.x -= sinf(g_aCamera[CAMERATYPE_MAIN].rot.y + (D3DX_PI * 0.5f)) * GetMouseMove().x;
		g_aCamera[CAMERATYPE_MAIN].posR.z -= cosf(g_aCamera[CAMERATYPE_MAIN].rot.y + (D3DX_PI * 0.5f)) * GetMouseMove().x;

		g_aCamera[CAMERATYPE_MAIN].posR.x += sinf(g_aCamera[CAMERATYPE_MAIN].rot.y) * GetMouseMove().y;
		g_aCamera[CAMERATYPE_MAIN].posR.z += cosf(g_aCamera[CAMERATYPE_MAIN].rot.y) * GetMouseMove().y;
	}
}

//============================================================
//	���C���J�����̋����̍X�V���� (����)
//============================================================
void DisCamera(void)
{
	//--------------------------------------------------------
	//	�}�E�X����̍X�V
	//--------------------------------------------------------
	if (GetMouseMove().z != 0.0f)
	{ // �}�E�X�z�C�[���̈ړ��ʂ� 0.0f �ł͂Ȃ��ꍇ

		// �}�E�X�� z�ړ��ʂ̕����Ɏ��_���ړ�
		g_aCamera[CAMERATYPE_MAIN].fDis += GetMouseMove().z * REV_DIS_MOUSE;
	}

	//--------------------------------------------------------
	//	�����̕␳
	//--------------------------------------------------------
	if (g_aCamera[CAMERATYPE_MAIN].fDis > REV_DIS)
	{ // �Œ዗�����������ꍇ

		// �Œ዗���ɕ␳
		g_aCamera[CAMERATYPE_MAIN].fDis = REV_DIS;
	}
}

//============================================================
//	���C���J�����̌����̍X�V���� (����)
//============================================================
void RotCamera(void)
{
	//--------------------------------------------------------
	//	�}�E�X����̍X�V
	//--------------------------------------------------------
	if (GetMousePress(PUSH_LEFT) == true && GetMousePress(PUSH_RIGHT) == false)
	{ // ���N���b�N������������Ă���ꍇ

		// �}�E�X�� x�ړ��ʂ̕����� y������]
		g_aCamera[CAMERATYPE_MAIN].rot.y += GetMouseMove().x * REV_ROT_MOUSE;

		// �}�E�X�� y�ړ��ʂ̕����� x������]
		g_aCamera[CAMERATYPE_MAIN].rot.x += GetMouseMove().y * REV_ROT_MOUSE;
	}

	//--------------------------------------------------------
	//	�����̕␳
	//--------------------------------------------------------
	// �����̕␳ (x)
	RevRotXCamera();

	// �����̕␳ (y)
	RevRotYCamera();

	//--------------------------------------------------------
	//	���_�̍X�V
	//--------------------------------------------------------
	g_aCamera[CAMERATYPE_MAIN].posV.x = g_aCamera[CAMERATYPE_MAIN].posR.x + ((g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * sinf(g_aCamera[CAMERATYPE_MAIN].rot.y));
	g_aCamera[CAMERATYPE_MAIN].posV.y = g_aCamera[CAMERATYPE_MAIN].posR.y + ((g_aCamera[CAMERATYPE_MAIN].fDis * cosf(g_aCamera[CAMERATYPE_MAIN].rot.x)));
	g_aCamera[CAMERATYPE_MAIN].posV.z = g_aCamera[CAMERATYPE_MAIN].posR.z + ((g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * cosf(g_aCamera[CAMERATYPE_MAIN].rot.y));

	//--------------------------------------------------------
	//	�}�E�X����̍X�V
	//--------------------------------------------------------
	if (GetMousePress(PUSH_RIGHT) == true && GetMousePress(PUSH_LEFT) == false)
	{ // �E�N���b�N������������Ă���ꍇ

		// �}�E�X�� x�ړ��ʂ̕����� y������]
		g_aCamera[CAMERATYPE_MAIN].rot.y += GetMouseMove().x * REV_ROT_MOUSE;

		// �}�E�X�� y�ړ��ʂ̕����� x������]
		g_aCamera[CAMERATYPE_MAIN].rot.x += GetMouseMove().y * REV_ROT_MOUSE;
	}

	//--------------------------------------------------------
	//	�����̕␳
	//--------------------------------------------------------
	// �����̕␳ (x)
	RevRotXCamera();

	// �����̕␳ (y)
	RevRotYCamera();

	//--------------------------------------------------------
	//	�����_�̍X�V
	//--------------------------------------------------------
	g_aCamera[CAMERATYPE_MAIN].posR.x = g_aCamera[CAMERATYPE_MAIN].posV.x + ((-g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * sinf(g_aCamera[CAMERATYPE_MAIN].rot.y));
	g_aCamera[CAMERATYPE_MAIN].posR.y = g_aCamera[CAMERATYPE_MAIN].posV.y + ((-g_aCamera[CAMERATYPE_MAIN].fDis * cosf(g_aCamera[CAMERATYPE_MAIN].rot.x)));
	g_aCamera[CAMERATYPE_MAIN].posR.z = g_aCamera[CAMERATYPE_MAIN].posV.z + ((-g_aCamera[CAMERATYPE_MAIN].fDis * sinf(g_aCamera[CAMERATYPE_MAIN].rot.x)) * cosf(g_aCamera[CAMERATYPE_MAIN].rot.y));
}

//============================================================
//	�J�����̌����̕␳���� (x)
//============================================================
void RevRotXCamera(void)
{
	if (g_aCamera[CAMERATYPE_MAIN].rot.x > LIMIT_ROT_HIGH)
	{ // ��]�� (x) �� LIMIT_ROT_HIGH �𒴂����ꍇ

		// LIMIT_ROT_HIGH ���� (����)
		g_aCamera[CAMERATYPE_MAIN].rot.x = LIMIT_ROT_HIGH;
	}
	else if (g_aCamera[CAMERATYPE_MAIN].rot.x < LIMIT_ROT_LOW)
	{ // ��]�� (x) �� LIMIT_ROT_LOW �𒴂����ꍇ

		// LIMIT_ROT_LOW ���� (����)
		g_aCamera[CAMERATYPE_MAIN].rot.x = LIMIT_ROT_LOW;
	}
}

//============================================================
//	�J�����̌����̕␳���� (y)
//============================================================
void RevRotYCamera(void)
{
	if (g_aCamera[CAMERATYPE_MAIN].rot.y > D3DX_PI)
	{ // ��]�� (y) �� D3DX_PI �𒴂����ꍇ

		// D3DX_PI���� (����)
		g_aCamera[CAMERATYPE_MAIN].rot.y = D3DX_PI;

		// ��]�� (y) �𔽓]������
		g_aCamera[CAMERATYPE_MAIN].rot.y *= -1.0f;
	}
	else if (g_aCamera[CAMERATYPE_MAIN].rot.y < -D3DX_PI)
	{ // ��]�� (y) �� -D3DX_PI �𒴂����ꍇ

		// -D3DX_PI���� (����)
		g_aCamera[CAMERATYPE_MAIN].rot.y = -D3DX_PI;

		// ��]�� (y) �𔽓]������
		g_aCamera[CAMERATYPE_MAIN].rot.y *= -1.0f;
	}
}

//============================================================
//	�J�����̎擾����
//============================================================
Camera *GetCamera(int nID)
{
	// �J�����̏��̈����̗v�f�̃A�h���X��Ԃ�
	return &g_aCamera[nID];
}

#ifdef _DEBUG	// �f�o�b�O����
//============================================================
//	�f�o�b�O�����ꗗ
//============================================================
//************************************************************
//	���_���W�̎擾����
//************************************************************
D3DXVECTOR3 GetCameraPosV(void)
{
	// ���_���W��Ԃ�
	return g_aCamera[CAMERATYPE_MAIN].posV;
}

//************************************************************
//	�����_���W�̎擾����
//************************************************************
D3DXVECTOR3 GetCameraPosR(void)
{
	// �����_���W��Ԃ�
	return g_aCamera[CAMERATYPE_MAIN].posR;
}

//************************************************************
//	�����̎擾����
//************************************************************
D3DXVECTOR3 GetCameraRot(void)
{
	// ������Ԃ�
	return g_aCamera[CAMERATYPE_MAIN].rot;
}

//************************************************************
//	�����̎擾����
//************************************************************
float GetCameraDis(void)
{
	// ������Ԃ�
	return g_aCamera[CAMERATYPE_MAIN].fDis;
}
#endif