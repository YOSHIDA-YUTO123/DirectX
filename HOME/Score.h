#ifndef _SCORE_H_
#define _SCORE_H_

#include"main.h"

//�v���g�^�C�v�錾
int ScoreCounter(int nScore);
void InitScore(void);//�X�R�A�[�̏���������
void UninitScore(void);//�X�R�A�[�̏I������
void UpdateScore(void);//�X�R�A�[�̍X�V����
void DrawScore(void);//�X�R�A�[�̕`�揈��
void SetScore(int nScore);
void AddScore(int nValue);
#endif
