#include"explosion.h"
#include"main.h"

//�}�N����`
#define MAX_EXPLOSION (128)
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 rot; //����
	D3DXCOLOR col;//�F
	int nCounterAnim;//�A�j���[�V�����J�E���^�[
	int nPatternAnim;//�A�j���[�V�����p�^�[��
	bool bUse;//�g�p���Ă��邩�ǂ���
	float fLengthExplosion;
	float nAngleExplosion;
}Explosion;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureexplosion = NULL;//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffexplosion = NULL;//���_�o�b�t�@�ւ̃|�C���^
Explosion g_aexplosion[MAX_EXPLOSION];//�e�̏��

void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntexplosion;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureexplosion);

	//�e�̏���������
	for (nCntexplosion = 0; nCntexplosion < MAX_EXPLOSION; nCntexplosion++)
	{
		g_aexplosion[nCntexplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aexplosion[nCntexplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aexplosion[nCntexplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aexplosion[nCntexplosion].nPatternAnim = 0;
		g_aexplosion[nCntexplosion].nCounterAnim = 0;
		g_aexplosion[nCntexplosion].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffexplosion,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffexplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntexplosion = 0; nCntexplosion < MAX_EXPLOSION; nCntexplosion++)
	{
		////���_���W�̐ݒ�
		//pVtx[0].Pos.x = 0;
		//pVtx[0].Pos.y = 0;
		//pVtx[0].Pos.z = 0;

		//pVtx[1].Pos.x = 0;
		//pVtx[1].Pos.y = 0;
		//pVtx[1].Pos.z = 0;

		//pVtx[2].Pos.x = 0;
		//pVtx[2].Pos.y = 0;
		//pVtx[2].Pos.z = 0;

		//pVtx[3].Pos.x = 0;
		//pVtx[3].Pos.y = 0;
		//pVtx[3].Pos.z = 0;

		//���_���W�̐ݒ�
		pVtx[0].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x - 40, g_aexplosion[nCntexplosion].pos.y - 40, 0.0f);//���E���Őݒ肷��
		pVtx[1].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x + 40, g_aexplosion[nCntexplosion].pos.y - 40, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x - 40, g_aexplosion[nCntexplosion].pos.y + 40, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x + 40, g_aexplosion[nCntexplosion].pos.y + 40, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4�����₷
	}
	g_pVtxBuffexplosion->Unlock();
}
//�����̏I������
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureexplosion != NULL)
	{
		g_pTextureexplosion->Release();
		g_pTextureexplosion = NULL;
	}
	if (g_pVtxBuffexplosion != NULL)
	{
		g_pVtxBuffexplosion->Release();
		g_pVtxBuffexplosion = NULL;
	}
}
//�����̍X�V����
void UpdateExplosion(void)
{
	int nCntExplosion;//�������J�E���g
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffexplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aexplosion[nCntExplosion].nCounterAnim++;

		if (g_aexplosion[nCntExplosion].bUse == true)
		{

			if (g_aexplosion[nCntExplosion].nCounterAnim >= 5)
			{
				g_aexplosion[nCntExplosion].nCounterAnim = NULL;//�J�E���^�[�������l�ɖ߂�

				g_aexplosion[nCntExplosion].nPatternAnim++;//�p�^�[���i���o�[���X�V

				//���_���W�̍X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f + g_aexplosion[nCntExplosion].nPatternAnim * 0.125f , 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + g_aexplosion[nCntExplosion].nPatternAnim * 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + g_aexplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + g_aexplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);

			}
			if (g_aexplosion[nCntExplosion].nPatternAnim > 8)
			{
				g_aexplosion[nCntExplosion].nPatternAnim = 0;//�p�^�[���i���o�[�������l�ɖ߂�
				g_aexplosion[nCntExplosion].bUse = false;
			}
		}

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffexplosion->Unlock();

	

	//for (nCntexplosion = 0; nCntexplosion < MAX_EXPLOSION; nCntexplosion++)
	//{
	//	if (g_aexplosion[nCntexplosion].bUse == true)
	//	{
	//		//�J�E���^�[��i�߂ăp�^�[��NO���X�V����
	//		g_aexplosion[nCntexplosion].nCounterAnim++;

	//		//�������g�p����Ă���
	//		if (g_aexplosion[nCntexplosion].nCounterAnim >= 8)
	//		{
	//			g_aexplosion[nCntexplosion].nCounterAnim = 0;
	//			g_aexplosion[nCntexplosion].bUse = false;
	//		}
	//		if ((g_aexplosion[nCntexplosion].nPatternAnim%5)==0)//���p�^�[�����𒴂���
	//		{
	//			g_aexplosion[nCntexplosion].nCounterAnim = 0;
	//			g_aexplosion[nCntexplosion].nPatternAnim = (g_aexplosion[nCntexplosion].nPatternAnim + 1) % 10;

	//			//�e�N�X�`�����W�̍X�V
	//			pVtx[0].tex = D3DXVECTOR2(0.125f * g_aexplosion[nCntexplosion].nPatternAnim, 0.0f);
	//			pVtx[1].tex = D3DXVECTOR2(0.125f + 0.125f * g_aexplosion[nCntexplosion].nPatternAnim, 0.0f);
	//			pVtx[2].tex = D3DXVECTOR2(0.125f * g_aexplosion[nCntexplosion].nPatternAnim, 1.0f);
	//			pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f * g_aexplosion[nCntexplosion].nPatternAnim, 1.0f);

	//			g_aexplosion[nCntexplosion].nCounterAnim--;
	//		}
	//	}
	//	pVtx += 4;
	//}
	
}
//�����̕`�揈��
void DrawExplosion(void)
{
	int nCntexplosion;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffexplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (nCntexplosion = 0; nCntexplosion < MAX_EXPLOSION; nCntexplosion++)
	{
		if (g_aexplosion[nCntexplosion].bUse == true)
		{
			//�|���S���̕`��
			pDevice->SetTexture(0, g_pTextureexplosion);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntexplosion * 4, 2);
		}
	}
}
//�����̐ݒ菈��
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)/*(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot,float fLength)*/
{
	VERTEX_2D* pVtx;

	int nCntexplosion;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffexplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntexplosion = 0; nCntexplosion < MAX_EXPLOSION; nCntexplosion++)
	{
		if (g_aexplosion[nCntexplosion].bUse == false)
		{
			//�������g�p����Ă��Ȃ�
			g_aexplosion[nCntexplosion].pos = pos;
			g_aexplosion[nCntexplosion].col = col;
			g_aexplosion[nCntexplosion].bUse = true;

			/*g_aexplosion[nCntexplosion].rot = rot;*/
			 
			//�������̐ݒ�
			/*pVtx[0].Pos.x = g_aexplosion[nCntexplosion].pos.x + sinf(g_aexplosion[nCntexplosion].rot.z - (D3DX_PI - g_aexplosion[nCntexplosion].fLengthExplosion));
			pVtx[0].Pos.y = g_aexplosion[nCntexplosion].pos.y + cosf(g_aexplosion[nCntexplosion].rot.z - (D3DX_PI - g_aexplosion[nCntexplosion].fLengthExplosion));
			pVtx[0].Pos.z = 0.0f;

			pVtx[1].Pos.x = g_aexplosion[nCntexplosion].pos.x + sinf(g_aexplosion[nCntexplosion].rot.z + (D3DX_PI - g_aexplosion[nCntexplosion].fLengthExplosion));
			pVtx[1].Pos.y = g_aexplosion[nCntexplosion].pos.y + cosf(g_aexplosion[nCntexplosion].rot.z + (D3DX_PI - g_aexplosion[nCntexplosion].fLengthExplosion));
			pVtx[1].Pos.z = 0.0f;

			pVtx[2].Pos.x = g_aexplosion[nCntexplosion].pos.x + sinf(g_aexplosion[nCntexplosion].rot.z +(0.0f - g_aexplosion[nCntexplosion].fLengthExplosion));
			pVtx[2].Pos.y = g_aexplosion[nCntexplosion].pos.y + cosf(g_aexplosion[nCntexplosion].rot.z + (0.0f - g_aexplosion[nCntexplosion].fLengthExplosion));
			pVtx[2].Pos.z = 0.0f;

			pVtx[3].Pos.x = g_aexplosion[nCntexplosion].pos.x + sinf(g_aexplosion[nCntexplosion].rot.z - (0.0f - g_aexplosion[nCntexplosion].fLengthExplosion));
			pVtx[3].Pos.y = g_aexplosion[nCntexplosion].pos.y + cosf(g_aexplosion[nCntexplosion].rot.z - (0.0f - g_aexplosion[nCntexplosion].fLengthExplosion));
			pVtx[3].Pos.z = 0.0f;
			*/

			pVtx[0].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x - 40, g_aexplosion[nCntexplosion].pos.y - 40, 0.0f);//���E���Őݒ肷��
			pVtx[1].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x + 40, g_aexplosion[nCntexplosion].pos.y - 40, 0.0f);
			pVtx[2].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x - 40, g_aexplosion[nCntexplosion].pos.y + 40, 0.0f);
			pVtx[3].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x + 40, g_aexplosion[nCntexplosion].pos.y + 40, 0.0f);

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			/*g_aexplosion[nCntexplosion].col=col;
			g_aexplosion[nCntexplosion].bUse = true;*/

			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffexplosion->Unlock();
}

