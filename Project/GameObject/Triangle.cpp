#include "Triangle.h"


Triangle::Triangle() {

	modelPlane_ = new Model();
	sprite_ = new Sprite();
	modelSphere_ = new Model();
	demoObj_ = new Model();
}



Triangle::~Triangle() {

	delete modelPlane_;
	delete sprite_;
	delete modelSphere_;
	delete demoObj_;
}


/// <summary>
/// 初期化処理
/// </summary>
void Triangle::Initialize() {

	texhandle1_ = TextureManager::LoadTexture("Resources/Texture/uvChecker.png");
	texhandle2_ = TextureManager::LoadTexture("Resources/Texture/monsterBall.png");
	texhandle3_ = TextureManager::LoadTexture("Resources/Texture/asanoha.png");
	texhandle4_ = TextureManager::LoadTexture("Resources/Texture/sky.png");


	// 平面モデル
	/*modelPlane_->Initialize(new ModelPlaneState);
	modelPlaneTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},
	};*/

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
	modelSphereTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 10.0f},
	};
	// 光の設定
	light_.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	light_.direction = { 0.0f, -1.0f, 0.0f };
	light_.intensity = 1.0f;
	modelSphere_->Initialize(new ModelSphereState);
	modelSphere_->SetTexHandle(texhandle3_);
	modelSphere_->SetIsLighting(1); // ライティングするかしないか


	// デモObj
	demoObjTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, -2.0f, 10.0f},
	};
	demoObj_->CreateFromObj("axis");
	modelSphere_->SetIsLighting(1);
}



/// <summary>
/// 更新処理
/// </summary>
void Triangle::Update() {

	modelSphereTransform_.rotate_.x -= 0.02f;
	modelSphereTransform_.rotate_.y += 0.02f;
	modelSphereTransform_.rotate_.z += 0.02f;
	modelSphere_->SetDirectionalLight(light_);
	demoObj_->SetDirectionalLight(light_);
	sprite_->SetUVTransform(uvTransform_);

	ImGui::Begin("DrawObject");
	//ImGui::Text("Plane");
	//ImGui::DragFloat3("planeScale", &modelPlaneTransform_.scale_.x, 0.01f);
	//ImGui::DragFloat3("planeRotate", &modelPlaneTransform_.rotate_.x, 0.01f);
	//ImGui::DragFloat3("planeTranslate", &modelPlaneTransform_.translation_.x, 0.01f);
	//ImGui::Text("Sprite");
	//ImGui::DragFloat3("spriteScale", &spriteTransform_.scale_.x, 0.1f);
	//ImGui::DragFloat3("spriteRotate", &spriteTransform_.rotate_.x, 0.1f);
	//ImGui::DragFloat3("spriteTranslate", &spriteTransform_.translation_.x, 0.1f);
	//ImGui::DragFloat2("uvScale", &uvTransform_.scale.x, 0.01f);
	//ImGui::DragFloat("uvRotate", &uvTransform_.rotate.z, 0.01f);
	//ImGui::DragFloat2("uvTranslate", &uvTransform_.translate.x, 0.01f);
	//ImGui::Text("Sphere");
	//ImGui::DragFloat3("sphereScale", &modelSphereTransform_.scale_.x, 0.1f);
	//ImGui::DragFloat3("sphereRotate", &modelSphereTransform_.rotate_.x, 0.1f);
	//ImGui::DragFloat3("sphereTranslate", &modelSphereTransform_.translation_.x, 0.1f);
	//ImGui::DragFloat4("LightColor", &light_.color.x, 0.01f);
	//ImGui::DragFloat3("LightDirection", &light_.direction.x, 0.01f);
	ImGui::Text("DemoObj");
	ImGui::DragFloat3("DemoObjScele", &demoObjTransform_.scale_.x, 0.01f);
	ImGui::DragFloat3("DemoObjRotate", &demoObjTransform_.rotate_.x, 0.01f);
	ImGui::DragFloat3("DemoObjTranslate", &demoObjTransform_.translation_.x, 0.01f);

	ImGui::End();
}



/// <summary>
/// 描画処理
/// </summary>
void Triangle::Draw3D(Matrix4x4& ViewMatrix) {

	//modelSphere_->Draw(modelSphereTransform_, ViewMatrix);
	//modelPlane_->Draw(modelPlaneTransform_, ViewMatrix);
	demoObj_->Draw(demoObjTransform_, ViewMatrix);
}


void Triangle::Draw2D() {
	//sprite_->Draw(spriteTransform_);
}


