#include "Enemy.h"
#include "GameManager.h"


/// <summary>
/// 初期化処理
/// </summary>
void Enemy::Init(Model& model, Model& modelBullet, Vector3 position, Vector3 velocity) {

	modle_ = make_unique<Model>();
	(*modle_) = model;
	modleBullet_ = make_unique<Model>();
	(*modleBullet_) = modelBullet;

	worldTrans_.Initialize();
	worldTrans_.scale = { 2.0f, 2.0f, 2.0f };
	worldTrans_.translate = position;
	velocity_ = velocity;
	moveSpeed_ = 1.0f;
	bulletVel_ = { 0.0f, 0.0f, kBulletSpeed_ };
	bullet_.FireInterval = 80;
	bullet_.FireTimer = int32_t(RandomGenerator::getRandom({ 5.0f, 300.0f }));

	initMoveFlag_ = false;

	phaseState_ = new IEnemyApproachState();
}


/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {

	// ステートパターンによるフェーズ処理
	phaseState_->Update(this);

	playerWorldPos_ = player_->GetWorldTransform().GetWorldPos();

	worldTrans_.UpdateMatrix();


#ifdef _DEBUG


#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw(ViewProjection view) {

	modle_->Draw(worldTrans_, view);
}


/// <summary>
/// フェーズの変更
/// </summary>
void Enemy::ChangePhaseState(IEnemyPhaseState* newState) {

	delete phaseState_;
	phaseState_ = newState;
}


/// <summary>
/// ステートパターン内で使用する移動用関数(加算 減算) 
/// </summary>
void Enemy::Approach2BattlePosition() {

	if (!initMoveFlag_) {
		worldTrans_.translate = Subtract(worldTrans_.translate, { 0.0f, 1.0f, 0.0f });
	}

	if (worldTrans_.translate.y <= 0.0f) {
		initMoveFlag_ = true;
	}
}


/// <summary>
/// 攻撃処理
/// </summary>
void Enemy::Attack() {

	bullet_.FireTimer--;

	if (bullet_.FireTimer <= 0) {

		FirePreparation();
		FireBullet();
		bullet_.FireTimer = bullet_.FireInterval;
	}
}


/// <summary>
/// 射撃準備処理
/// </summary>
void Enemy::FirePreparation() {

	assert(player_);

	Vector3 plaWorldPos = player_->GetWorldTransform().GetWorldPos();
	Vector3 eneWorldPos = worldTrans_.GetWorldPos();

	Vector3 toPlayer = Subtract(plaWorldPos, eneWorldPos);
	toPlayer = Normalize(toPlayer);

	bulletVel_ = {
		toPlayer.x * kBulletSpeed_,
		toPlayer.y * kBulletSpeed_,
		toPlayer.z * kBulletSpeed_,
	};

	bulletVel_ = TransformNormal(bulletVel_, worldTrans_.matWorld);
}


/// <summary>
/// 弾の射撃処理
/// </summary>
void Enemy::FireBullet() {

	EnemyBullet* newBullet = new EnemyBullet();
	Vector3 newPos = worldTrans_.translate;
	Vector3 newVal = bulletVel_;


	newBullet->Init((*modleBullet_), newPos, newVal);

	gameScene_->AddEnemyBulletList(newBullet);
}