#include"input.h"
//マクロ定義
#define NUM_KEY_MAX (256)//キーの最大数

//グローバル変数
LPDIRECTINPUT8 g_pInput=NULL;//DirectInputオブジェクトへのぽいんた
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//入力デバイス(キーボード)へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];//キーボードのプレス情報
BYTE g_aOldState[NUM_KEY_MAX];
XINPUT_STATE g_joykeyState;//ジョイパッドのプレス情報
XINPUT_STATE g_Oldjoykeystate;

//キーボードの入力処理
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//キーボードの終了処理
void UninitKeyboard(void)
{
	//入力デバイス(キーボード)の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();//キーボードへのアクセス権を放棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの攻撃
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//キーボードの更新処理
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力処理
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];//ひとつ前のキーボードプレス情報を保存
	}

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//キーボードのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();//キーボードへのアクセス権を獲得
	}
}
bool GetKeyboardPress(int Key)
{
	return (g_aKeyState[Key] & 0x80) ? true : false;
}
bool KeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger=true;
	}
	return Trigger;
}
bool KeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
bool KeyboardRepeat(int nKey)
{
	bool Trigger = true;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//ジョイパッドの初期化処理
HRESULT InitJoypad(void)
{
	//メモのクリア
	memset(&g_joykeyState, 0, sizeof(XINPUT_STATE));

	//xinputのステートを有効にする
	XInputEnable(true);

	return S_OK;
}
//ジョイパッドの終了処理
void UninitJoypad(void)
{
	//XInputのステートを無効にする
	XInputEnable(false);
}
//ジョイパッドの更新処理
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//ジョイパッドの初期化処理
	
	//ジョイパッドの状態取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joykeyState = joykeyState;//ジョイパッドの入力情報
	}
}
//ジョイパッドのプレス情報を取得
bool GetJoypadPress(JOYKEY key)
{
	return (g_joykeyState.Gamepad.wButtons & (0x01 << key))?true:false;
}
//ジョイパッドのトリガー処理
bool JoyPadTrigger(JOYKEY key)
{
	bool Trigger = false;
	if (g_joykeyState.Gamepad.wButtons == (0x01 << key))
	{
		if (g_joykeyState.Gamepad.wButtons != g_Oldjoykeystate.Gamepad.wButtons)
		{
			Trigger = true;
		}
	}
	return Trigger;
}
//L2,R2
bool GetJoyTrigger(JOYKEY key)
{
	if (key == JOYKEY_L2)
	{
		return  (g_joykeyState.Gamepad.bLeftTrigger) ? true : false;
	}
	else if (key == JOYKEY_R2)
	{
		return (g_joykeyState.Gamepad.bRightTrigger) ? true : false;
	}
}
bool GetJoyTrigggerTrigger(JOYKEY key)//押したとき
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		if ((g_joykeyState.Gamepad.bLeftTrigger > 0) && !(g_Oldjoykeystate.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (JOYKEY_R2)
	{
		if ((g_joykeyState.Gamepad.bRightTrigger > 0) && !(g_Oldjoykeystate.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}
	}
	return JoyStick;
}
bool GetJoyTriggerRelease(JOYKEY key)//離したとき
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		if ((g_joykeyState.Gamepad.bLeftTrigger > 0) && !(g_joykeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_R2)
	{
		if ((g_joykeyState.Gamepad.bRightTrigger > 0) && !(g_joykeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}
	}
	return JoyStick;
}
//スティック処理
bool GetJoyStick()
{
	bool joykey = false;
	//真ん中じゃなかったら
	if (g_joykeyState.Gamepad.sThumbLX >= 100 ||
		g_joykeyState.Gamepad.sThumbLX <= -100 ||
		g_joykeyState.Gamepad.sThumbLY >= 100 ||
		g_joykeyState.Gamepad.sThumbLY <= -100)
	{
		joykey = true;
	}
	return joykey;
}
//スティック情報の取得
XINPUT_STATE* GetJoySticAngle(void)
{
	return &g_joykeyState;
}
