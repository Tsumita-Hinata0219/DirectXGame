#include "Player.h"


/// <summary>
/// デストラクタ
/// </summary>
Player::~Player() {}


/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize() {

	objModel_ = make_unique<Model>();
	objModel_->CreateFromObj("Player", worldTrans_);
	worldTrans_.Initialize();
}


/// <summary>
/// 更新処理
/// </summary>
void Player::Update() {

	worldTrans_.UpdateMatrix();

	// 入力処理
	JoyStateCommand();

	// 移動処理
	Move();

#ifdef _DEBUG

	ImGui::Begin("Player");
	ImGui::DragFloat3("Scale", &worldTrans_.scale.x, 0.01f, 0.0f, 10.0f);
	ImGui::DragFloat3("Rotate", &worldTrans_.rotate.x, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("Translate", &worldTrans_.translate.x, 0.01f);
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void Player::Draw(ViewProjection view) {

	objModel_->Draw(worldTrans_, view);
}



/// <summary>
/// ゲームパッドの入力処理
/// </summary>
void Player::JoyStateCommand() {

	// ゲームパッドを見接続なら何もせず抜ける
	if (!Input::GetJoyStickState(joyState_)) {
		return;
	}


	if (Input::IsButtonPress(joyState_, XINPUT_GAMEPAD_Y)) {

		OutputDebugStringA("Press Button A\n");
	}
	if (Input::IsButtonTrigger(joyState_, XINPUT_GAMEPAD_B)) {

		OutputDebugStringA("Trigger Button B\n");
	}


	if (Input::GetJoyStickState(joyState_)) {
		move_.x += (float)joyState_.Gamepad.sThumbLX / SHRT_MAX * moveSpeed_;
		move_.y += (float)joyState_.Gamepad.sThumbLY / SHRT_MAX * moveSpeed_;
	}
	else {
		move_ = { 0.0f, 0.0f, 0.0f };
	}

}



/// <summary>
/// 移動処理
/// </summary>
void Player::Move() {

	// 範囲を超えない処理
	worldTrans_.translate.x = max(worldTrans_.translate.x, -kMoveLimitX);
	worldTrans_.translate.x = min(worldTrans_.translate.x, +kMoveLimitX);
	worldTrans_.translate.y = max(worldTrans_.translate.y, -kMoveLimitY);
	worldTrans_.translate.y = min(worldTrans_.translate.y, +kMoveLimitY);

	// 移動行列に移動ベクトルを加算
	worldTrans_.translate = Add(worldTrans_.translate, move_);
}