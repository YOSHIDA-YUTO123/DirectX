#include"fade.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;//頂点バッファへのポインタ
FADE g_fade;//頂点フェードの状態
MODE g_modeNext;//次の画面(モード)
D3DXCOLOR g_colorFade;//ポリゴン(フェード)の色

//フェードの初期化処理
void InitFade(MODE modeNext)
{
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;
	
	//デバイスの習得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	//頂点バッファのロック
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	g_fade = FADE_IN;//フェードイン状態
	g_modeNext = modeNext;//次の画面(モード)を設定
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//黒いポリゴンを透明にする

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
	pVtx[0].col = D3DXCOLOR(g_colorFade);
	pVtx[1].col = D3DXCOLOR(g_colorFade);
	pVtx[2].col = D3DXCOLOR(g_colorFade);
	pVtx[3].col = D3DXCOLOR(g_colorFade);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffFade->Unlock();

	//モードの設定
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
//フェードの更新処理
void UpdateFade(void)
{
	VERTEX_2D* pVtx;

	//頂点バッファのロック
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//フェードイン状態
			g_colorFade.a -= 0.05f;//ポリゴンを透明にしていく
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;//何もしていない状態

			}
		}
		else if (g_fade == FADE_OUT)
		{//フェードアウト状態
			g_colorFade.a += 0.05f;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;//フェードイン状態に
			    //モード設定
				SetMode(g_modeNext);
			}
		}

		//頂点カラーの設
		pVtx[0].col = D3DXCOLOR(g_colorFade);
		pVtx[1].col = D3DXCOLOR(g_colorFade);
		pVtx[2].col = D3DXCOLOR(g_colorFade);
		pVtx[3].col = D3DXCOLOR(g_colorFade);
	}
	g_pVtxBuffFade->Unlock();
}
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの習得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類
}
//フェードの設定処理
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;//フェードアウト状態

	g_modeNext = modeNext;//次の画面(モード)を設定

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//黒いポリゴンを(透明)にしておく
}
//フェードの取得処理
FADE GetFade(void)
{
	return g_fade;
}