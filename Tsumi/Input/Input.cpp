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

	// 各ボタンのトリガー状態の初期化処理
	Input::GetInstance()->ResetButtonTriggers();
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

	// ジョイスティックの状態をポーリング
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
	}
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



 /// <summary>
 /// ジョイコンの入力の取得
 /// </summary>
bool Input::GetJoyStickState(XINPUT_STATE& state) {

	DWORD dwresult = XInputGetState(0, &state);

	if (dwresult == ERROR_SUCCESS) {
		return true;
	}
	return false;
}



/// <summary>
/// 押された瞬間
/// </summary>
bool Input::IsButtonTrigger(const XINPUT_STATE& state, WORD button) {

	// ボタンが押された瞬間だけを判定
	return((state.Gamepad.wButtons & button) != 0) && ((Input::GetInstance()->buttonTriggers[button] & button) == 0);
}



/// <summary>
/// ボタンが押されたら
/// </summary>
bool Input::IsButtonPress(const XINPUT_STATE& state, WORD button) {

	// 指定されたボタンが押されているか確認
	return (state.Gamepad.wButtons & button) != 0;
}



/// <summary>
/// 各ボタンのトリガー状態の初期化処理
/// </summary>
void Input::ResetButtonTriggers() {

	ZeroMemory(buttonTriggers, sizeof(buttonTriggers));
}