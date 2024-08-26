#include"bullet.h"
#include"main.h"
#include"explosion.h"
#include"enemy.h"
#include"player.h"
#include"effect.h"

//マクロ定義
#define MAX_BULLET (128)//玉の最大数

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	float fRadius;
	int nLife;
	BULLETTYPE type;
	bool bUse;
}Bullet;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];//弾の情報

void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//頂点バッファのロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//弾の情報を初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 25;
		g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
	}
		
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
	g_pVtxBuffBullet->Unlock();
}
//弾の終了処理
void UninitBullet(void)
{
	//テクスチャの破棄
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
		//弾の位置の更新
		g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
		g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;

		//頂点座標の設定
		pVtx[0].Pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y - 30.0f, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y - 30.0f, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y + 30.0f, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y + 30.0f, 0.0f);

		g_aBullet[nCntBullet].nLife--;

		if (0 >= g_aBullet[nCntBullet].pos.x >= SCREEN_WIDTH || 0 >= g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT)//弾が画面外に出た
		{
			g_aBullet[nCntBullet].bUse = false;//使用しない状態
		}
		//寿命カウントダウン
		if (g_aBullet[nCntBullet].nLife <= 0)//寿命尽きた
		{
			//爆発の設定
			SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			g_aBullet[nCntBullet].bUse = false;//使用していない状態
		}

		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
				
				int nCntEnemy;

				//敵の取得
				Enemy* pEnemy = GetEnemy();

				if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
				{
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50.0f, 50);

					for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
					{
						if (pEnemy->bUse == true)
						{//敵が使用されている

							if (g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + MAX_WIDTH *1.0f
								&& g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - MAX_WIDTH * 0.15f
								&& g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + MAX_HEIGHT * 0.55f
								&& g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - MAX_HEIGHT * 0.6f
								)
							{
								HitEnemy(nCntEnemy,1);

								//爆発の設定
								SetExplosion(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255));

								/*pEnemy->bUse = false;*/

								g_aBullet[nCntBullet].bUse = false;
							}
						}
						pEnemy++;
					}
				}
				//プレイヤー
				else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
				{//敵の弾
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

							//爆発の設定
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
//弾の描画処理
void DrawBullet(void)
{
	int nCntBullet;

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの習得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
			//ポリゴンの描画
			pDevice->SetTexture(0, g_pTextureBullet);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBullet* 4, 2);//プリミティブの種類
		}
	}
}
//弾の設定処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	VERTEX_2D* pVtx;

	int nCntBullet;

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されていない
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 25;
			g_aBullet[nCntBullet].bUse = true;
			g_aBullet[nCntBullet].type = type;
	
			//頂点座標の設定
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
