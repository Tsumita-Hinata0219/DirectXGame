#include "Model.h"



/// <summary>
/// 初期化処理
/// </summary>
void Model::Initialize(IModelState* state) {

	// ワールドトランスフォームの設定
	worldTansform_.scale = { 1.0f, 1.0f, 1.0f };
	worldTansform_.rotate = { 0.0f, 0.0f, 0.0f };
	worldTansform_.translate = { 0.0f, 0.0f, 0.0f };

	// テクスチャの設定
	// デフォルトではuvCheckerを使う
	useTexture_ = 1;

	// 色の設定
	color_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 色の設定
	material_.color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// Lightingを有効にする
	material_.enableLightting = false;

	// 光の設定
	light_.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	light_.direction = { 0.0f, -1.0f, 0.0f };
	light_.intensity = 1.0f;

	// ステートパターンの初期化処理
	state_ = state;
	state_->Initialize(this);
}


/// <summary>
/// Objファイルの読み込み & 初期化処理
/// </summary>
void Model::CreateFromObj(const std::string& directoryPath) {

	// ワールドトランスフォームの設定
	worldTansform_.scale = { 1.0f, 1.0f, 1.0f };
	worldTansform_.rotate = { 0.0f, 0.0f, 0.0f };
	worldTansform_.translate = { 0.0f, 0.0f, 0.0f };

	// テクスチャの設定
	// デフォルトではuvCheckerを使う
	useTexture_ = 1;

	// 色の設定
	color_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 色の設定
	material_.color = { 1.0f, 1.0f, 1.0f, 1.0f };

	state_ = new ModelObjState();
	directoryPath_ = directoryPath;
	state_->Initialize(this);
}


/// <summary>
/// 描画処理
/// </summary>
void Model::Draw(WorldTransform worldTransform, Matrix4x4& viewMatrix) {

	state_->Draw(this, worldTransform, viewMatrix);
}

