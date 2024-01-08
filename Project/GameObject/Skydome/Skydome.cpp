#include "Skydome.h"


/// <summary>
/// 初期化処理
/// </summary>
void Skydome::Initialize() {

	model_ = make_unique<Model>();
	model_->CreateFromObj("Skydome");
	worldTrans_.Initialize();
	worldTrans_.scale = { 500.0f, 500.0f, 500.0f };
}


/// <summary>
/// 更新処理
/// </summary>
void Skydome::Update() {

	worldTrans_.UpdateMatrix();
}



/// <summary>
/// 描画処理
/// </summary>
void Skydome::Draw(ViewProjection view) {

	model_->Draw(worldTrans_, view);
}
