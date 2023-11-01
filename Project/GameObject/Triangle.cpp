#include "Triangle.h"


Triangle::Triangle() {

	sprite_ = new Sprite();
	sphere_ = new Sphere();
}



Triangle::~Triangle() {

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


	// 三角形の各要素を決める
	// Left Top Right Color
	modelElement_ = {
		{ -0.5f, -0.5f, 0.0f, 1.0f},
		{0.0f, 0.5f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
	};
	// SRT
	modelTransform_ = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};


	// スプライト
	spriteTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 0.0f},
	};
	vertex_ = {
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 360.0f, 0.0f, 1.0f },
		{ 640.0f, 0.0f, 0.0f, 1.0f },
		{ 640.0f, 360.0f, 0.0f, 1.0f }
	};


	// スフィア
	sphereTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 150.0f},
	};
	sphere_->Initialize();


}



/// <summary>
/// 更新処理
/// </summary>
void Triangle::Update() {

	modelTransform_.rotate_.y += 0.03f;

	sphereTransform_.rotate_.x -= 0.02f;
	sphereTransform_.rotate_.y += 0.02f;
	sphereTransform_.rotate_.z += 0.02f;

	sphere_->Update();



	ImGui::Begin("DrawObject");
	ImGui::Text("Sphere");
	ImGui::DragFloat3("sphereScale", &sphereTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("sphereRotate", &sphereTransform_.rotate_.x, 0.1f);
	ImGui::DragFloat3("sphereTranslate", &sphereTransform_.translation_.x, 0.1f);
	ImGui::End();
}



/// <summary>
/// 描画処理
/// </summary>
void Triangle::Draw3D(Matrix4x4& ViewMatrix) {

	//pastorale_->GetModel()->Draw(texhandle1_);

	sphere_->Draw(sphereTransform_, ViewMatrix);
}


void Triangle::Draw2D() {

	//sprite_->DrawSpriteuseTex_ ? texhandle4_ : texhandle1_);
}


