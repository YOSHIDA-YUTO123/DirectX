#include"enemy.h"
#include"bullet.h"
#include"main.h"

//マクロ定義
#define NUM_ENEMY (4)//敵の種類

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];//敵の情報
int g_nNumEnemy = 0;//敵の総数

//敵の初期化処理
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイスを取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;

	//テクスチャ(４枚分)の読み込み
	
	for (int nCnt = 0; nCnt < ENEMYTYPE_MAX; nCnt++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			ENEMY_TEXTURE[nCnt],
			&g_apTextureEnemy[nCnt]);
	}

	//頂点バッファの生成・頂点情報の設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//初期化
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
	
	//頂点バッファのロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		g_aEnemy[NUM_ENEMY].pos = D3DXVECTOR3(500.0f, 150.0f, 0.0f);

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

		//頂点カラーの設定
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
	g_pVtxBuffEnemy->Unlock();
}
//敵の終了処理
void UninitEnemy(void)
{
	int nCntEnemy;

	//テクスチャの破棄
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

	//頂点バッファのロック
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
	
					//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//g_aEnemy[nCntEnemy].BulletCounter++;
					//if (g_aEnemy[nCntEnemy].BulletCounter == 3)//一定時間経過
					//{
					//	g_aEnemy[nCntEnemy].BulletCounter = 0;
					//}
					break;

				case ENEMYSTATE_DAMAGE:
				
					g_aEnemy[nCntEnemy].nCnterState--;

					if (g_aEnemy[nCntEnemy].nCnterState <= 0)
					{
						////頂点バッファのロック
						//g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

						g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
						//頂点カラーの設定
						
						//pVtx += 4 * nCntEnemy;

						//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						////頂点バッファをアンロックする
						//g_pVtxBuffEnemy->Unlock();			
					}
					break;
			}
		}
	}
	g_pVtxBuffEnemy->Unlock();
}
//敵の描画処理
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用されている

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[nCntEnemy]);
		}
	}
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//敵(ポリゴン)の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}
//敵の設定処理
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D* pVtx;

	int nCntEnemy;

	//頂点バッファのロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//敵が使用されていない

			//敵の情報の設定
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = 5;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCnterState = 0;
			g_aEnemy[nCntEnemy].BulletCounter = 0;
			g_aEnemy[nCntEnemy].bUse = true;

			//頂点座標の設定
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

	if (g_aEnemy[nCntEnemy].nLife<=0)//敵の体力がなくなった
	{
		//爆発の設定
		g_aEnemy[nCntEnemy].bUse = false;

		g_nNumEnemy--;
	}
	else
	{
		//頂点バッファのロック
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCnterState = 5;

		pVtx += 4 * nCntEnemy;

		//頂点カラーの設定
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
