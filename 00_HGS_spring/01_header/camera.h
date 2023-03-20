//======================================================================================================================
//
//	�J�����w�b�_�[ [camera.h]
//	Author�F���c�E��
//
//======================================================================================================================
#ifndef _CAMERA_H_					// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _CAMERA_H_					// ��d�C���N���[�h�h�~�̃}�N�����`����

//**********************************************************************************************************************
//	�}�N����`
//**********************************************************************************************************************
#define CNT_ROT_FOLLOW	(50)		// �Ǐ]���̉�荞�݂��n�܂�J�E���^�[�̒l
#define VIEW_ANGLE		(D3DXToRadian(65.0f))	// ����p

#define POS_R_PLUS		(25.0f)		// �v���C���[�̈ʒu�ƒ����_�̈ʒu�̋��� (x, z)
#define POS_R_PLUS_Y	(180.0f)	// �v���C���[�̈ʒu�ƒ����_�̈ʒu�̋��� (y)
#define POS_V_Y			(200.0f)	// �Ǐ]���̎��_�̈ʒu (y)

// �}�b�v�J����
#define MAPCAM_POS_R	(0.0f)		// �}�b�v�J�����̒����_�̈ʒu (y)
#define MAPCAM_POS_V	(6000.0f)	// �}�b�v�J�����̎��_�̈ʒu (y)
#define MAPCAM_X		(980)		// �}�b�v�J�����̍�����̃s�N�Z�����W (x)
#define MAPCAM_Y		(72)		// �}�b�v�J�����̍�����̃s�N�Z�����W (y)
#define MAPCAM_SIZE_X	(220)		// �}�b�v�J�����̕`�悷���ʂ̉���
#define MAPCAM_SIZE_Y	(210)		// �}�b�v�J�����̕`�悷���ʂ̏c��

//**********************************************************************************************************************
//	�񋓌^��` (CAMERATYPE)
//**********************************************************************************************************************
typedef enum
{
	CAMERATYPE_MAIN = 0,			// ���C���J����
	CAMERATYPE_MAP,					// �~�j�}�b�v�J����
	CAMERATYPE_UI,					// UI�J����
	CAMERATYPE_MAX,					// ���̗񋓌^�̑���
} CAMERATYPE;

//**********************************************************************************************************************
//	�\���̒�` (Camera)
//**********************************************************************************************************************
typedef struct
{
	D3DXVECTOR3  posV;				// ���݂̎��_
	D3DXVECTOR3  posVOld;			// �O��̎��_
	D3DXVECTOR3  posR;				// ���݂̒����_
	D3DXVECTOR3  destPosV;			// �ڕW�̎��_
	D3DXVECTOR3  destPosR;			// �ڕW�̒����_
	D3DXVECTOR3  vecU;				// ������x�N�g��
	D3DXVECTOR3  rot;				// ����
	float        fDis;				// ���_�ƒ����_�̋���
	D3DXMATRIX   mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX   mtxView;			// �r���[�}�g���b�N�X
	D3DVIEWPORT9 viewport;			// �r���[�|�[�g
} Camera;

//**********************************************************************************************************************
//	�v���g�^�C�v�錾
//**********************************************************************************************************************
void InitCamera(void);				// �J�����̏���������
void UninitCamera(void);			// �J�����̏I������
void UpdateCamera(void);			// �J�����̍X�V����
void SetCamera(int nID);			// �J�����̐ݒ菈��
Camera *GetCamera(int nID);			// �J�����̎擾����

//**********************************************************************************************************************
//	�v���g�^�C�v�錾 (�f�o�b�O�p)
//**********************************************************************************************************************
D3DXVECTOR3 GetCameraPosV(void);	// ���_���W�̎擾����
D3DXVECTOR3 GetCameraPosR(void);	// �����_���W�̎擾����
D3DXVECTOR3 GetCameraRot(void);		// �����̎擾����
float GetCameraDis(void);			// �����̎擾����

#endif