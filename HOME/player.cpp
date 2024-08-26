#include "main.h"
#include "player.h"
#include "input.h"
#include"bullet.h"
#include"enemy.h"
#include"explosion.h"
#include"fade.h"
#include"effect.h"

//グローバル変数宣言

LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//テクスチャへのポインタ//ノート
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//頂点バッファへのポインタ
Player g_player;//プレイヤーの情報

int g_nCounterAnimPlayer = 0; //アニメーションカウンター
int g_nPatternAnimPlayer = 0; //アニメーションパターンNo.

D3DXVECTOR3 g_posPlayer;//位置
D3DXVECTOR3 g_movePlayer;//移動量
D3DXVECTOR3 g_rotPlayer;//向き
float g_fLengthPlayer;//対角線の長さ
float g_fAnglePlayer;//対角線の角度


//プレイヤーの初期化処理
void InitPlayer(void)
{
	VERTEX_2D* pVtx;//頂点座標へのポインタ

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの習得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player.png",
		&g_pTexturePlayer);

	g_nCounterAnimPlayer = 0;//カウンターを初期化する
	g_nPatternAnimPlayer = 0;//カウンターを初期化する
	g_posPlayer = D3DXVECTOR3(PLAYER_WIDTH,PLAYER_HEIGHT,0.0f);//位置を初期化する
	g_movePlayer = D3DXVECTOR3(0.0f,0.0f,0.0f);//移動量を初期化する
	g_rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きを初期化する
	g_player.nCounterState = 0;
	g_player.bDisp = true;
	g_player.nLife = 3;

	//対角線の長さを算出する
	g_fLengthPlayer = sqrtf((PLAYER_WIDTH*PLAYER_WIDTH)+(PLAYER_HEIGHT*PLAYER_HEIGHT))/2.0f;

	//対角線の角度を算出する
	g_fAnglePlayer = atan2f(PLAYER_WIDTH,PLAYER_HEIGHT);

	//頂点座標の設定
	pVtx[0].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[0].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[0].Pos.z = 0.0f;

	//頂点座標の設定
	pVtx[1].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + (D3DX_PI - g_fAnglePlayer)) *g_fLengthPlayer;
	pVtx[1].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + (D3DX_PI - g_fAnglePlayer)) *g_fLengthPlayer;
	pVtx[1].Pos.z = 0.0f;

	//頂点座標の設定
	pVtx[2].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].Pos.z = 0.0f;

	//頂点座標の設定
	pVtx[3].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[3].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[3].Pos.z = 0.0f;

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffPlayer->Unlock();
}
//プレイヤーの終了処理
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//プレイヤーの更新処理
void UpdatePlayer(void)
{
	XINPUT_STATE* pStick;
	pStick = GetJoySticAngle();
	VERTEX_2D* pVtx;//頂点座標へのポインタ

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			g_player.state = PLAYERSTATE_NORMAL;
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

			g_pVtxBuffPlayer->Unlock();
		}
		break;

	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{
			//モード設定(リザルト画面に移動)
			/*SetMode(MODE_RESULT);*/

			return;
		}
		break;
	}
	
	static float fData = 0.2f;

	if (GetJoypadPress(JOYKEY_UP) == true)
	{//上キーが押された
		g_posPlayer.y -= 1.0f;
		//頂点座標の更新
	}
	else if (GetJoypadPress(JOYKEY_DOWN) == true)
	{//下キーが押された
		g_posPlayer.y += 1.0f;
		//頂点座標の更新
	}
	else if (GetJoypadPress(JOYKEY_RIGHT) == true)
	{//右キーが押された
		g_posPlayer.x += 1.0f;
		//頂点座標の更新
	}
	else if (GetJoypadPress(JOYKEY_LEFT) == true)
	{//左キーが押された
		g_posPlayer.x -= 1.0f;
		//頂点座標の更新
	}
	
	else if (GetJoypadPress(JOYKEY_BAKC) == true)
	{//バックが押された
		g_fLengthPlayer = 110.0f;
		g_rotPlayer.z = 0.0f;
		g_posPlayer.x = PLAYER_WIDTH;
		g_posPlayer.y = PLAYER_HEIGHT;
	}
	else if (GetJoypadPress(JOYKEY_LEFT_SHOULDER) == true)
	{//左トリガーが押された
		g_rotPlayer.z += 0.04f;
	}
	else if (GetJoypadPress(JOYKEY_RIGHT_SHOULDER) == true)
	{//右トリガーが押された
		g_rotPlayer.z -= 0.04f;
	}
	else if (GetJoypadPress(JOYKEY_A) == true)
	{//Aボタンが押された
		SetEnemy(D3DXVECTOR3(100.0f, 100.0f, 0.0f), 0);
	}
	else if (GetJoypadPress(JOYKEY_B) == true)
	{//Bボタンが押された
		if (g_fLengthPlayer > 0)
		{
			g_fLengthPlayer -= 0.5f;
		}
	}
	else if (GetJoyTrigger(JOYKEY_X) == true)
	{//Xボタンが押された
		//弾の設定
		SetBullet(g_posPlayer, D3DXVECTOR3(sinf(g_rotPlayer.z + D3DX_PI) * 10.0f, cosf(g_rotPlayer.z + D3DX_PI) * 10.0f, 0.0f), 1, BULLETTYPE_PLAYER);
	}
	else if (GetJoypadPress(JOYKEY_Y) == true)
	{//Yボタンが押された
		if (g_fLengthPlayer < 300.0f)
		{
			g_fLengthPlayer += 0.5f;
		}
	}
	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーが押された
		fData = 0.2f;

		if (GetKeyboardPress(DIK_W) == true)
		{//Wキーが押された
			//上移動
			g_movePlayer.x += sinf(-D3DX_PI * 0.75f) * 0.5f;
			g_movePlayer.y += cosf(-D3DX_PI * 0.75f) * 0.5f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//Sキーが押された
			//下移動
			g_movePlayer.x += sinf(-D3DX_PI*0.25f) * 0.5f;
			g_movePlayer.y += cosf(-D3DX_PI*0.25f) * 0.5f;
		}
		else
		{
			//左移動
			g_movePlayer.x -= 0.5f;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//Dキーが押された	
		fData = -0.2f;
		if (GetKeyboardPress(DIK_W) == true)
		{//Wキーが押された
			//上移動
			g_movePlayer.x += sinf(D3DX_PI * 0.75f) * 0.5f;
			g_movePlayer.y += cosf(D3DX_PI * 0.75f) * 0.5f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//Sキーが押された
			//下移動
			g_movePlayer.x += sinf(D3DX_PI * 0.25f) * 0.5f;
			g_movePlayer.y += cosf(D3DX_PI * 0.25f) * 0.5f;
		}
		else
		{
			//右移動
			g_movePlayer.x += 0.5f;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{//Wキーが押された
		//上移動
		g_movePlayer.y -= 0.5f;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//Sキーが押された
		//下移動
		g_movePlayer.y += 0.5f;
	}
	else if (GetKeyboardPress(DIK_Q) == true)//左回転
	{
		g_rotPlayer.z += 0.04f;
	}
	else if (GetKeyboardPress(DIK_E) == true)//右回転
	{
		g_rotPlayer.z -= 0.04f;
	}
	else if (GetKeyboardPress(DIK_F) == true)
	{
		if (g_fLengthPlayer < 300.0f)
		{
			g_fLengthPlayer += 0.5f;
		}
	}
	else if (GetKeyboardPress(DIK_G) == true)
	{
		if (g_fLengthPlayer > 0)
		{
			g_fLengthPlayer -= 0.5f;
		}
	}
	else if (GetKeyboardPress(DIK_V) == true)//リセット
	{
		g_fLengthPlayer = 110.0f;
		g_rotPlayer.z = 0.0f;
		g_posPlayer.x = PLAYER_WIDTH;
		g_posPlayer.y = PLAYER_HEIGHT;
	}
	else if (GetJoyStick() == true)
	{
		if (pStick->Gamepad.sThumbLX > 10922)
		{//右移動
			g_player.move.x += 0.5;
		}
		else if (pStick->Gamepad.sThumbLX < -10922)
		{//左移動
			g_player.move.x -= 0.5;
		}
		else if (pStick->Gamepad.sThumbLY > 10922)
		{//上移動
			g_player.move.y -= 0.5;
		}
		else if (pStick->Gamepad.sThumbLY < -10922)
		{//下移動
			g_player.move.y += 0.5;
		}
	}
	/*else if (KeyboardTrigger(DIK_T) == true)
	{
		SetEnemy(D3DXVECTOR3(100.0f, 100.0f, 0.0f), 0);
	}*/
	if (KeyboardTrigger(DIK_SPACE) == true)
	{//SPACEキーが押された
		
		//弾の設定
		SetBullet(g_posPlayer,D3DXVECTOR3(sinf(g_rotPlayer.z+D3DX_PI)*10.0f,cosf(g_rotPlayer.z+D3DX_PI)*10.0f,0.0f),1,BULLETTYPE_PLAYER);
	}


	//位置を更新
	g_posPlayer.x += g_movePlayer.x;
	g_posPlayer.y += g_movePlayer.y;

	//移動量を減衰
	g_movePlayer.x += (0.0f - g_movePlayer.x) * 0.1f;
	g_movePlayer.y += (0.0f - g_movePlayer.y) * 0.1f;

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].Pos.z = 0.0f;

	//頂点座標の設定
	pVtx[1].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - (D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - (D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].Pos.z = 0.0f;

	//頂点座標の設定
	pVtx[2].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].Pos.z = 0.0f;

	//頂点座標の設定
	pVtx[3].Pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[3].Pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[3].Pos.z = 0.0f;

	g_pVtxBuffPlayer->Unlock();
	//g_nCounterAnimPlayer++;//カウンターを加算

	//if (g_nCounterAnimPlayer >1)
	//{
	//	g_nCounterAnimPlayer = 0;//パターンNo.を初期値に戻す
	//	g_nPatternAnimPlayer++;//パターンNo.を更新する

	//	if (g_nPatternAnimPlayer >= 10)
	//	{
	//		g_nPatternAnimPlayer = 0;//パターンNo.を初期値に戻す
	//	}

	

	//	//頂点バッファをロックし、頂点情報へのポインタを取得
	//	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//	//アニメーション
	//	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f);
	//	pVtx[1].tex = D3DXVECTOR2(fData+g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f);
	//	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f + 0.5f);
	//	pVtx[3].tex = D3DXVECTOR2(fData+g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f + 0.5f);

	//	//頂点バッファをアンロックする
	//	g_pVtxBuffPlayer->Unlock();
	//}
}
//プレイヤーの描画処理
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの習得
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類
	}
}
//プレイヤーの取得
Player* GetPlayer(void)
{
	return &g_player;
}
//プレイヤーのヒット処理
void HitPlayer(int nDamage)
{
	VERTEX_2D* pVtx;
	
	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)//プレイヤーの体力がなくなった
	{
		//爆発の設定
		SetExplosion(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255));

		g_player.bDisp = false;

		g_player.state = PLAYERSTATE_DEATH;

		g_player.nCounterState = 60;
	}
	else
	{
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 10;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		g_pVtxBuffPlayer->Unlock();
	}
	
}