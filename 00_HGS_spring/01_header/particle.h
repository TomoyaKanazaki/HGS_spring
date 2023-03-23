#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//�p�[�e�B�N���\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�����ʒu
	D3DXVECTOR3 rot;	//�p�x
	D3DXCOLOR col;		//�F
	int nLife;			//����(��������)
	float nSize;		//����(��������)
	int nType;			//���	
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Particle;

//�v���g�^�C�v�錾
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, float nSize, int nType);
#endif
