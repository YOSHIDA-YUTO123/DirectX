#include "main.h"
#include"player.h"
#include"background.h"
#include"input.h"
#include"bullet.h"
#include"explosion.h"
#include"enemy.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"fade.h"
#include"effect.h"
#include"Score.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;//�Q�[���̏��
int g_nCounterGameState = 0;//��ԊǗ��J�E���^�[

//�Q�[����ʂ̏���������
void InitGame(void)
{
	//�w�i�̏���������
	InitBackground();

	//�v���C���[�̏���������
	InitPlayer();

	InitBullet();

	InitExplosion();

	InitEffect();

	//�G�̏���������
	InitEnemy();

	InitScore();

	SetEnemy(D3DXVECTOR3(500.0f, 150.0f, 0.0f), 0);

	g_gameState = GAMESTATE_NORMAL;//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
}
void UninitGame(void)
{
	//�w�i�̏I������
	UninitBackground();

	//�v���C���[�̏I������
	UninitPlayer();

	//�e�̏I������
	UninitBullet();

	UninitEnemy();

	UninitExplosion();

	UninitEffect();

	UninitScore();
}
//�Q�[����ʂ̍X�V����
void UpdateGame(void)
{
	//�w�i�̍X�V����
	UpdateBackground();

	//�v���C���[�̍X�V����
	UpdatePlayer();

	UpdateBullet();

	UpdateEnemy();

	UpdateExplosion();

	UpdateEffect();

	UpdateScore();

	int Num = GetNumEnemy();

	Enemy* Enemy = GetEnemy();

	if (Num <= 0)
	{
		g_gameState = GAMESTATE_END;
	}
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL://�ʏ���
		break;

	case GAMESTATE_END://�I�����
		g_nCounterGameState++;

		if (g_nCounterGameState >= 60)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ����

			//���(���[�h)�̐ݒ�
			SetFade(MODE_RESULT);
		}
		break;
	}
	//if (?)//�G�S��||�v���C���[��||�^�C���I�[�o�[
	//{
	//	
	//}
}
void DrawGame(void)
{
	DrawBackground();

	DrawEnemy();

	DrawExplosion();

	DrawPlayer();

	DrawBullet();

	DrawEffect();

	DrawScore();
}
//�Q�[���̏�Ԃ̐ݒ�
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	g_nCounterGameState = 0;
}

//�Q�[���̏�Ԃ̎擾
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
