#include "Input.h"



/// <summary>
/// インスタンスの取得
/// </summary>
Input* Input::GetInstance() {
	static Input instance;
	return &instance;
}



/// <summary>
/// 初期化処理
/// </summary>
void Input::Initialize() {

	// DirectInputのインスタンス生成
	HRESULT result = DirectInput8Create(
		WinApp::GetWc().hInstance, DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (void**)&Input::GetInstance()->directInput_, nullptr);
	assert(SUCCEEDED(result));

	// キーボードデバイス生成
	result = Input::GetInstance()->directInput_->CreateDevice(GUID_SysKeyboard, &Input::GetInstance()->keyboard_, NULL);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = Input::GetInstance()->keyboard_->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));

	// 排他制御レベルのセット
	result = Input::GetInstance()->keyboard_->SetCooperativeLevel(
		WinApp::GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}


/// <summary>
/// 更新処理
/// </summary>
void Input::BeginFrame() {

	// メモリコピー
	memcpy(Input::GetInstance()->preKeys, Input::GetInstance()->Keys, 256);

	// キーボード情報の取得開始
	Input::GetInstance()->keyboard_->Acquire();

	// 全キーの入力状態を取得する
	Input::GetInstance()->keyboard_->GetDeviceState(sizeof(Input::GetInstance()->Keys), Input::GetInstance()->Keys);
}


/// <summary>
/// 押されていない
/// </summary>
bool Input::NoneKey(uint32_t keyNum) {

	if (Input::GetInstance()->preKeys[keyNum] == 0x00 && Input::GetInstance()->Keys[keyNum] == 0x00) {
		return true;
	}
	return false;
}


/// <summary>
/// 押した瞬間
/// </summary>
bool Input::TriggerKey(uint32_t keyNum) {

	if (Input::GetInstance()->preKeys[keyNum] == 0x00 && Input::GetInstance()->Keys[keyNum] == 0x80) {
		return true;
	}
	return false;
}


/// <summary>
/// 押しっぱなし
/// </summary>
bool Input::PressKeys(uint32_t keyNum) {

	if (Input::GetInstance()->preKeys[keyNum] == 0x80 && Input::GetInstance()->Keys[keyNum] == 0x80) {
		return true;
	}
	return false;
}


/// <summary>
/// 離された瞬間
/// </summary>
bool Input::ReleaseKeys(uint32_t keyNum) {

	if (Input::GetInstance()->preKeys[keyNum] == 0x80 && Input::GetInstance()->Keys[keyNum] == 0x00) {
		return true;
	}
	return false;
}