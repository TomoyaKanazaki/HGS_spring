#ifndef _BULLET_H_
#define _BULLET_H_

#define MAX_BULLET (256)		//�e�̍ő吔

//���f���̍\����
typedef enum
{
	BULLET_NORMAL = 0,
	BULLET_MIRROR,
	BULLET_MAX,

}BULLET_TYPE;

//�r���{�[�h�\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 posOld;							//�ʒu
	D3DXVECTOR3 move;							//�ʒu
	D3DXMATRIX mtxWorld;						//���[���h�}�g���b�N�X
	BULLET_TYPE nType;						//�e�̎��
	float rot;									//����
	int nLife;									//����
	int nEffectCounter;							//�G�t�F�N�g���Z�b�g����Ԋu
	int nIndex;
	bool bUse;									//�g�p���Ă��邩�ǂ���
}Bullet;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, float rot, int nLife, BULLET_TYPE Type);
D3DXVECTOR3 GETAAA(void);
Bullet * GetBullet(void);
#endif