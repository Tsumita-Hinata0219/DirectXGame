#include "EnemyBullet.h"



/// <summary>
/// 初期化処理
/// </summary>
void EnemyBullet::Init(Model& model, Vector3& position, Vector3& velocity) {

	model_ = make_unique<Model>();
	(*model_) = model;

	worldTrans_.Initialize();
	worldTrans_.translate = position;
	velocity_ = velocity;
	rotateVelocity_ = 0.02f;

	life_.kLifeTimer = 60 * 10;
	life_.Timer = life_.kLifeTimer;
	life_.IsAlive = true;
	life_.IsDead = false;

	this->size_ = {
		.x = 2.0f * worldTrans_.scale.x,
		.y = 2.0f * worldTrans_.scale.y,
		.z = 0.4f * worldTrans_.scale.z,
	};

	Vector3 kVelocity = velocity_;
	float velocityZ_ = sqrt((kVelocity.x * kVelocity.x) + (kVelocity.z * kVelocity.z));
	float height_ = -kVelocity.y;
	worldTrans_.rotate.y = std::atan2(kVelocity.x, kVelocity.z);
	worldTrans_.rotate.x = std::atan2(height_, velocityZ_);

	SettingColliderAttributeAndMask();
}


/// <summary>
/// 更新処理
/// </summary>
void EnemyBullet::Update() {

	// ぐるぐる回してみる
	worldTrans_.rotate.x += rotateVelocity_;

	// 前方に進める
	worldTrans_.translate = Add(worldTrans_.translate, velocity_);

	// 寿命の処理
	UpdateLifeStatus();

	SetupOBBProperties();

	worldTrans_.UpdateMatrix();
}


/// <summary>
/// 描画処理
/// </summary>
void EnemyBullet::Draw(ViewProjection view) {

	model_->Draw(worldTrans_, view);
}



/// <summary>
/// 衝突時コールバック関数
/// </summary>
void EnemyBullet::OnCollision(uint32_t id) {

	life_.IsAlive = false;
	life_.IsDead = true;
}



/// <summary>
/// 寿命の処理
/// </summary>
void EnemyBullet::UpdateLifeStatus() {

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
void EnemyBullet::SetupOBBProperties() {

	this->size_ = {
		.x = 2.0f * worldTrans_.scale.x,
		.y = 2.0f * worldTrans_.scale.y,
		.z = 0.4f * worldTrans_.scale.z,
	};

	OBBCollider::SetSize(this->size_);
	OBBCollider::SetRotate(this->worldTrans_.rotate);
}



/// <summary>
/// フィルターのセッティング
/// </summary>
void EnemyBullet::SettingColliderAttributeAndMask() {

	OBBCollider::SetCollosionAttribute(kCollisionAttributeEnemy);
	OBBCollider::SetCollisionMask(kCollisionMaskEnemy);
}