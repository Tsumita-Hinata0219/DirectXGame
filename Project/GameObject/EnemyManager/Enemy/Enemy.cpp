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
}


/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {

	// 後方に進める
	worldTrans_.translate = Add(worldTrans_.translate, velocity_);


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


