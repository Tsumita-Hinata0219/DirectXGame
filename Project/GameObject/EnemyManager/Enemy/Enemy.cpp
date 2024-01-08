#include "Enemy.h"



/// <summary>
/// 初期化処理
/// </summary>
void Enemy::Init(Vector3 position, Vector3 move) {

	object_ = make_unique<Model>();
	object_->CreateFromObj("Enemy");

	worldTransform_.Initialize();
	worldTransform_.translate = position;

	move_ = move;

	isMoveStart_ = true;
	isMoveFinish_ = false;
}



/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {

	worldTransform_.UpdateMatrix();
	//MoveToSpecificPos();


	//if (Input::PushKeyPressed(DIK_1)) {
	//	isMoveStart_ = true;
	//	isMoveFinish_ = false;
	//}


#ifdef _DEBUG


#endif // _DEBUG

}



/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw(ViewProjection view) {

	object_->Draw(worldTransform_, view);
}



/// <summary>
/// 移動処理
/// </summary>
void Enemy::MoveToSpecificPos() {

	if (isMoveStart_) {

		Vector3 toSpecificPosition = {
			.x = specificPosition_.x - worldTransform_.translate.x,
			.y = specificPosition_.y - worldTransform_.translate.y,
			.z = specificPosition_.z - worldTransform_.translate.z,
		};

		float distance = sqrt(
			(toSpecificPosition.x * toSpecificPosition.x) +
			(toSpecificPosition.y * toSpecificPosition.y) +
			(toSpecificPosition.z * toSpecificPosition.z));

		vel_ = {
		.x = toSpecificPosition.x / distance * move_.x,
		.y = toSpecificPosition.y / distance * move_.y,
		.z = toSpecificPosition.z / distance * move_.z,
		};

		worldTransform_.translate = Add(worldTransform_.translate, vel_);

		if (distance < 1.0f) {

			isMoveStart_ = false;
			isMoveFinish_ = true;
		}
	}
}