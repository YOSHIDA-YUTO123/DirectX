#include"player.h"
#include"title.h"
#include"fade.h"
#include"input.h"
#include"sound.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//頂点バッファへのポインタ

//タイトル画面の初期化処理
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title000.png",
		&g_pTextureTitle);

	//頂点バッファの生成・頂点情報の設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);
	//サウンドの再生
	/*PlaySound();*/

	//頂点ロック
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点ロック解除
	g_pVtxBuffTitle->Unlock();
}
void UninitTitle(void)
{
	//テクスチャの破棄
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
void UpdateTitle(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		//Enterキーの入力
		SetFade(MODE_GAME);
	}
	if (GetJoypadPress(JOYKEY_START) == true)
	{//STARTキーが押された
		//Enterキーの入力
		SetFade(MODE_GAME);
	}
}
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの習得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);

	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類
}