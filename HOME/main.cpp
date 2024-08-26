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
#include"sound.h"
#include"Score.h"
#include"effect.h"

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//グローバル変数宣言
LPDIRECT3D9 g_pD3D = NULL;//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
MODE g_mode = MODE_TITLE;//現在のモード

//===================================
//メイン関数
//===================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DWORD dwCurrentTime;//現在時刻
	DWORD dwExecLastTime = timeGetTime();//最後に処理した時刻

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;//初期化する
	dwExecLastTime = timeGetTime();//現在時刻保存

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,        //ウインドウのスタイル
		WindowProc,        //ウインドウプロシージャ
		0,                 //0にする(通常は使用しない)
		0,                 //0にする(通常は使用しない)
		hInstance,         //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),//クライアント領域の色
		NULL,//メニューバー
		CLASS_NAME,//ウインドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)//ファイルのアイコン
	};
	HWND hWnd;//ウインドウのハンドル
	MSG msg;

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定サイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx(0,//拡張ウィンドウスタイル
		CLASS_NAME,           //ウインドウクラスの名前
		WINDOW_NAME,          //ウインドウの名前
		WS_OVERLAPPEDWINDOW,  //ウインドウのスタイル
		CW_USEDEFAULT,        //ウインドウ左上X座標
		CW_USEDEFAULT,        //ウインドウ左上Y座標
		(rect.right - rect.left),//ウインドウ左上x座標幅
		(rect.bottom - rect.top),//ウインドウ左上Y座標高さ
		NULL,                 //親ウインドウのハンドル
		NULL,                 //メニューハンドルまたはウインドウID
		hInstance,            //インスタンスハンドル
		NULL);                 //ウインドウ作成データ

		//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);//ウインドウの表示状態を設定
	UpdateWindow(hWnd);            //クライアント領域を更新

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}
	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらループを抜ける
				break;
			}
			else
			{//DirectXの処理
				//メッセージの設定
				dwCurrentTime = timeGetTime();//現在時刻

				if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
				{
					dwExecLastTime = dwCurrentTime;//処理開始の時刻(現在時刻)を保存
				}
				TranslateMessage(&msg);//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg); //ウインドウプロシージャへメッセージを送出
			}
		}
		else
		{
			//更新処理
			Update();

			//描画処理
			Draw();
		}
		
	}
	//終了処理
	Uninit();

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);


	return(int)msg.wParam;
}
//ウインドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;//デバイスコンテキスト(GDIオブジェクト)のハンドル

	const RECT rect = { 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };//ウインドウの領域

	switch (uMsg)
	{
	case WM_DESTROY: //ウインドウの破棄メッセージ
		//WM_QUITへメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE://[Esc]キー押された
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);    //既定の処理を返す
}
//初期化処理
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{

	D3DDISPLAYMODE d3ddm; //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp; //プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;//バックバッファの形式
	d3dpp.BackBufferCount = 1;//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//バックバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//インターバル

	//Direct3Dデバイスの生成描画処理と頂点処理をハードウェアで行う
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//ジョイパッドの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}
	
	
	InitTitle();

	InitGame();

	InitResult();

	InitSound(hWnd);

	//モードの設定
	SetMode(g_mode);

	//フェードの設定
	InitFade(g_mode);

	return S_OK;
}
//デバイスの取得
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//終了処理
void Uninit(void)
{
	//ジョイパッドの終了処理
	UninitJoypad();

	//タイトル画面の終了
	UninitTitle();
	
	//ゲーム画面の終了処理
	UninitGame();

	//リザルト画面の終了処理
	UninitResult();

	//フェード
	UninitFade();

	//キーボードの終了処理
	UninitKeyboard();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3Dデバイスの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
//更新処理
void Update(void)
{
	//ジョイパッドの更新処理
	UpdateJoypad();

	//キーボードの更新処理
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UpdateTitle();
		break;

	case MODE_GAME://ゲーム画面
		UpdateGame();
		break;

	case MODE_RESULT://リザルト画面
		UpdateResult();
		break;
	}
	UpdateFade();
}
//描画処理
void Draw(void)
{
	//画面クリア(バックバッファ&Zバッファのクリア)
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
		switch (g_mode)
		{
		case MODE_TITLE://タイトル画面
			DrawTitle();
			break;

		case MODE_GAME://ゲーム画面
			DrawGame();
			break;

		case MODE_RESULT://リザルト画面
			DrawResult();
			break;
		}
		DrawFade();
	
	 //プレイヤーの描画処理
	
		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
void SetMode(MODE mode)
{
	//現在のモードの終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;
	}
	//新しいゲームモードの初期化処理
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;
	}
	g_mode = mode;
}
MODE GetMode(void)
{
	return g_mode;
}


