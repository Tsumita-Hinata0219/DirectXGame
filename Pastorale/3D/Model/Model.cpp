#include "Model.h"



/// <summary>
/// 初期化処理
/// </summary>
void Model::Initialize(IModelState* state) {

	// ワールドトランスフォームの設定
	worldTansform_.scale_ = { 1.0f, 1.0f, 1.0f };
	worldTansform_.rotate_ = { 0.0f, 0.0f, 0.0f };
	worldTansform_.translation_ = { 0.0f, 0.0f, 0.0f };

	// テクスチャの設定
	// デフォルトではuvCheckerを使う
	useTexture_ = 1;

	// 色の設定
	color_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// ステートパターンの初期化処理
	state_ = state;
	state_->Initialize(this);
}


/// <summary>
/// 描画処理
/// </summary>
void Model::Draw(WorldTransform worldTransform, Matrix4x4& viewMatrix) {

	state_->Draw(this, worldTransform, viewMatrix);
}

