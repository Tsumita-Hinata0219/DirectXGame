#include "Skydome.h"



/// <summary>
/// インスタンス取得
/// </summary>
Skydome* Skydome::GetInstance() {
	static Skydome instance;
	return &instance;
}


/// <summary>
/// 初期化処理
/// </summary>
void Skydome::Initialize() {

	Skydome::GetInstance()->model_ = make_unique<Model>();
	Skydome::GetInstance()->model_->CreateFromObj("Skydome");
	Skydome::GetInstance()->worldTrans_.Initialize();
	Skydome::GetInstance()->worldTrans_.scale = { 500.0f, 500.0f, 500.0f };
}


/// <summary>
/// 更新処理
/// </summary>
void Skydome::Update() {

	Skydome::GetInstance()->worldTrans_.UpdateMatrix();
}



/// <summary>
/// 描画処理
/// </summary>
void Skydome::Draw(ViewProjection view) {

	Skydome::GetInstance()->model_->Draw(Skydome::GetInstance()->worldTrans_, view);
}
