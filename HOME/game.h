#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include"main.h"

typedef enum
{
	GAMESTATE_NONE=0,//�������Ă��Ȃ����
	GAMESTATE_NORMAL,//�ʏ���
	GAMESTATE_END,//�ʏ���
	GAMESTATE_MAX
}GAMESTATE;
//�v���g�^�C�v�錾
void InitGame(void);//�Q�[���̏���������
void UninitGame(void);//�Q�[���̏I������
void UpdateGame(void);//�Q�[���̍X�V����
void DrawGame(void);//�Q�[���̕`�揈��
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
#endif