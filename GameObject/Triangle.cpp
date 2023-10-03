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
void Triangle::Initialize(Pastorale* pastorale, DirectXCommon* dXCommon){

  	pastorale_ = pastorale;

	pastorale_->GetATextureManager()->LoadTexture("Resources/uvChecker.png", "Resources/monsterBall.png");


	// 三角形の各要素を決める
	// Left Top Right Color
	element_ = {
		{ -0.5f, -0.5f, 0.0f, 1.0f},
		{0.0f, 0.5f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
	};
	// SRT
	transform_ = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};


	// スプライト
	sprite_->Initialize(1280, 720, dXCommon);
	spriteTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1000.0f},
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
	sphereElemnt_ = {
		{0.0f, 0.0f, 20.0f},
		{20.0f},
	};
	sphere_->Initialize(1280, 720, dXCommon, sphereTransform_);
}



/// <summary>
/// 更新処理
/// </summary>
void Triangle::Update(Matrix4x4& ViewMatrix){

	transform_.rotate.y += 0.03f;

	sphereTransform_.rotate.y += 0.02f;

	pastorale_->GetModel()->Update(element_, transform_, ViewMatrix);

	sprite_->Update(spriteTransform_, vertex_);

	sphere_->Update(sphereElemnt_, sphereTransform_, ViewMatrix);



	ImGui::Begin("Sprite");

	ImGui::SliderFloat3("Scale", &spriteTransform_.scale.x, -2.0f, 2.0f);
	ImGui::SliderFloat3("Rotate", &spriteTransform_.rotate.x, -4.0f, 4.0f);
	ImGui::SliderFloat3("Translate", &spriteTransform_.translate.x, 0.0f, 1000);

	ImGui::End();



	ImGui::Begin("sphere");

	ImGui::SliderFloat3("Scale", &sphereTransform_.scale.x, -2.0f, 2.0f);
	ImGui::SliderFloat3("Rotate", &sphereTransform_.rotate.x, -4.0f, 4.0f);
	ImGui::SliderFloat3("Translate", &sphereTransform_.translate.x, 0.0f, 1000);

	ImGui::End();

}



/// <summary>
/// 描画処理
/// </summary>
void Triangle::Draw3D() {

	//pastorale_->GetModel()->Draw(pastorale_->GetATextureManager());
	sphere_->Draw(pastorale_->GetATextureManager());
}


void Triangle::Draw2D() {

	sprite_->DrawSprite(pastorale_->GetATextureManager());
}

