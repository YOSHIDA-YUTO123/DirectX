#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//マクロ定義
#define MAX_ENEMY (128)//敵の最大数
#define MAX_WIDTH (100)
#define MAX_HEIGHT (100)

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,//通常状態
	ENEMYSTATE_DAMAGE,//ダメージ状態
	ENEMYSTATE_MAX
}ENEMYSTATE;

//敵情報(列挙型)
typedef enum
{
	ENEMYTYPE_OWN=0,
	ENEMYTYPE_TWO,
	ENEMYTYPE_THREE,
	ENEMYTYPE_FOUR,
	ENEMYTYPE_FIVE,
	ENEMYTYPE_SIX,
	ENEMYTYPE_MAX
}ENEMYTYPE;

static const char* ENEMY_TEXTURE[ENEMYTYPE_MAX] =//敵のテクスチャの設定
{
	"data\\TEXTURE\\Ene1.png",
	"data\\TEXTURE\\Ene2.jpeg",
	"data\\TEXTURE\\Ene3.jpg",
	"data\\TEXTURE\\monster.png",
};
//敵構造体定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	int nUnko;
	int nType;//種類
	bool bUse;//使用しているかどうか
	ENEMYSTATE state;//状態
	int nCnterState;//状態カウンター
	int BulletCounter;
	int nLife;
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
Enemy* GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
int GetNumEnemy(void);

#endif