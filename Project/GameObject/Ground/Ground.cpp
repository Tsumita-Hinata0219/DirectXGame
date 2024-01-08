#include "Ground.h"


/// <summary>
/// 初期化処理
/// </summary>
void Ground::Initialize() {

	model_ = make_unique<Model>();
	model_->CreateFromObj("Ground");
	worldTrans_.Initialize();
}


/// <summary>
/// 更新処理
/// </summary>
void Ground::Update() {

	worldTrans_.UpdateMatrix();
}



/// <summary>
/// 描画処理
/// </summary>
void Ground::Draw(ViewProjection view) {

	model_->Draw(worldTrans_, view);
}
