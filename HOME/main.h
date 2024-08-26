#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_
#include<windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)//ビルド時の警告対処マクロ
#include "dinput.h"
#include"Xinput.h"
#include"xaudio2.h"

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")//描画処理に必要
#pragma comment(lib,"d3dx9.lib")//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")//DirectXコンポネーション(部品)使用に必要
#pragma comment(lib,"winmm.lib")//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")//入力処理に必要
#pragma comment(lib,"xinput.lib")//ジョイパッド処理に必要

//マクロ定義
#define CLASS_NAME "WindowClass" //ウインドウクラスの名前
#define WINDOW_NAME "DirectXの基本処理" //ウインドウの名前(キャプションに表示)
#define SCREEN_WIDTH (1280) //ウインドウの幅
#define SCREEN_HEIGHT (720) //ウインドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define PLAYER_WIDTH (200.0f)//幅
#define PLAYER_HEIGHT (100.0f)//高さ


typedef struct
{
	D3DXVECTOR3 Pos; //頂点座標
	float rhw;       //座標返還係数(1.0fで指定)
	D3DCOLOR col;    //頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_2D;

typedef enum
{
	MODE_TITLE = 0, //タイトル画面
	MODE_GAME,//ゲーム画面
	MODE_RESULT,//リザルト画面
	MODE_MAX
}MODE;

typedef enum
{
	JOYKEY_UP=0,//十字キー上
	JOYKEY_DOWN,//十字キー下
	JOYKEY_LEFT,//十字キー左
	JOYKEY_RIGHT,//十字キー右
	JOYKEY_START,//START
	JOYKEY_BAKC,//BACK
	JOYKEY_LEFT_THUMB,
	JOYKEY_RIGHT_THUMB,
	JOYKEY_LEFT_SHOULDER,//左トリガー
	JOYKEY_RIGHT_SHOULDER,//右トリガー
	JOYKEY_L2,
	JOYKEY_R2,
	JOYKEY_A,//Aボタン
	JOYKEY_B,//Bボタン
	JOYKEY_X,//Xボタン
	JOYKEY_Y,//Yボタン
	
	
	JOYKEY_MAX

}JOYKEY;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif
