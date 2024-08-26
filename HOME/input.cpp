#include"input.h"
//�}�N����`
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput=NULL;//DirectInput�I�u�W�F�N�g�ւ̂ۂ���
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̃v���X���
BYTE g_aOldState[NUM_KEY_MAX];
XINPUT_STATE g_joykeyState;//�W���C�p�b�h�̃v���X���
XINPUT_STATE g_Oldjoykeystate;

//�L�[�{�[�h�̓��͏���
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//�L�[�{�[�h�̏I������
void UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();//�L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̍U��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//�L�[�{�[�h�̍X�V����
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏���
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];//�ЂƂO�̃L�[�{�[�h�v���X����ۑ�
	}

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
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
//�W���C�p�b�h�̏���������
HRESULT InitJoypad(void)
{
	//�����̃N���A
	memset(&g_joykeyState, 0, sizeof(XINPUT_STATE));

	//xinput�̃X�e�[�g��L���ɂ���
	XInputEnable(true);

	return S_OK;
}
//�W���C�p�b�h�̏I������
void UninitJoypad(void)
{
	//XInput�̃X�e�[�g�𖳌��ɂ���
	XInputEnable(false);
}
//�W���C�p�b�h�̍X�V����
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//�W���C�p�b�h�̏���������
	
	//�W���C�p�b�h�̏�Ԏ擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joykeyState = joykeyState;//�W���C�p�b�h�̓��͏��
	}
}
//�W���C�p�b�h�̃v���X�����擾
bool GetJoypadPress(JOYKEY key)
{
	return (g_joykeyState.Gamepad.wButtons & (0x01 << key))?true:false;
}
//�W���C�p�b�h�̃g���K�[����
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
bool GetJoyTrigggerTrigger(JOYKEY key)//�������Ƃ�
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
bool GetJoyTriggerRelease(JOYKEY key)//�������Ƃ�
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
//�X�e�B�b�N����
bool GetJoyStick()
{
	bool joykey = false;
	//�^�񒆂���Ȃ�������
	if (g_joykeyState.Gamepad.sThumbLX >= 100 ||
		g_joykeyState.Gamepad.sThumbLX <= -100 ||
		g_joykeyState.Gamepad.sThumbLY >= 100 ||
		g_joykeyState.Gamepad.sThumbLY <= -100)
	{
		joykey = true;
	}
	return joykey;
}
//�X�e�B�b�N���̎擾
XINPUT_STATE* GetJoySticAngle(void)
{
	return &g_joykeyState;
}
