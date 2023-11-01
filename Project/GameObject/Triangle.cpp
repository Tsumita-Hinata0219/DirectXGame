#include "Triangle.h"


Triangle::Triangle() {

	sphere_ = new Sphere();
}



Triangle::~Triangle() {

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


	// スフィア
	sphereTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 10.0f},
	};
	sphere_->Initialize();
}



/// <summary>
/// 更新処理
/// </summary>
void Triangle::Update() {

	sphereTransform_.rotate_.x -= 0.02f;
	sphereTransform_.rotate_.y += 0.02f;
	sphereTransform_.rotate_.z += 0.02f;


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

	sphere_->Draw(sphereTransform_, ViewMatrix);
}


void Triangle::Draw2D() {

}


