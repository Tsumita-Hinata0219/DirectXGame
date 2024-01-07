#pragma once

#define DIRECTINPUT_VERSION 0x0800 // DirectInputnoバージョン指定
#include <dinput.h>
#include <Xinput.h>
#define XUSER_MAX_COUNT 4
#define XINPUT_GAMEPAD_MAX 16

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"xinput.lib")
#pragma comment(lib, "dxguid.lib")

#include "WinApp.h"
#include "Struct.h"

#include <cassert>
#include <wrl.h>



/* Inputクラス */
class Input {

public: // メンバ関数

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static Input* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	static void BeginFrame();

	/// <summary>
	/// 押されていない
	/// </summary>
	static bool NoneKey(uint32_t keyNum);

	/// <summary>
	/// 押した瞬間
	/// </summary>
	static bool TriggerKey(uint32_t keyNum);

	/// <summary>
	/// 押しっぱなし
	/// </summary>
	static bool PressKeys(uint32_t keyNum);

	/// <summary>
	/// 離された瞬間
	/// </summary>
	static bool ReleaseKeys(uint32_t keyNum);

	/// <summary>
	/// ジョイコンの入力の取得
	/// </summary>
	static bool GetJoyStickState(XINPUT_STATE& state);

	/// <summary>
	/// 押された瞬間
	/// </summary>
	static bool IsButtonTrigger(const XINPUT_STATE& state, WORD button);

	/// <summary>
	/// 押しっぱなし
	/// </summary>
	static bool IsButtonPress(const XINPUT_STATE& state, WORD button);


private: // メンバ関数

	/// <summary>
	/// 各ボタンのトリガー状態の初期化処理
	/// </summary>
	void ResetButtonTriggers();


private: // メンバ変数

	ComPtr<IDirectInput8> directInput_ = nullptr;
	ComPtr<IDirectInputDevice8> keyboard_ = nullptr;

	BYTE Keys[256] = {};
	BYTE preKeys[256] = {};
	XINPUT_STATE joyState = {};
	WORD buttonTriggers[XINPUT_GAMEPAD_MAX];
};