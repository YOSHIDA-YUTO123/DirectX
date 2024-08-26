#include"enemy.h"
#include"bullet.h"
#include"main.h"

//�}�N����`
#define NUM_ENEMY (4)//�G�̎��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];//�G�̏��
int g_nNumEnemy = 0;//�G�̑���

//�G�̏���������
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X���擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;

	//�e�N�X�`��(�S����)�̓ǂݍ���
	
	for (int nCnt = 0; nCnt < ENEMYTYPE_MAX; nCnt++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			ENEMY_TEXTURE[nCnt],
			&g_apTextureEnemy[nCnt]);
	}

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//������
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy]. move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].state = {};
		g_aEnemy[nCntEnemy].nCnterState = 0;
		g_aEnemy[nCntEnemy].nLife = 5;
		g_aEnemy[nCntEnemy].nType =4;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].BulletCounter = 0;
	}
	g_nNumEnemy = 0;
	
	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		g_aEnemy[NUM_ENEMY].pos = D3DXVECTOR3(500.0f, 150.0f, 0.0f);

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
	g_pVtxBuffEnemy->Unlock();
}
//�G�̏I������
void UninitEnemy(void)
{
	int nCntEnemy;

	//�e�N�X�`���̔j��
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].BulletCounter++;
			if (g_aEnemy[nCntEnemy].BulletCounter == 50)
			{
				SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 25.0f, 0.0f), 100, BULLETTYPE_ENEMY);
				g_aEnemy[nCntEnemy].BulletCounter=0;
			}
			switch (g_aEnemy[nCntEnemy].state)
			{
				case ENEMYSTATE_NORMAL:
	
					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//g_aEnemy[nCntEnemy].BulletCounter++;
					//if (g_aEnemy[nCntEnemy].BulletCounter == 3)//��莞�Ԍo��
					//{
					//	g_aEnemy[nCntEnemy].BulletCounter = 0;
					//}
					break;

				case ENEMYSTATE_DAMAGE:
				
					g_aEnemy[nCntEnemy].nCnterState--;

					if (g_aEnemy[nCntEnemy].nCnterState <= 0)
					{
						////���_�o�b�t�@�̃��b�N
						//g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

						g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
						//���_�J���[�̐ݒ�
						
						//pVtx += 4 * nCntEnemy;

						//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						////���_�o�b�t�@���A�����b�N����
						//g_pVtxBuffEnemy->Unlock();			
					}
					break;
			}
		}
	}
	g_pVtxBuffEnemy->Unlock();
}
//�G�̕`�揈��
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[nCntEnemy]);
		}
	}
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//�G(�|���S��)�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}
//�G�̐ݒ菈��
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D* pVtx;

	int nCntEnemy;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//�G���g�p����Ă��Ȃ�

			//�G�̏��̐ݒ�
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = 5;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCnterState = 0;
			g_aEnemy[nCntEnemy].BulletCounter = 0;
			g_aEnemy[nCntEnemy].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].Pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x , g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
			pVtx[1].Pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 100.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
			pVtx[2].Pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x , g_aEnemy[nCntEnemy].pos.y + 30.0f, 0.0f);
			pVtx[3].Pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 100.0f, g_aEnemy[nCntEnemy].pos.y + 30.0f, 0.0f);

			g_nNumEnemy++;

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffEnemy->Unlock();
}
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D* pVtx=0;
	
	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife<=0)//�G�̗̑͂��Ȃ��Ȃ���
	{
		//�����̐ݒ�
		g_aEnemy[nCntEnemy].bUse = false;

		g_nNumEnemy--;
	}
	else
	{
		//���_�o�b�t�@�̃��b�N
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCnterState = 5;

		pVtx += 4 * nCntEnemy;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		g_pVtxBuffEnemy->Unlock();
	}
}
int GetNumEnemy(void)
{
	return g_nNumEnemy;
}
