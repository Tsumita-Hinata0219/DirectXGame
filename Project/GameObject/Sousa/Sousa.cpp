#include "Sousa.h"

/// <summary>
/// インスタンス取得
/// </summary>
Sousa* Sousa::GetInstance() {
	static Sousa instance;
	return &instance;
}


/// <summary>
/// 初期化処理
/// </summary>
void Sousa::Initialize() {

	Sousa::GetInstance()->model_ = make_unique<Model>();
	Sousa::GetInstance()->model_->CreateFromObj("Sousa");
	Sousa::GetInstance()->worldTrans_.Initialize();
	Sousa::GetInstance()->worldTrans_.scale = { 60.0f, 60.0f, 60.0f };
	Sousa::GetInstance()->worldTrans_.rotate = { 0.0f, 0.0f, 0.0f };
	Sousa::GetInstance()->worldTrans_.translate = { 00.0f, 20.0f, 400.0f };
}


/// <summary>
/// 更新処理
/// </summary>
void Sousa::Update() {

	Sousa::GetInstance()->worldTrans_.UpdateMatrix();
}



/// <summary>
/// 描画処理
/// </summary>
void Sousa::Draw(ViewProjection view) {

	Sousa::GetInstance()->model_->Draw(Sousa::GetInstance()->worldTrans_, view);
}
