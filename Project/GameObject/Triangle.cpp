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
void Triangle::Initialize(Pastorale* pastorale) {

	pastorale_ = pastorale;

	texhandle1_ = TextureManager::LoadTexture("Resources/uvChecker.png");
	texhandle2_ = TextureManager::LoadTexture("Resources/monsterBall.png");
	texhandle3_ = TextureManager::LoadTexture("Resources/asanoha.png");
	texhandle4_ = TextureManager::LoadTexture("Resources/sky.png");


	// モデル
	modelTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 0.0f},
	};
	triElement_ = {
		{ -0.5f, -0.5f, 0.0f, 1.0f},
		{0.0f, 0.5f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 1.0f},
	};
	model_->Initialize();
	model_->SetTextureHandle(texhandle1_);

	// スプライト
	spriteTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 0.0f},
	};
	sprite_->Initialize({ 0.0f, 0.0f }, { 100.0f, 100.0f });
	sprite_->SetTextureHandle(texhandle3_);

	// スフィア
	sphereTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 10.0f},
	};
	sphere_->Initialize();
	sphere_->SetIsLighting(1);
	sphere_->SetTextureHandle(texhandle2_);
	light_.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	light_.direction = { 0.0f, -1.0f, 0.0f };
	light_.intensity = 1.0f;
}



/// <summary>
/// 更新処理
/// </summary>
void Triangle::Update() {

	modelTransform_.rotate_.y += 0.02f;

	sphereTransform_.rotate_.x -= 0.02f;
	sphereTransform_.rotate_.y += 0.02f;
	sphereTransform_.rotate_.z += 0.02f;
	sphere_->SetDirectionalLight(light_);

	ImGui::Begin("DrawObject");
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
	//model_->Draw(triElement_, modelTransform_, ViewMatrix);
}


void Triangle::Draw2D() {
	//sprite_->Draw(spriteTransform_);
}


