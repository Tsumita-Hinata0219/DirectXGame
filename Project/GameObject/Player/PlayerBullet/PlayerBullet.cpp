#include "PlayerBullet.h"
#include "Player/Player.h"


/// <summary>
/// 初期化処理
/// </summary>
void PlayerBullet::Init(Model& model, Vector3& position, Vector3& velocity) {

	model_ = make_unique<Model>();
	(*model_) = model;

	worldTrans_.Initialize();
	worldTrans_.translate = position;
	velocity_ = velocity;
	rotateVelocity_ = 2.0f;
	this->size_ = {
		.x = 2.0f * worldTrans_.scale.x,
		.y = 2.5f * worldTrans_.scale.y,
		.z = 2.0f * worldTrans_.scale.z,
	};

	life_.kLifeTimer = 60 * 5;
	life_.Timer = life_.kLifeTimer;
	life_.IsAlive = true;

	entityID_ = playerBulletID;

	SettingColliderAttributeAndMask();
}


/// <summary>
/// 更新処理
/// </summary>
void PlayerBullet::Update() {

	// ぐるぐる回してみる
	worldTrans_.rotate.z += rotateVelocity_;
	
	// 前方に進める
	worldTrans_.translate = Add(worldTrans_.translate, velocity_);

	// 寿命の処理
	UpdateLifeStatus();

	SetupOBBProperties();


	worldTrans_.UpdateMatrix();


#ifdef _DEBUG

	ImGui::Begin("PlayerBullet");
	ImGui::DragFloat3("Scale", &worldTrans_.scale.x, 0.01f, 0.0f, 10.0f);
	ImGui::DragFloat3("Rotate", &worldTrans_.rotate.x, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("Translate", &worldTrans_.translate.x, 0.01f);
	ImGui::DragFloat3("size", &size_.x, 0.1f);
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void PlayerBullet::Draw(ViewProjection view) {

	model_->Draw(worldTrans_, view);
}


/// <summary>
/// 衝突時コールバック関数
/// </summary>
void PlayerBullet::OnCollision(uint32_t id) {

	life_.IsAlive = false;
	life_.IsDead = true;

	if (id == EnemyID) {

		player_->SubtructKillCount(1);
	}
}


/// <summary>
/// 寿命の処理
/// </summary>
void PlayerBullet::UpdateLifeStatus() {

	life_.Timer--;

	if (life_.Timer <= 0) {
		life_.Timer = 0;
		life_.IsAlive = false;
		life_.IsDead = true;
	}
}


/// <summary>
/// OBBのセッティング
/// </summary>
void PlayerBullet::SetupOBBProperties() {

	this->size_ = {
		.x = 2.0f * worldTrans_.scale.x,
		.y = 2.5f * worldTrans_.scale.y,
		.z = 2.0f * worldTrans_.scale.z,
	};

	OBBCollider::SetSize(this->size_);
	OBBCollider::SetRotate(this->worldTrans_.rotate);
}


/// <summary>
/// フィルターのセッティング
/// </summary>
void PlayerBullet::SettingColliderAttributeAndMask() {

	OBBCollider::SetCollosionAttribute(kCollisionAttributePlayer);
	OBBCollider::SetCollisionMask(kCollisionMaskPlayer);
}