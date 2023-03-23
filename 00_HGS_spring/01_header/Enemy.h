#ifndef _ENEMY_H_
#define _ENEMY_H_

#define MAX_ENEMY (2048)		//�I�u�W�F�N�g�̍ő吔

//���f���̍\����
typedef enum
{
	ENEMY_STATE_WAIT = 0,
	ENEMY_STATE_BATTLE,
	ENEMY_STATE_MAX,

}ENEMY_STATE;

//���f���̍\����
typedef enum
{
	ENEMY_NTYPE00 = 0,
	ENEMY_NTYPE01,
	ENEMY_MAX,

}ENEMY_NTYPE;

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;							//���݂̈ʒu
	D3DXVECTOR3 posOld;							//�ߋ��̈ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 rot;							//����
	D3DXMATRIX mtxWorld;						//���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMin;							//���f���̍ŏ�
	D3DXVECTOR3 vtxMax;							//���f���̍ő�
	D3DXVECTOR3 size; //�傫��
	int nType;							//���f���̎��
	ENEMY_STATE State;							//�G�̏��
	int BulletCounter;							//��C�̃J�E���^�[
	float fRadius; //���a
	bool bUse;									//���f�����g�p����Ă��邩�ǂ���
	D3DXMATERIAL pMatD;							//�}�e���A���f�[�^�ւ̃|�C���^
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void RotEnemy(D3DXVECTOR3 Pos, int nCnt);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 min, D3DXVECTOR3 max);
void KnoccBackPlayer(D3DXVECTOR3 Pos, float Power);
bool CollisionCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut, float nRadiusIn, float MinY, float MaxY);
Enemy * GetEnemy(void);
bool GetHit(void);

#endif