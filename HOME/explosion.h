#pragma once
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//�v���g�^�C�v�錾
void InitExplosion(void);//�����̏���������
void UninitExplosion(void);//�����̏I������
void UpdateExplosion(void);//�����̍X�V����
void DrawExplosion(void);//�����̕`�揈��
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);//�����̐ݒ菈��

#endif