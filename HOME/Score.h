#ifndef _SCORE_H_
#define _SCORE_H_

#include"main.h"

//プロトタイプ宣言
int ScoreCounter(int nScore);
void InitScore(void);//スコアーの初期化処理
void UninitScore(void);//スコアーの終了処理
void UpdateScore(void);//スコアーの更新処理
void DrawScore(void);//スコアーの描画処理
void SetScore(int nScore);
void AddScore(int nValue);
#endif
