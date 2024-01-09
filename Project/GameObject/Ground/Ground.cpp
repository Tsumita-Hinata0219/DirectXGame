#include "Ground.h"



/// <summary>
/// インスタンスの取得
/// </summary>
Ground* Ground::GetInstance() {
	static Ground instance;
	return &instance;
}


/// <summary>
/// 初期化処理
/// </summary>
void Ground::Initialize() {

	Ground::GetInstance()->model_ = make_unique<Model>();
	Ground::GetInstance()->model_->CreateFromObj("Ground");
	Ground::GetInstance()->worldTrans_.Initialize();
}


/// <summary>
/// 更新処理
/// </summary>
void Ground::Update() {

	Ground::GetInstance()->worldTrans_.UpdateMatrix();
}



/// <summary>
/// 描画処理
/// </summary>
void Ground::Draw(ViewProjection view) {

	Ground::GetInstance()->model_->Draw(Ground::GetInstance()->worldTrans_, view);
}
