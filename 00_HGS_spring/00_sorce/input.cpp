//========================================================================================
//
// ���̓f�o�C�X�̏���[input.cpp]
// Author: ��{�@�ėB
//
//========================================================================================
#include "input.h"
#include <stdio.h>

//�}�N����`
#define GAMEPAD_TRIGGER_DEADZONE (100)	//�g���K�[�̃f�b�h�]�[��
#define TRIGGER_MAX (255)	//�g���K�[�̃}�b�N�X
#define NUM_KEY_MAX (256)	//�L�[�̍ő吔
#define MAX_PLAYER (4)	//�v���C���[�̐l��

#define MOUSE_SENS (0.1f) //�}�E�X���x�̕␳

//�L�[�{�[�h
typedef struct
{
	LPDIRECTINPUTDEVICE8 pDevKeyboard = NULL; //���̓f�o�C�X�ւ̃|�C���^
	BYTE aKeyState[NUM_KEY_MAX]; //�S���͏��̕ۊ�
	BYTE aKeyStateTrigger[NUM_KEY_MAX]; //�g���K�[���
	BYTE aKeyStateRerease[NUM_KEY_MAX]; //�����[�X���
	BYTE aKeyStateRepeat[NUM_KEY_MAX]; //���s�[�g���
}KeyBoard;

//�}�E�X
typedef struct
{
	LPDIRECTINPUTDEVICE8 pDevMouse = NULL; //���̓f�o�C�X�ւ̃|�C���^
	DIMOUSESTATE2 MouseState; //�S���͏��̕ۊ�
	DIMOUSESTATE2 MouseStateTrigger; //�g���K�[���
	DIMOUSESTATE2 MouseStateRerease; //�����[�X���
	DIMOUSESTATE2 MouseStateRepeat; //���s�[�g���
	BYTE aOldState[8]; //�O��̓��͏���ۑ�
}Mouse;

//�W���C�p�b�h
typedef struct
{
	LPDIRECTINPUTDEVICE8 pDevJoypad = NULL; //���̓f�o�C�X�ւ̃|�C���^
	DIJOYSTATE aKeyState; //�S���͏��̕ۊ�
	DIJOYSTATE aKeyStateTrigger; //�g���K�[���
	DIJOYSTATE aKeyStateRerease; //�����[�X���
	DIJOYSTATE aKeyStateRepeat; //���s�[�g���
	BYTE aOldState[32]; //�O��̓��͏���ۑ�

	JOYPAD_LSTICK LStickInput;
	bool OutputDOK;
	bool OutputUOK;
	bool OutputLOK;
	bool OutputROK;
}JoyPad;

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;				//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
KeyBoard g_KeyBoard; //�L�[�{�[�h�̏��
JoyPad g_aJoyPad[MAX_PLAYER]; //�W���C�p�b�h�̏��
Mouse g_Mouse; //�}�E�X�̏��
int g_nJoyNumCnt; //�g�p����W���C�p�b�h�̃J�E���g

XINPUT_STATE g_JoyKeyState[MAX_PLAYER];
XINPUT_STATE g_JoyKeyStateTrigger[MAX_PLAYER];
XINPUT_STATE g_JoyKeyStateRelease[MAX_PLAYER];
XINPUT_VIBRATION vibration[MAX_PLAYER];
//==========================================
//  �f�o�C�X�̏�����
//==========================================
HRESULT InitDevice(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (g_pInput == nullptr)
	{
		if (FAILED(DirectInput8Create
		(
			hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&g_pInput,
			NULL
		)))
		{
			return E_FAIL;
		}
	}

	//�L�[�{�[�h
	if (FAILED(InitKeyboard(hWnd)))
	{
		return E_FAIL;
	}

	//�W���C�p�b�h
	InitGamepad(hWnd);

	//�}�E�X
	InitMouse(hWnd);

	return S_OK;
}

//==========================================
//  �f�o�C�X�̏I������
//==========================================
void UninitDevice(void)
{
	//�L�[�{�[�h
	UninitKeyboard();

	//�W���C�p�b�h
	UninitGamepad();

	//�}�E�X
	UninitMouse();

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//==========================================
//  �f�o�C�X�̍X�V����
//==========================================
void UpdateDevice(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�W���C�p�b�h�̍X�V����
	UpdateGamepad();

	//�}�E�X�̍X�V����
	UpdateMouse();
}

//====================================================================
//�L�[�{�[�h�̏���������
//====================================================================
HRESULT InitKeyboard(HWND hWnd)
{
	//���̓f�o�C�X�̐ݒ�
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_KeyBoard.pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_KeyBoard.pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_KeyBoard.pDevKeyboard->SetCooperativeLevel
	(
		hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)
	)))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_KeyBoard.pDevKeyboard->Acquire();

	return S_OK;
}

//====================================================================
//�L�[�{�[�h�̏I������
//====================================================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_KeyBoard.pDevKeyboard != NULL)
	{
		g_KeyBoard.pDevKeyboard->Unacquire();
		g_KeyBoard.pDevKeyboard->Release();
		g_KeyBoard.pDevKeyboard = NULL;
	}
}

//====================================================================
//�L�[�{�[�h�̍X�V����
//====================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX]; //�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_KeyBoard.pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_KeyBoard.aKeyStateRerease[nCntKey] = ~aKeyState[nCntKey] & ((g_KeyBoard.aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_KeyBoard.aKeyState[nCntKey]); //�L�[�{�[�h�̃����[�X����ۑ�
			g_KeyBoard.aKeyStateTrigger[nCntKey] = (g_KeyBoard.aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //�L�[�{�[�h�̃g���K�[���̕ۑ�
			g_KeyBoard.aKeyState[nCntKey] = aKeyState[nCntKey]; //�L�[�{�[�h�̃v���X���̕ۑ�
		}
	}
	else
	{
		g_KeyBoard.pDevKeyboard->Acquire(); //�L�[�{�[�h�̃A�N�Z�X��
	}
}

//====================================================================
//�L�[�{�[�h�̃v���X��������
//====================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_KeyBoard.aKeyState[nKey] & 0x80) ? true : false;
}

//====================================================================
//�L�[�{�[�h�̃g���K�[��������
//====================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_KeyBoard.aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//====================================================================
//�L�[�{�[�h�̃����[�X��������
//====================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_KeyBoard.aKeyStateRerease[nKey] & 0x80) ? true : false;
}

//====================================================================
//�Q�[���p�b�h�̏���������
//====================================================================
HRESULT InitGamepad(HWND hWnd)
{
	//Xinput�̃X�e�[�g�̐ݒ�
	XInputEnable(true);
	int nCount;

	for (nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		//�������[���N���A����
		memset(&g_JoyKeyState[nCount], 0, sizeof(XINPUT_STATE));
		memset(&g_JoyKeyStateTrigger[nCount], 0, sizeof(XINPUT_STATE));
		memset(&g_JoyKeyStateRelease[nCount], 0, sizeof(XINPUT_STATE));

		g_aJoyPad[MAX_PLAYER].LStickInput = LSTICK_UP;
		g_aJoyPad[MAX_PLAYER].OutputDOK = false;
		g_aJoyPad[MAX_PLAYER].OutputUOK = false;
		g_aJoyPad[MAX_PLAYER].OutputLOK = false;
		g_aJoyPad[MAX_PLAYER].OutputROK = false;
	}
	return S_OK;
}

//====================================================================
//�Q�[���p�b�h�̏I������
//====================================================================
void UninitGamepad(void)
{
	//Xinput�̃X�e�[�g�̐ݒ�
	XInputEnable(false);
}

//====================================================================
//�Q�[���p�b�h�̍X�V����
//====================================================================
void UpdateGamepad(void)
{
	XINPUT_STATE aGamepadState[MAX_PLAYER];	//�Q�[���p�b�h�̓��͏���
	static int nCountSpece = 0;
	int nCntPad = 0;

	for (nCntPad = 0; nCntPad < MAX_PLAYER; nCntPad++)
	{
		//���̓f�o�C�X����f�[�^������
		if (XInputGetState(nCntPad, &aGamepadState[nCntPad]) == ERROR_SUCCESS)
		{
			g_JoyKeyStateTrigger[nCntPad].Gamepad.wButtons =
				~g_JoyKeyState[nCntPad].Gamepad.wButtons
				& aGamepadState[nCntPad].Gamepad.wButtons;	//�g���K�[

			g_JoyKeyStateRelease[nCntPad].Gamepad.wButtons =
				((g_JoyKeyState[nCntPad].Gamepad.wButtons
					^ aGamepadState[nCntPad].Gamepad.wButtons)
					& g_JoyKeyState[nCntPad].Gamepad.wButtons);	//�����[�X

			g_JoyKeyStateTrigger[nCntPad].Gamepad.bLeftTrigger =
				~g_JoyKeyState[nCntPad].Gamepad.bLeftTrigger
				& aGamepadState[nCntPad].Gamepad.bLeftTrigger;	//�g���K�[

			g_JoyKeyStateTrigger[nCntPad].Gamepad.bRightTrigger =
				~g_JoyKeyState[nCntPad].Gamepad.bRightTrigger
				& aGamepadState[nCntPad].Gamepad.bRightTrigger;	//�g���K�[

																//g_JoyKeyStateTrigger[nCntPad].Gamepad.bRightTrigger = aGamepadState[nCntPad].Gamepad.bRightTrigger;	//�v���X

			g_JoyKeyStateTrigger[nCntPad].Gamepad.sThumbLY =
				~g_JoyKeyState[nCntPad].Gamepad.sThumbLY
				& aGamepadState[nCntPad].Gamepad.sThumbLY;	//�g���K�[

			g_JoyKeyStateTrigger[nCntPad].Gamepad.sThumbLX =
				~g_JoyKeyState[nCntPad].Gamepad.sThumbLX
				& aGamepadState[nCntPad].Gamepad.sThumbLX;	//�g���K�[

			g_JoyKeyStateRelease[nCntPad].Gamepad.sThumbLY =
				((g_JoyKeyState[nCntPad].Gamepad.sThumbLY
					^ aGamepadState[nCntPad].Gamepad.sThumbLY)
					& g_JoyKeyState[nCntPad].Gamepad.sThumbLY);	//�����[�X

			g_JoyKeyState[nCntPad] = aGamepadState[nCntPad];	//�v���X
		}
	}
}

//====================================================================
//�Q�[���p�b�h�̃v���X��������
//====================================================================
bool GetGamepadPress(JOYKEY key, int nPlayer)
{
	return (g_JoyKeyState[nPlayer].Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//====================================================================
//�Q�[���p�b�h�̃g���K�[��������
//====================================================================
bool GetGamepadTrigger(JOYKEY key, int nPlayer)
{
	return (g_JoyKeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//====================================================================
//�Q�[���p�b�h�̃����[�X��������
//====================================================================
bool GetGamepadRelease(JOYKEY key, int nPlayer)
{
	return (g_JoyKeyStateRelease[nPlayer].Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//====================================================================
//�Q�[���p�b�h��L�X�e�B�b�N�̏�������
//====================================================================
D3DXVECTOR3 GetGamepad_Stick_Left(int nPlayer)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 Stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Stick.x = (float)g_JoyKeyState[nPlayer].Gamepad.sThumbLX / (float)SHRT_MAX;
	//if (fabsf(Stick.x) < (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / (float)SHRT_MAX)
	//{
	//	Stick.x = 0.0f;
	//}

	Stick.y = (float)g_JoyKeyState[nPlayer].Gamepad.sThumbLY / (float)SHRT_MAX;
	//if (fabsf(Stick.y) < (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / (float)SHRT_MAX)
	//{
	//	Stick.y = 0.0f;
	//}

	if (Stick.x > 0.5f || Stick.x < -0.5f &&Stick.y > 0.5f || Stick.x < -0.5f)
	{
		D3DXVec3Normalize(&Stick, &Stick);	//�x�N�g���𐳋K������
	}

	return Stick;
}

//====================================================================
//�Q�[���p�b�h��L�X�e�B�b�N�̏�������
//====================================================================
bool GetGamepad_LStick_Trigger(int nPlayer, JOYPAD_LSTICK Type)
{
	//���[�J���ϐ��錾
	float StickX = 0.0f;
	float StickY = 0.0f;
	bool Output = false;

	StickX = (float)g_JoyKeyState[nPlayer].Gamepad.sThumbLX / (float)SHRT_MAX;
	if (fabsf(StickX) < (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / (float)SHRT_MAX)
	{
		StickX = 0.0f;
	}

	StickY = (float)g_JoyKeyState[nPlayer].Gamepad.sThumbLY / (float)SHRT_MAX;
	if (fabsf(StickY) < (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / (float)SHRT_MAX)
	{
		StickY = 0.0f;
	}

	switch (Type)
	{
	case LSTICK_UP:
		if (StickY >= 0.8f)
		{
			if (g_aJoyPad[nPlayer].OutputUOK == false)
			{
				Output = true;
				g_aJoyPad[nPlayer].OutputUOK = true;
			}
		}
		else
		{
			g_aJoyPad[nPlayer].OutputUOK = false;
		}
		break;

	case LSTICK_DOWN:

		if (StickY <= -0.8f)
		{
			if (g_aJoyPad[nPlayer].OutputDOK == false)
			{
				Output = true;
				g_aJoyPad[nPlayer].OutputDOK = true;
			}
		}
		else
		{
			g_aJoyPad[nPlayer].OutputDOK = false;
		}
		break;
	case LSTICK_RIGHT:

		if (StickX >= 0.8f)
		{
			if (g_aJoyPad[nPlayer].OutputROK == false)
			{
				Output = true;
				g_aJoyPad[nPlayer].OutputROK = true;
			}
		}
		else
		{
			g_aJoyPad[nPlayer].OutputROK = false;
		}
		break;

	case LSTICK_LEFT:
		if (StickX <= -0.8f)
		{
			if (g_aJoyPad[nPlayer].OutputLOK == false)
			{
				Output = true;
				g_aJoyPad[nPlayer].OutputLOK = true;
			}
		}
		else
		{
			g_aJoyPad[nPlayer].OutputLOK = false;
		}
		break;
	}

	return Output;
}

//====================================================================
//�Q�[���p�b�h��L�X�e�B�b�N�̏�������
//====================================================================
bool GetGamepad_LStick_DOWN(int nPlayer)
{
	//���[�J���ϐ��錾
	float Stick = 0.0f;
	bool Output = false;

	Stick = (float)g_JoyKeyState[nPlayer].Gamepad.sThumbLY / (float)SHRT_MAX;
	if (fabsf(Stick) < (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / (float)SHRT_MAX)
	{
		Stick = 0.0f;
	}

	if (Stick <= -0.8f)
	{
		if (g_aJoyPad[nPlayer].OutputDOK == false)
		{
			Output = true;
			g_aJoyPad[nPlayer].OutputDOK = true;
		}
	}
	else
	{
		g_aJoyPad[nPlayer].OutputDOK = false;
	}

	return Output;
}

//====================================================================
//�Q�[���p�b�h��L�X�e�B�b�N�̏�������
//====================================================================
bool GetGamepad_LStick_RIGHT(int nPlayer)
{
	//���[�J���ϐ��錾
	float Stick = 0.0f;
	bool Output = false;

	Stick = (float)g_JoyKeyState[nPlayer].Gamepad.sThumbLX / (float)SHRT_MAX;
	if (fabsf(Stick) < (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / (float)SHRT_MAX)
	{
		Stick = 0.0f;
	}

	if (Stick >= 0.8f)
	{
		if (g_aJoyPad[nPlayer].OutputROK == false)
		{
			Output = true;
			g_aJoyPad[nPlayer].OutputROK = true;
		}
	}
	else
	{
		g_aJoyPad[nPlayer].OutputROK = false;
	}

	return Output;
}

//====================================================================
//�Q�[���p�b�h��L�X�e�B�b�N�̏�������
//====================================================================
bool GetGamepad_LStick_LEFT(int nPlayer)
{
	//���[�J���ϐ��錾
	float Stick = 0.0f;
	bool Output = false;

	Stick = (float)g_JoyKeyState[nPlayer].Gamepad.sThumbLX / (float)SHRT_MAX;
	if (fabsf(Stick) < (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / (float)SHRT_MAX)
	{
		Stick = 0.0f;
	}

	if (Stick >= 0.8f)
	{
		if (g_aJoyPad[nPlayer].OutputLOK == false)
		{
			Output = true;
			g_aJoyPad[nPlayer].OutputLOK = true;
		}
	}
	else
	{
		g_aJoyPad[nPlayer].OutputLOK = false;
	}

	return Output;
}

//====================================================================
//�Q�[���p�b�h��R�X�e�B�b�N�̏�������
//====================================================================
D3DXVECTOR3 GetGamepad_Stick_Right(int nPlayer)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 Stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Stick.x = (float)g_JoyKeyState[nPlayer].Gamepad.sThumbRX / (float)SHRT_MAX;
	if (fabsf(Stick.x) < (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / (float)SHRT_MAX)
	{
		Stick.x = 0.0f;
	}

	Stick.y = (float)g_JoyKeyState[nPlayer].Gamepad.sThumbRY / (float)SHRT_MAX;
	if (fabsf(Stick.y) < (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / (float)SHRT_MAX)
	{
		Stick.y = 0.0f;
	}

	if (Stick.x > 0.5f || Stick.x < -0.5f &&Stick.y > 0.5f || Stick.x < -0.5f)
	{
		D3DXVec3Normalize(&Stick, &Stick);	//�x�N�g���𐳋K������
	}

	return Stick;
}

//====================================================================
//�Q�[���p�b�h��L�g���K�[�̏�������
//====================================================================
float GetGamepad_Trigger_Left(int nPlayer)
{
	//���[�J���ϐ��錾
	float Trigger = 0.0f;

	Trigger = (float)g_JoyKeyState[nPlayer].Gamepad.bLeftTrigger / (float)TRIGGER_MAX;
	if (fabsf(Trigger) < (float)GAMEPAD_TRIGGER_DEADZONE / (float)TRIGGER_MAX)
	{
		Trigger = 0.0f;
	}

	return Trigger;
}

//====================================================================
//�Q�[���p�b�h��R�g���K�[�̏�������
//====================================================================
float GetGamepad_Trigger_Right(int nPlayer)
{
	//���[�J���ϐ��錾
	float Trigger = 0.0f;

	Trigger = (float)g_JoyKeyState[nPlayer].Gamepad.bRightTrigger / (float)TRIGGER_MAX;
	if (fabsf(Trigger) < (float)GAMEPAD_TRIGGER_DEADZONE / (float)TRIGGER_MAX)
	{
		Trigger = 0.0f;
	}

	return Trigger;
}

//====================================================================
//�Q�[���p�b�h�̃o�C�u���[�V�����̏���
//====================================================================
void GetGamepad_Vibrtion(int nPlayer, int nLeftPower, int RightPoewr)
{
	vibration[nPlayer].wLeftMotorSpeed = nLeftPower;
	vibration[nPlayer].wRightMotorSpeed = RightPoewr;
	XInputSetState(nPlayer, &vibration[nPlayer]);
}

//====================================================================
//�Q�[���p�b�h�̃o�C�u���[�V��������
//====================================================================
void GetGamepad_Vibrtion_false(int nPlayer)
{
	XINPUT_VIBRATION vibrationDef;

	vibrationDef.wLeftMotorSpeed = 0;
	vibrationDef.wRightMotorSpeed = 0;

	XInputSetState(nPlayer, &vibrationDef);
}

//==========================================
//  �}�E�X�̏�����
//==========================================
HRESULT InitMouse(HWND hWnd)
{
	//���̓f�o�C�X�̐ݒ�
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_Mouse.pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_Mouse.pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_Mouse.pDevMouse->SetCooperativeLevel
	(
		hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)
	)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; //���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED(g_Mouse.pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return E_FAIL;
	}

	//�}�E�X�ւ̃A�N�Z�X�����擾
	g_Mouse.pDevMouse->Acquire();

	//�}�E�X�J�[�\���̏���
	ShowCursor(false);

	return S_OK;
}

//==========================================
//  �}�E�X�̏I������
//==========================================
void UninitMouse(void)
{
	//���̓f�o�C�X(�}�E�X)�̔j��
	if (g_Mouse.pDevMouse != NULL)
	{
		g_Mouse.pDevMouse->Unacquire();
		g_Mouse.pDevMouse->Release();
		g_Mouse.pDevMouse = NULL;
	}
}

//==========================================
//  �}�E�X�̍X�V����
//==========================================
void UpdateMouse(void)
{
	DIMOUSESTATE2 mouse; //�}�E�X�̓��͏��

						 //���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_Mouse.pDevMouse->GetDeviceState(sizeof(mouse), &mouse)))
	{
		//���͏��̕ۑ�
		g_Mouse.MouseState = mouse;
	}
	else
	{
		g_Mouse.pDevMouse->Acquire(); //�}�E�X�ւ̃A�N�Z�X��
	}
}

//==========================================
//  �}�E�X�̃v���X���
//==========================================
bool GetMousePress(MOUSE_PUSH nKey)
{
	return (g_Mouse.MouseState.rgbButtons[nKey] & 0x80) ? true : false;
}

//==========================================
//  �}�E�X�̈ړ���
//==========================================
D3DXVECTOR3 GetMouseMove(void)
{
	return D3DXVECTOR3(((float)g_Mouse.MouseState.lX) * MOUSE_SENS, ((float)g_Mouse.MouseState.lY) * MOUSE_SENS, ((float)g_Mouse.MouseState.lZ) * MOUSE_SENS);
}