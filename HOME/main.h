#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_
#include<windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)//�r���h���̌x���Ώ��}�N��
#include "dinput.h"
#include"Xinput.h"
#include"xaudio2.h"

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")//DirectX�R���|�l�[�V����(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")//�W���C�p�b�h�����ɕK�v

//�}�N����`
#define CLASS_NAME "WindowClass" //�E�C���h�E�N���X�̖��O
#define WINDOW_NAME "DirectX�̊�{����" //�E�C���h�E�̖��O(�L���v�V�����ɕ\��)
#define SCREEN_WIDTH (1280) //�E�C���h�E�̕�
#define SCREEN_HEIGHT (720) //�E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define PLAYER_WIDTH (200.0f)//��
#define PLAYER_HEIGHT (100.0f)//����


typedef struct
{
	D3DXVECTOR3 Pos; //���_���W
	float rhw;       //���W�ԊҌW��(1.0f�Ŏw��)
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_2D;

typedef enum
{
	MODE_TITLE = 0, //�^�C�g�����
	MODE_GAME,//�Q�[�����
	MODE_RESULT,//���U���g���
	MODE_MAX
}MODE;

typedef enum
{
	JOYKEY_UP=0,//�\���L�[��
	JOYKEY_DOWN,//�\���L�[��
	JOYKEY_LEFT,//�\���L�[��
	JOYKEY_RIGHT,//�\���L�[�E
	JOYKEY_START,//START
	JOYKEY_BAKC,//BACK
	JOYKEY_LEFT_THUMB,
	JOYKEY_RIGHT_THUMB,
	JOYKEY_LEFT_SHOULDER,//���g���K�[
	JOYKEY_RIGHT_SHOULDER,//�E�g���K�[
	JOYKEY_L2,
	JOYKEY_R2,
	JOYKEY_A,//A�{�^��
	JOYKEY_B,//B�{�^��
	JOYKEY_X,//X�{�^��
	JOYKEY_Y,//Y�{�^��
	
	
	JOYKEY_MAX

}JOYKEY;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif
