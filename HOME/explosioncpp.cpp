#include"explosion.h"
#include"main.h"

//マクロ定義
#define MAX_EXPLOSION (128)
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 rot; //向き
	D3DXCOLOR col;//色
	int nCounterAnim;//アニメーションカウンター
	int nPatternAnim;//アニメーションパターン
	bool bUse;//使用しているかどうか
	float fLengthExplosion;
	float nAngleExplosion;
}Explosion;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureexplosion = NULL;//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffexplosion = NULL;//頂点バッファへのポインタ
Explosion g_aexplosion[MAX_EXPLOSION];//弾の情報

void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntexplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureexplosion);

	//弾の情報を初期化
	for (nCntexplosion = 0; nCntexplosion < MAX_EXPLOSION; nCntexplosion++)
	{
		g_aexplosion[nCntexplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aexplosion[nCntexplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aexplosion[nCntexplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aexplosion[nCntexplosion].nPatternAnim = 0;
		g_aexplosion[nCntexplosion].nCounterAnim = 0;
		g_aexplosion[nCntexplosion].bUse = false;//使用していない状態にする
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffexplosion,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファのロック
	g_pVtxBuffexplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntexplosion = 0; nCntexplosion < MAX_EXPLOSION; nCntexplosion++)
	{
		////頂点座標の設定
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

		//頂点座標の設定
		pVtx[0].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x - 40, g_aexplosion[nCntexplosion].pos.y - 40, 0.0f);//←右回りで設定する
		pVtx[1].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x + 40, g_aexplosion[nCntexplosion].pos.y - 40, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x - 40, g_aexplosion[nCntexplosion].pos.y + 40, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x + 40, g_aexplosion[nCntexplosion].pos.y + 40, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分増やす
	}
	g_pVtxBuffexplosion->Unlock();
}
//爆発の終了処理
void UninitExplosion(void)
{
	//テクスチャの破棄
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
//爆発の更新処理
void UpdateExplosion(void)
{
	int nCntExplosion;//爆発をカウント
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファのロック
	g_pVtxBuffexplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aexplosion[nCntExplosion].nCounterAnim++;

		if (g_aexplosion[nCntExplosion].bUse == true)
		{

			if (g_aexplosion[nCntExplosion].nCounterAnim >= 5)
			{
				g_aexplosion[nCntExplosion].nCounterAnim = NULL;//カウンターを初期値に戻す

				g_aexplosion[nCntExplosion].nPatternAnim++;//パターンナンバーを更新

				//頂点座標の更新
				pVtx[0].tex = D3DXVECTOR2(0.0f + g_aexplosion[nCntExplosion].nPatternAnim * 0.125f , 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + g_aexplosion[nCntExplosion].nPatternAnim * 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + g_aexplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + g_aexplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);

			}
			if (g_aexplosion[nCntExplosion].nPatternAnim > 8)
			{
				g_aexplosion[nCntExplosion].nPatternAnim = 0;//パターンナンバーを初期値に戻す
				g_aexplosion[nCntExplosion].bUse = false;
			}
		}

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffexplosion->Unlock();

	

	//for (nCntexplosion = 0; nCntexplosion < MAX_EXPLOSION; nCntexplosion++)
	//{
	//	if (g_aexplosion[nCntexplosion].bUse == true)
	//	{
	//		//カウンターを進めてパターンNOを更新する
	//		g_aexplosion[nCntexplosion].nCounterAnim++;

	//		//爆発が使用されている
	//		if (g_aexplosion[nCntexplosion].nCounterAnim >= 8)
	//		{
	//			g_aexplosion[nCntexplosion].nCounterAnim = 0;
	//			g_aexplosion[nCntexplosion].bUse = false;
	//		}
	//		if ((g_aexplosion[nCntexplosion].nPatternAnim%5)==0)//総パターン数を超えた
	//		{
	//			g_aexplosion[nCntexplosion].nCounterAnim = 0;
	//			g_aexplosion[nCntexplosion].nPatternAnim = (g_aexplosion[nCntexplosion].nPatternAnim + 1) % 10;

	//			//テクスチャ座標の更新
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
//爆発の描画処理
void DrawExplosion(void)
{
	int nCntexplosion;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffexplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
    pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (nCntexplosion = 0; nCntexplosion < MAX_EXPLOSION; nCntexplosion++)
	{
		if (g_aexplosion[nCntexplosion].bUse == true)
		{
			//ポリゴンの描画
			pDevice->SetTexture(0, g_pTextureexplosion);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntexplosion * 4, 2);
		}
	}
}
//爆発の設定処理
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)/*(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot,float fLength)*/
{
	VERTEX_2D* pVtx;

	int nCntexplosion;

	//頂点バッファのロック
	g_pVtxBuffexplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntexplosion = 0; nCntexplosion < MAX_EXPLOSION; nCntexplosion++)
	{
		if (g_aexplosion[nCntexplosion].bUse == false)
		{
			//爆発が使用されていない
			g_aexplosion[nCntexplosion].pos = pos;
			g_aexplosion[nCntexplosion].col = col;
			g_aexplosion[nCntexplosion].bUse = true;

			/*g_aexplosion[nCntexplosion].rot = rot;*/
			 
			//爆発情報の設定
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

			pVtx[0].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x - 40, g_aexplosion[nCntexplosion].pos.y - 40, 0.0f);//←右回りで設定する
			pVtx[1].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x + 40, g_aexplosion[nCntexplosion].pos.y - 40, 0.0f);
			pVtx[2].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x - 40, g_aexplosion[nCntexplosion].pos.y + 40, 0.0f);
			pVtx[3].Pos = D3DXVECTOR3(g_aexplosion[nCntexplosion].pos.x + 40, g_aexplosion[nCntexplosion].pos.y + 40, 0.0f);

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			/*g_aexplosion[nCntexplosion].col=col;
			g_aexplosion[nCntexplosion].bUse = true;*/

			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffexplosion->Unlock();
}

