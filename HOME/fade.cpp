#include"fade.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;//���_�o�b�t�@�ւ̃|�C���^
FADE g_fade;//���_�t�F�[�h�̏��
MODE g_modeNext;//���̉��(���[�h)
D3DXCOLOR g_colorFade;//�|���S��(�t�F�[�h)�̐F

//�t�F�[�h�̏���������
void InitFade(MODE modeNext)
{
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;
	
	//�f�o�C�X�̏K��
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	g_fade = FADE_IN;//�t�F�[�h�C�����
	g_modeNext = modeNext;//���̉��(���[�h)��ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//�����|���S���𓧖��ɂ���

	//���_���W�̐ݒ�
	pVtx[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(g_colorFade);
	pVtx[1].col = D3DXCOLOR(g_colorFade);
	pVtx[2].col = D3DXCOLOR(g_colorFade);
	pVtx[3].col = D3DXCOLOR(g_colorFade);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffFade->Unlock();

	//���[�h�̐ݒ�
	SetMode(g_modeNext);
}
void UninitFade(void)
{
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
//�t�F�[�h�̍X�V����
void UpdateFade(void)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C�����
			g_colorFade.a -= 0.05f;//�|���S���𓧖��ɂ��Ă���
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;//�������Ă��Ȃ����

			}
		}
		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorFade.a += 0.05f;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�
			    //���[�h�ݒ�
				SetMode(g_modeNext);
			}
		}

		//���_�J���[�̐�
		pVtx[0].col = D3DXCOLOR(g_colorFade);
		pVtx[1].col = D3DXCOLOR(g_colorFade);
		pVtx[2].col = D3DXCOLOR(g_colorFade);
		pVtx[3].col = D3DXCOLOR(g_colorFade);
	}
	g_pVtxBuffFade->Unlock();
}
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏K��
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//�v���~�e�B�u�̎��
}
//�t�F�[�h�̐ݒ菈��
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;//�t�F�[�h�A�E�g���

	g_modeNext = modeNext;//���̉��(���[�h)��ݒ�

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//�����|���S����(����)�ɂ��Ă���
}
//�t�F�[�h�̎擾����
FADE GetFade(void)
{
	return g_fade;
}