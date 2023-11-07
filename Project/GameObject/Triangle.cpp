#include "Triangle.h"


Triangle::Triangle() {

	model_ = new Model();
	sprite_ = new Sprite();
	sphere_ = new Sphere();
}



Triangle::~Triangle() {

	delete model_;
	delete sprite_;
	delete sphere_;
}


/// <summary>
/// 初期化処理
/// </summary>
void Triangle::Initialize() {

	texhandle1_ = TextureManager::LoadTexture("Resources/uvChecker.png");
	texhandle2_ = TextureManager::LoadTexture("Resources/monsterBall.png");
	texhandle3_ = TextureManager::LoadTexture("Resources/asanoha.png");
	texhandle4_ = TextureManager::LoadTexture("Resources/sky.png");


	// モデル
	modelTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 20.0f},
	};
	model_->Initialize();

	// スプライト
	spriteTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 0.0f},
	};
	sprite_->Initialize({ 0.0f, 0.0f }, { 640.0f, 360.0f });
	sprite_->SetTextureHandle(texhandle1_);
	uvTransform_ = {
		{ 1.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	};

	// スフィア
	sphereTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 10.0f},
	};
	sphere_->Initialize();
	sphere_->SetTextureHandle(texhandle3_);
}



/// <summary>
/// 更新処理
/// </summary>
void Triangle::Update() {

	sphereTransform_.rotate_.x -= 0.02f;
	sphereTransform_.rotate_.y += 0.02f;
	sphereTransform_.rotate_.z += 0.02f;
	sphere_->SetDirectionalLight(light_);
	sprite_->SetUVTransform(uvTransform_);

	ImGui::Begin("DrawObject");
	ImGui::Text("Model");
	ImGui::DragFloat3("modelScale", &modelTransform_.scale_.x, 0.01f);
	ImGui::DragFloat3("modelRotate", &modelTransform_.rotate_.x, 0.01f);
	ImGui::DragFloat3("modelTranslate", &modelTransform_.translation_.x, 0.01f);
	ImGui::Text("Sprite");
	ImGui::DragFloat3("spriteScale", &spriteTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("spriteRotate", &spriteTransform_.rotate_.x, 0.1f);
	ImGui::DragFloat3("spriteTranslate", &spriteTransform_.translation_.x, 0.1f);
	ImGui::DragFloat2("uvScale", &uvTransform_.scale.x, 0.01f);
	ImGui::DragFloat("uvRotate", &uvTransform_.rotate.z, 0.01f);
	ImGui::DragFloat2("uvTranslate", &uvTransform_.translate.x, 0.01f);
	ImGui::Text("Sphere");
	ImGui::DragFloat3("sphereScale", &sphereTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("sphereRotate", &sphereTransform_.rotate_.x, 0.1f);
	ImGui::DragFloat3("sphereTranslate", &sphereTransform_.translation_.x, 0.1f);
	ImGui::DragFloat4("LightColor", &light_.color.x, 0.01f);
	ImGui::DragFloat3("LightDirection", &light_.direction.x, 0.01f);
	ImGui::End();
}



/// <summary>
/// 描画処理
/// </summary>
void Triangle::Draw3D(Matrix4x4& ViewMatrix) {

	sphere_->Draw(sphereTransform_, ViewMatrix);
	model_->Draw(modelTransform_, ViewMatrix);
}


void Triangle::Draw2D() {
	sprite_->Draw(spriteTransform_);
}


