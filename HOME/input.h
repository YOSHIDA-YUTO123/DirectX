#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);

void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);

HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool JoyPadTrigger(JOYKEY key);
bool GetJoyTrigger(JOYKEY key);
bool GetJoyTriggerTrigger(JOYKEY key);
bool GetJoyTriggerRelease(JOYKEY key);
//�X�e�B�b�N
bool GetJoyStick(void);
XINPUT_STATE* GetJoySticAngle(void);
#endif
