#include "EngineManual.h"



/// <summary>
/// 初期化処理
/// </summary>
void EngineManual::Initialize() {

	// テクスチャの読み込み
	texHD1_ = TextureManager::LoadTexture("Resources/Texture/uvChecker.png");
	texHD2_ = TextureManager::LoadTexture("Resources/Texture/monsterBall.png");
	texHD3_ = TextureManager::LoadTexture("Resources/Texture/asanoha.png");
	texHD4_ = TextureManager::LoadTexture("Resources/Texture/sky.png");


	// 平面モデル
	planeModel_ = std::make_unique<Model>();
	planeModel_->Initialize(new ModelPlaneState());
	planeModelTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},
	};


	// スプライト
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize({ 0.0f, 0.0f }, { 640.0f, 360.0f });
	sprite_->SetTextureHandle(texHD1_);


	// Objモデル
	objModel_->CreateFromObj("axis");
	objModelTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, -2.0f, 10.0f},
	};
}


/// <summary>
/// 更新処理
/// </summary>
void EngineManual::Update() {

	planeModelTransform_.UpdateMatrix();
	objModelTransform_.UpdateMatrix();
	spriteTransform_.UpdateMatrix();
}


/// <summary>
/// 描画処理3D
/// </summary>
void EngineManual::Draw3D(ViewProjection view) {

	planeModel_->Draw(planeModelTransform_, view);
	objModel_->Draw(objModelTransform_, view);
}


/// <summary>
/// 描画処理2D
/// </summary>
void EngineManual::Draw2D() {

	sprite_->Draw(spriteTransform_);
}