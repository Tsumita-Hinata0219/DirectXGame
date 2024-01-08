#include "Enemy.h"



/// <summary>
/// 初期化処理
/// </summary>
void Enemy::Init(Model& model, Vector3 position, Vector3 velocity) {

	modle_ = make_unique<Model>();
	(*modle_) = model;	

	worldTrans_.Initialize();
	worldTrans_.translate = position;
	velocity_ = velocity;

	phaseState_ = new IEnemyApproachState();
}


/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {

	// ステートパターンによるフェーズ処理
	phaseState_->Update(this);


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
void Enemy::AddTransform(const Vector3& velocity) {

	worldTrans_.translate = Add(worldTrans_.translate, velocity);
}
void Enemy::SubtractTransform(const Vector3& velocity) {

	worldTrans_.translate = Subtract(worldTrans_.translate, velocity);
}