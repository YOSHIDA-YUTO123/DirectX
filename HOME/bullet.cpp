#include"bullet.h"
#include"main.h"
#include"explosion.h"
#include"enemy.h"
#include"player.h"
#include"effect.h"

//�}�N����`
#define MAX_BULLET (128)//�ʂ̍ő吔

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	float fRadius;
	int nLife;
	BULLETTYPE type;
	bool bUse;
}Bullet;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];//�e�̏��

void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//�e�̏���������
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 25;
		g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}
		
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4�����₷
	}
	g_pVtxBuffBullet->Unlock();
}
//�e�̏I������
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
void UpdateBullet(void)
{
	VERTEX_2D* pVtx{};

	int nCntBullet;

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�e�̈ʒu�̍X�V
		g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
		g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;

		//���_���W�̐ݒ�
		pVtx[0].Pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y - 30.0f, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y - 30.0f, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y + 30.0f, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y + 30.0f, 0.0f);

		g_aBullet[nCntBullet].nLife--;

		if (0 >= g_aBullet[nCntBullet].pos.x >= SCREEN_WIDTH || 0 >= g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT)//�e����ʊO�ɏo��
		{
			g_aBullet[nCntBullet].bUse = false;//�g�p���Ȃ����
		}
		//�����J�E���g�_�E��
		if (g_aBullet[nCntBullet].nLife <= 0)//�����s����
		{
			//�����̐ݒ�
			SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ����
		}

		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
				
				int nCntEnemy;

				//�G�̎擾
				Enemy* pEnemy = GetEnemy();

				if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
				{
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50.0f, 50);

					for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
					{
						if (pEnemy->bUse == true)
						{//�G���g�p����Ă���

							if (g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + MAX_WIDTH *1.0f
								&& g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - MAX_WIDTH * 0.15f
								&& g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + MAX_HEIGHT * 0.55f
								&& g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - MAX_HEIGHT * 0.6f
								)
							{
								HitEnemy(nCntEnemy,1);

								//�����̐ݒ�
								SetExplosion(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255));

								/*pEnemy->bUse = false;*/

								g_aBullet[nCntBullet].bUse = false;
							}
						}
						pEnemy++;
					}
				}
				//�v���C���[
				else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
				{//�G�̒e
					Player* pPlayer = GetPlayer();
					if (pPlayer->bDisp == true)
					{
						if (g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + MAX_WIDTH * 0.5f
							&& g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - MAX_WIDTH * 0.5f
							&& g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + MAX_HEIGHT * 0.5f
							&& g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - MAX_HEIGHT * 0.5f
							)
						{
							HitPlayer(1);

							//�����̐ݒ�
							SetExplosion(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255));

							pPlayer->bDisp = false;
							g_aBullet[nCntBullet].bUse= false;
						}
					}
				}
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}
//�e�̕`�揈��
void DrawBullet(void)
{
	int nCntBullet;

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏K��
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
			//�|���S���̕`��
			pDevice->SetTexture(0, g_pTextureBullet);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBullet* 4, 2);//�v���~�e�B�u�̎��
		}
	}
}
//�e�̐ݒ菈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	VERTEX_2D* pVtx;

	int nCntBullet;

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 25;
			g_aBullet[nCntBullet].bUse = true;
			g_aBullet[nCntBullet].type = type;
	
			//���_���W�̐ݒ�
			pVtx[0].Pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y - 30.0f, 0.0f);
			pVtx[1].Pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y - 30.0f, 0.0f);
			pVtx[2].Pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y + 30.0f, 0.0f);
			pVtx[3].Pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y + 30.0f, 0.0f);

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}
