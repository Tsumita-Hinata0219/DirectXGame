#include "Manual.h"


/// <summary>
/// インスタンス取得
/// </summary>
Manual* Manual::GetInstance() {
	static Manual instance;
	return &instance;
}


/// <summary>
/// 初期化処理
/// </summary>
void Manual::Initialize() {

	Manual::GetInstance()->model_ = make_unique<Model>();
	Manual::GetInstance()->model_->CreateFromObj("Manual");
	Manual::GetInstance()->worldTrans_.Initialize();
	Manual::GetInstance()->worldTrans_.scale = { 60.0f, 60.0f, 60.0f };
	Manual::GetInstance()->worldTrans_.rotate = { 0.0f, 0.0f, 0.0f };
	Manual::GetInstance()->worldTrans_.translate = { 00.0f, 20.0f, 400.0f };
}


/// <summary>
/// 更新処理
/// </summary>
void Manual::Update() {

	Manual::GetInstance()->worldTrans_.UpdateMatrix();
}



/// <summary>
/// 描画処理
/// </summary>
void Manual::Draw(ViewProjection view) {

	Manual::GetInstance()->model_->Draw(Manual::GetInstance()->worldTrans_, view);
}
