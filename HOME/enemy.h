#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//�}�N����`
#define MAX_ENEMY (128)//�G�̍ő吔
#define MAX_WIDTH (100)
#define MAX_HEIGHT (100)

//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,//�ʏ���
	ENEMYSTATE_DAMAGE,//�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�G���(�񋓌^)
typedef enum
{
	ENEMYTYPE_OWN=0,
	ENEMYTYPE_TWO,
	ENEMYTYPE_THREE,
	ENEMYTYPE_FOUR,
	ENEMYTYPE_FIVE,
	ENEMYTYPE_SIX,
	ENEMYTYPE_MAX
}ENEMYTYPE;

static const char* ENEMY_TEXTURE[ENEMYTYPE_MAX] =//�G�̃e�N�X�`���̐ݒ�
{
	"data\\TEXTURE\\Ene1.png",
	"data\\TEXTURE\\Ene2.jpeg",
	"data\\TEXTURE\\Ene3.jpg",
	"data\\TEXTURE\\monster.png",
};
//�G�\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	int nUnko;
	int nType;//���
	bool bUse;//�g�p���Ă��邩�ǂ���
	ENEMYSTATE state;//���
	int nCnterState;//��ԃJ�E���^�[
	int BulletCounter;
	int nLife;
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
Enemy* GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
int GetNumEnemy(void);

#endif