#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//�o�����
	PLAYERSTATE_NORMAL,//�ʏ���
	PLAYERSTATE_DAMAGE,//�_���[�W���
	PLAYERSTATE_DEATH,//���S���
	PLAYERSTATE_MAX
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 move;//�ړ���
	PLAYERSTATE state;//�v���C���[�̏��
	int nCounterState;//��ԊǗ��J�E���^�[
	int nLife;//�̗�
	bool bDisp;//�\�����邩���Ȃ���
	bool bUse;
}Player;

void InitPlayer(void);//�v���C���[�̏���������
void UninitPlayer(void);//�v���C���[�̏I������
void UpdatePlayer(void);//�v���C���[�̍X�V����
void DrawPlayer(void);//�v���C���[�̕`�揈��
Player* GetPlayer(void);
void HitPlayer(int nDamage);
#endif
