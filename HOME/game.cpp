#include "main.h"
#include"player.h"
#include"background.h"
#include"input.h"
#include"bullet.h"
#include"explosion.h"
#include"enemy.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"fade.h"
#include"effect.h"
#include"Score.h"

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;//ゲームの状態
int g_nCounterGameState = 0;//状態管理カウンター

//ゲーム画面の初期化処理
void InitGame(void)
{
	//背景の初期化処理
	InitBackground();

	//プレイヤーの初期化処理
	InitPlayer();

	InitBullet();

	InitExplosion();

	InitEffect();

	//敵の初期化処理
	InitEnemy();

	InitScore();

	SetEnemy(D3DXVECTOR3(500.0f, 150.0f, 0.0f), 0);

	g_gameState = GAMESTATE_NORMAL;//通常状態に設定
	g_nCounterGameState = 0;
}
void UninitGame(void)
{
	//背景の終了処理
	UninitBackground();

	//プレイヤーの終了処理
	UninitPlayer();

	//弾の終了処理
	UninitBullet();

	UninitEnemy();

	UninitExplosion();

	UninitEffect();

	UninitScore();
}
//ゲーム画面の更新処理
void UpdateGame(void)
{
	//背景の更新処理
	UpdateBackground();

	//プレイヤーの更新処理
	UpdatePlayer();

	UpdateBullet();

	UpdateEnemy();

	UpdateExplosion();

	UpdateEffect();

	UpdateScore();

	int Num = GetNumEnemy();

	Enemy* Enemy = GetEnemy();

	if (Num <= 0)
	{
		g_gameState = GAMESTATE_END;
	}
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL://通常状態
		break;

	case GAMESTATE_END://終了状態
		g_nCounterGameState++;

		if (g_nCounterGameState >= 60)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;//何もしていない状態

			//画面(モード)の設定
			SetFade(MODE_RESULT);
		}
		break;
	}
	//if (?)//敵全滅||プレイヤー滅||タイムオーバー
	//{
	//	
	//}
}
void DrawGame(void)
{
	DrawBackground();

	DrawEnemy();

	DrawExplosion();

	DrawPlayer();

	DrawBullet();

	DrawEffect();

	DrawScore();
}
//ゲームの状態の設定
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	g_nCounterGameState = 0;
}

//ゲームの状態の取得
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
