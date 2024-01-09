#include "Player.h"
#include "GameManager.h"


/// <summary>
/// デストラクタ
/// </summary>
Player::~Player() {}


/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize(const Vector3& rotate, const Vector3& translate) {

	objModel_ = make_unique<Model>();
	objModel_->CreateFromObj("Player", worldTrans_);
	worldTrans_.Initialize();
	worldTrans_.rotate = rotate;
	worldTrans_.translate = translate;

	this->size_ = {
		.x = 2.0f * worldTrans_.scale.x,
		.y = 2.0f * worldTrans_.scale.y,
		.z = 4.0f * worldTrans_.scale.z,
	};

	// 移動
	move_ = { 0.0f, 0.0f, 0.0f };
	moveSpeed_ = 0.5f;

	// BulletModel
	bulletModel_ = make_unique<Model>();
	bulletModel_->CreateFromObj("PlayerBullet");

	killCount_ = 15;
	HP_ = 10;

	fireTimer_ = 5;

	SettingColliderAttributeAndMask();
}


/// <summary>
/// 更新処理
/// </summary>
void Player::Update() {

	//worldTrans_.rotate.z += 0.04f;

	// 入力処理
	JoyStateCommand();

	// 移動処理
	Move();

	SetupOBBProperties();

	worldTrans_.UpdateMatrix();

#ifdef _DEBUG

	ImGui::Begin("Player");
	ImGui::DragFloat3("Scale", &worldTrans_.scale.x, 0.01f, 0.0f, 10.0f);
	ImGui::DragFloat3("Rotate", &worldTrans_.rotate.x, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("Translate", &worldTrans_.translate.x, 0.01f);
	ImGui::DragFloat3("move", &move_.x, 0.01f);
	ImGui::DragFloat3("size", &size_.x, 0.1f);
	ImGui::DragInt("KillCount", reinterpret_cast<int*>(&killCount_), 1, 0, 20);
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
/// 衝突時コールバック関数
/// </summary>
void Player::OnCollision(uint32_t id) {

	if (id == EnemyBulletID) {
		SubtructHP(1);
	}
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

	move_ = zeroVector3;
	if (Input::PressKeys(DIK_A)) {
		move_.x = (-moveSpeed_);
	}
	if (Input::PressKeys(DIK_D)) {
		move_.x = moveSpeed_;
	}

	if (Input::IsButtonPress(joyState_, XINPUT_GAMEPAD_DPAD_LEFT)) {
		move_.x = (-moveSpeed_);
	}
	if (Input::IsButtonPress(joyState_, XINPUT_GAMEPAD_DPAD_RIGHT)) {
		move_.x = moveSpeed_;
	}



	if (Input::PressKeys(DIK_SPACE)) {
		fireTimer_--;
		if (fireTimer_ <= 0) {
			fireTimer_ = 5;
			PushBackBullet();
		}
	}

	if (Input::IsButtonPress(joyState_, XINPUT_GAMEPAD_B)) {
		fireTimer_--;
		if (fireTimer_ <= 0) {
			fireTimer_ = 5;
			PushBackBullet();
		}
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



/// <summary>
/// バレットリストの登録
/// </summary>
void Player::PushBackBullet() {

	PlayerBullet* newBullet = new PlayerBullet();
	Vector3 newPos = worldTrans_.GetWorldPos();
	Vector3 newVel = TransformNormal({ 0.0f, 0.0f, kBulletSpeed_ }, worldTrans_.matWorld);

	newBullet->Init((*bulletModel_), newPos, newVel);
	newBullet->SetPlayer(this);

	gameScene_->AddPlayerBulletList(newBullet);
}



/// <summary>
/// OBBのセッティング
/// </summary>
void Player::SetupOBBProperties() {

	this->size_ = {
		.x = 2.0f * worldTrans_.scale.x,
		.y = 2.0f * worldTrans_.scale.y,
		.z = 4.0f * worldTrans_.scale.z,
	};

	OBBCollider::SetSize(this->size_);
	OBBCollider::SetRotate(this->worldTrans_.rotate);
}



/// <summary>
/// フィルターのセッティング
/// </summary>
void Player::SettingColliderAttributeAndMask() {

	OBBCollider::SetCollosionAttribute(kCollisionAttributePlayer);
	OBBCollider::SetCollisionMask(kCollisionMaskPlayer);
}
