#include "effect.h"

//マクロ定義
#define MAX_EFFECT (4096)//エフェクトの最大数

//エフェクト構造体
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXCOLOR col;//色
	float fRadius;//半径(大きさ)
	int nLife;//寿命(表示時間)
	bool bUse;//使用しているかどうか
}Effect;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//頂点バッファへのポインタ
Effect  g_aEffect[MAX_EFFECT];//弾の情報

//エフェクトの初期化処理
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//頂点バッファのロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//弾の情報を初期化
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].nLife=50;
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].bUse = false;//使用していない状態にする
	}


	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//頂点座標の設定
		pVtx[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定bh
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分増やす
	}
	g_pVtxBuffEffect->Unlock();
}
//エフェクトの終了処理
void UninitEffect(void)
{
	//テクスチャの破棄
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//エフェクトの更新処理
void UpdateEffect(void)
{
	VERTEX_2D* pVtx;

	int nCntEffect;

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//頂点カラーの設定(更新)
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//頂点座標の設定
			pVtx[0].Pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].Pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].Pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].Pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			g_aEffect[nCntEffect].fRadius--;

			g_aEffect[nCntEffect].nLife--;

			if (g_aEffect[nCntEffect].nLife <= 0)//寿命が尽きた
			{
				g_aEffect[nCntEffect].bUse = false;
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock();

}
//エフェクトの描画処理
void DrawEffect(void)
{
	int nCntEffect;

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの習得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//aブレンディング
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//ポリゴンの描画
			pDevice->SetTexture(0, g_pTextureEffect);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);//プリミティブの種類
		}
	}
	//aブレンディングをもとに戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
}
//エフェクトの設定処理
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;

	VERTEX_2D* pVtx;

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//弾が使用されていない
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;

			//頂点カラーの設定(更新)
			pVtx[0].col = D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.25f);
			pVtx[1].col = D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.25f);
			pVtx[2].col = D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.25f);
			pVtx[3].col = D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.25f);

			//頂点座標の設定
			pVtx[0].Pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 30.0f, g_aEffect[nCntEffect].pos.y - 30.0f, 0.0f);
			pVtx[1].Pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 30.0f, g_aEffect[nCntEffect].pos.y - 30.0f, 0.0f);
			pVtx[2].Pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 30.0f, g_aEffect[nCntEffect].pos.y + 30.0f, 0.0f);
			pVtx[3].Pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 30.0f, g_aEffect[nCntEffect].pos.y + 30.0f, 0.0f);

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock();
}
