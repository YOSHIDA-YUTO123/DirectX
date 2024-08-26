#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//出現状態
	PLAYERSTATE_NORMAL,//通常状態
	PLAYERSTATE_DAMAGE,//ダメージ状態
	PLAYERSTATE_DEATH,//死亡状態
	PLAYERSTATE_MAX
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//向き
	D3DXVECTOR3 move;//移動量
	PLAYERSTATE state;//プレイヤーの状態
	int nCounterState;//状態管理カウンター
	int nLife;//体力
	bool bDisp;//表示するかしないか
	bool bUse;
}Player;

void InitPlayer(void);//プレイヤーの初期化処理
void UninitPlayer(void);//プレイヤーの終了処理
void UpdatePlayer(void);//プレイヤーの更新処理
void DrawPlayer(void);//プレイヤーの描画処理
Player* GetPlayer(void);
void HitPlayer(int nDamage);
#endif
