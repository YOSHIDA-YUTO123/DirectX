#include "main.h"
#include "player.h"
#include "input.h"
#include"bullet.h"
#include"enemy.h"
#include"explosion.h"
#include"fade.h"
#include"effect.h"

//�O���[�o���ϐ��錾

LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//�e�N�X�`���ւ̃|�C���^//�m�[�g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//���_�o�b�t�@�ւ̃|�C���^
Player g_player;//�v���C���[�̏��

int g_nCounterAnimPlayer = 0; //�A�j���[�V�����J�E���^�[
int g_nPatternAnimPlayer = 0; //�A�j���[�V�����p�^�[��No.

D3DXVECTOR3 g_posPlayer;//�ʒu
D3DXVECTOR3 g_movePlayer;//�ړ���
D3DXVECTOR3 g_rotPlayer;//����
float g_fLengthPlayer;//�Ίp���̒���
float g_fAnglePlayer;//�Ίp���̊p�x


//�v���C���[�̏���������
void InitPlayer(void)
{
	VERTEX_2D* pVtx;//���_���W�ւ̃|�C���^

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏K��
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player.png",
		&g_pTexturePlayer);

	g_nCounterAnimPlayer = 0;//�J�E���^�[������������
	g_nPatternAnimPlayer = 0;//�J�E���^�[������������
	g_posPlayer = D3DXVECTOR3(PLAYER_WIDTH,PLAYER_HEIGHT,0.0f);//�ʒu������������
	g_movePlayer = D3DXVECTOR3(0.0f,0.0f,0.0f);//�ړ��ʂ�����������
	g_rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����������������
	g_player.nCounterState = 0;
	g_player.bDisp = true;
	g_player.nLife = 3;

	//�Ίp���̒������Z�o����
	g_fLengthPlayer = sqrtf((PLAYER_WIDTH*PLAYER_WIDTH)+(PLAYER_HEIGHT*PLAYER_HEIGHT))/2.0f;

	//�Ίp���̊p�x���Z�o����
	g_fAnglePlayer = atan2f(PLAYER_WIDTH,PLAYER_HEIGHT);

	//���_���W�̐ݒ�
	pVtx[0].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[0].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[0].Pos.z = 0.0f;

	//���_���W�̐ݒ�
	pVtx[1].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + (D3DX_PI - g_fAnglePlayer)) *g_fLengthPlayer;
	pVtx[1].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + (D3DX_PI - g_fAnglePlayer)) *g_fLengthPlayer;
	pVtx[1].Pos.z = 0.0f;

	//���_���W�̐ݒ�
	pVtx[2].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].Pos.z = 0.0f;

	//���_���W�̐ݒ�
	pVtx[3].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[3].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[3].Pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffPlayer->Unlock();
}
//�v���C���[�̏I������
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//�v���C���[�̍X�V����
void UpdatePlayer(void)
{
	XINPUT_STATE* pStick;
	pStick = GetJoySticAngle();
	VERTEX_2D* pVtx;//���_���W�ւ̃|�C���^

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			g_player.state = PLAYERSTATE_NORMAL;
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

			g_pVtxBuffPlayer->Unlock();
		}
		break;

	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{
			//���[�h�ݒ�(���U���g��ʂɈړ�)
			/*SetMode(MODE_RESULT);*/

			return;
		}
		break;
	}
	
	static float fData = 0.2f;

	if (GetJoypadPress(JOYKEY_UP) == true)
	{//��L�[�������ꂽ
		g_posPlayer.y -= 1.0f;
		//���_���W�̍X�V
	}
	else if (GetJoypadPress(JOYKEY_DOWN) == true)
	{//���L�[�������ꂽ
		g_posPlayer.y += 1.0f;
		//���_���W�̍X�V
	}
	else if (GetJoypadPress(JOYKEY_RIGHT) == true)
	{//�E�L�[�������ꂽ
		g_posPlayer.x += 1.0f;
		//���_���W�̍X�V
	}
	else if (GetJoypadPress(JOYKEY_LEFT) == true)
	{//���L�[�������ꂽ
		g_posPlayer.x -= 1.0f;
		//���_���W�̍X�V
	}
	
	else if (GetJoypadPress(JOYKEY_BAKC) == true)
	{//�o�b�N�������ꂽ
		g_fLengthPlayer = 110.0f;
		g_rotPlayer.z = 0.0f;
		g_posPlayer.x = PLAYER_WIDTH;
		g_posPlayer.y = PLAYER_HEIGHT;
	}
	else if (GetJoypadPress(JOYKEY_LEFT_SHOULDER) == true)
	{//���g���K�[�������ꂽ
		g_rotPlayer.z += 0.04f;
	}
	else if (GetJoypadPress(JOYKEY_RIGHT_SHOULDER) == true)
	{//�E�g���K�[�������ꂽ
		g_rotPlayer.z -= 0.04f;
	}
	else if (GetJoypadPress(JOYKEY_A) == true)
	{//A�{�^���������ꂽ
		SetEnemy(D3DXVECTOR3(100.0f, 100.0f, 0.0f), 0);
	}
	else if (GetJoypadPress(JOYKEY_B) == true)
	{//B�{�^���������ꂽ
		if (g_fLengthPlayer > 0)
		{
			g_fLengthPlayer -= 0.5f;
		}
	}
	else if (GetJoyTrigger(JOYKEY_X) == true)
	{//X�{�^���������ꂽ
		//�e�̐ݒ�
		SetBullet(g_posPlayer, D3DXVECTOR3(sinf(g_rotPlayer.z + D3DX_PI) * 10.0f, cosf(g_rotPlayer.z + D3DX_PI) * 10.0f, 0.0f), 1, BULLETTYPE_PLAYER);
	}
	else if (GetJoypadPress(JOYKEY_Y) == true)
	{//Y�{�^���������ꂽ
		if (g_fLengthPlayer < 300.0f)
		{
			g_fLengthPlayer += 0.5f;
		}
	}
	if (GetKeyboardPress(DIK_A) == true)
	{//A�L�[�������ꂽ
		fData = 0.2f;

		if (GetKeyboardPress(DIK_W) == true)
		{//W�L�[�������ꂽ
			//��ړ�
			g_movePlayer.x += sinf(-D3DX_PI * 0.75f) * 0.5f;
			g_movePlayer.y += cosf(-D3DX_PI * 0.75f) * 0.5f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//S�L�[�������ꂽ
			//���ړ�
			g_movePlayer.x += sinf(-D3DX_PI*0.25f) * 0.5f;
			g_movePlayer.y += cosf(-D3DX_PI*0.25f) * 0.5f;
		}
		else
		{
			//���ړ�
			g_movePlayer.x -= 0.5f;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//D�L�[�������ꂽ	
		fData = -0.2f;
		if (GetKeyboardPress(DIK_W) == true)
		{//W�L�[�������ꂽ
			//��ړ�
			g_movePlayer.x += sinf(D3DX_PI * 0.75f) * 0.5f;
			g_movePlayer.y += cosf(D3DX_PI * 0.75f) * 0.5f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//S�L�[�������ꂽ
			//���ړ�
			g_movePlayer.x += sinf(D3DX_PI * 0.25f) * 0.5f;
			g_movePlayer.y += cosf(D3DX_PI * 0.25f) * 0.5f;
		}
		else
		{
			//�E�ړ�
			g_movePlayer.x += 0.5f;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{//W�L�[�������ꂽ
		//��ړ�
		g_movePlayer.y -= 0.5f;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//S�L�[�������ꂽ
		//���ړ�
		g_movePlayer.y += 0.5f;
	}
	else if (GetKeyboardPress(DIK_Q) == true)//����]
	{
		g_rotPlayer.z += 0.04f;
	}
	else if (GetKeyboardPress(DIK_E) == true)//�E��]
	{
		g_rotPlayer.z -= 0.04f;
	}
	else if (GetKeyboardPress(DIK_F) == true)
	{
		if (g_fLengthPlayer < 300.0f)
		{
			g_fLengthPlayer += 0.5f;
		}
	}
	else if (GetKeyboardPress(DIK_G) == true)
	{
		if (g_fLengthPlayer > 0)
		{
			g_fLengthPlayer -= 0.5f;
		}
	}
	else if (GetKeyboardPress(DIK_V) == true)//���Z�b�g
	{
		g_fLengthPlayer = 110.0f;
		g_rotPlayer.z = 0.0f;
		g_posPlayer.x = PLAYER_WIDTH;
		g_posPlayer.y = PLAYER_HEIGHT;
	}
	else if (GetJoyStick() == true)
	{
		if (pStick->Gamepad.sThumbLX > 10922)
		{//�E�ړ�
			g_player.move.x += 0.5;
		}
		else if (pStick->Gamepad.sThumbLX < -10922)
		{//���ړ�
			g_player.move.x -= 0.5;
		}
		else if (pStick->Gamepad.sThumbLY > 10922)
		{//��ړ�
			g_player.move.y -= 0.5;
		}
		else if (pStick->Gamepad.sThumbLY < -10922)
		{//���ړ�
			g_player.move.y += 0.5;
		}
	}
	/*else if (KeyboardTrigger(DIK_T) == true)
	{
		SetEnemy(D3DXVECTOR3(100.0f, 100.0f, 0.0f), 0);
	}*/
	if (KeyboardTrigger(DIK_SPACE) == true)
	{//SPACE�L�[�������ꂽ
		
		//�e�̐ݒ�
		SetBullet(g_posPlayer,D3DXVECTOR3(sinf(g_rotPlayer.z+D3DX_PI)*10.0f,cosf(g_rotPlayer.z+D3DX_PI)*10.0f,0.0f),1,BULLETTYPE_PLAYER);
	}


	//�ʒu���X�V
	g_posPlayer.x += g_movePlayer.x;
	g_posPlayer.y += g_movePlayer.y;

	//�ړ��ʂ�����
	g_movePlayer.x += (0.0f - g_movePlayer.x) * 0.1f;
	g_movePlayer.y += (0.0f - g_movePlayer.y) * 0.1f;

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].Pos.z = 0.0f;

	//���_���W�̐ݒ�
	pVtx[1].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - (D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - (D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].Pos.z = 0.0f;

	//���_���W�̐ݒ�
	pVtx[2].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].Pos.z = 0.0f;

	//���_���W�̐ݒ�
	pVtx[3].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[3].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[3].Pos.z = 0.0f;

	g_pVtxBuffPlayer->Unlock();
	//g_nCounterAnimPlayer++;//�J�E���^�[�����Z

	//if (g_nCounterAnimPlayer >1)
	//{
	//	g_nCounterAnimPlayer = 0;//�p�^�[��No.�������l�ɖ߂�
	//	g_nPatternAnimPlayer++;//�p�^�[��No.���X�V����

	//	if (g_nPatternAnimPlayer >= 10)
	//	{
	//		g_nPatternAnimPlayer = 0;//�p�^�[��No.�������l�ɖ߂�
	//	}

	

	//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//	//�A�j���[�V����
	//	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f);
	//	pVtx[1].tex = D3DXVECTOR2(fData+g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f);
	//	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f + 0.5f);
	//	pVtx[3].tex = D3DXVECTOR2(fData+g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f + 0.5f);

	//	//���_�o�b�t�@���A�����b�N����
	//	g_pVtxBuffPlayer->Unlock();
	//}
}
//�v���C���[�̕`�揈��
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏K��
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//�v���~�e�B�u�̎��
	}
}
//�v���C���[�̎擾
Player* GetPlayer(void)
{
	return &g_player;
}
//�v���C���[�̃q�b�g����
void HitPlayer(int nDamage)
{
	VERTEX_2D* pVtx;
	
	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)//�v���C���[�̗̑͂��Ȃ��Ȃ���
	{
		//�����̐ݒ�
		SetExplosion(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255));

		g_player.bDisp = false;

		g_player.state = PLAYERSTATE_DEATH;

		g_player.nCounterState = 60;
	}
	else
	{
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 10;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		g_pVtxBuffPlayer->Unlock();
	}
	
}