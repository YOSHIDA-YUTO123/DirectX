#include"main.h"
#include"background.h"

//マクロ定義
#define NUM_BG (3)//背景の数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureBG[NUM_BG] = {};//テクスチャ3枚分のポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBackground = NULL;//頂点バッファへのポインタ
float g_aPosTexU[NUM_BG];//テクスチャ座標の開始位置(U値)

//背景の初期化処理
void InitBackground(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	int nCntBG;

	//デバイスの習得
	pDevice = GetDevice();

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg100.png",
		&g_apTextureBG[0]);

	//テクスチャ2の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg101.png",
		&g_apTextureBG[1]);

	//テクスチャ3の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg102.png",
		&g_apTextureBG[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 8 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBackground,
		NULL);

	//テクスチャ座標の初期化
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] = 0.0f;
	}

	VERTEX_2D* pVtx;//頂点座標へのポインタ
	//頂点ロック
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//頂点座標の設定
		pVtx[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG]+1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG]+1.0f, 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffBackground->Unlock();
}
//プレイヤーの終了処理
void UninitBackground(void)
{
	int nCntBG;

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャの破棄
		if (g_apTextureBG[nCntBG] != NULL)
		{
 			g_apTextureBG[nCntBG]->Release();
			g_apTextureBG[nCntBG] = NULL;
		}
	}
	if (g_pVtxBuffBackground != NULL)
	{
		g_pVtxBuffBackground->Release();
		g_pVtxBuffBackground = NULL;
	}
	
}
//バックグラウンドの更新処理
void UpdateBackground(void)
{
	int nCntBG;
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャ座標の開始位置(U値)の更新
		g_aPosTexU[nCntBG] += 0.001f;

		//テクスチャ座標の更新
		// 
		//頂点座標の設定
		pVtx[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBackground->Unlock();
}
//プレイヤーの描画処理
void DrawBackground(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの習得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBackground, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	VERTEX_2D* pVtx=0;
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureBG[0]);
		pDevice->SetTexture(0, g_apTextureBG[1]);
		pDevice->SetTexture(0, g_apTextureBG[2]);

		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類

		pVtx += 4;
	}
}