#include "GameScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() {

	// 生成
	winApp_ = new WinApp();
	dXCommon_ = new DirectXCommon();
	model_ = new Model();
	camera_ = new Camera();
	imguiManager_ = new ImGuiManager();
	textureManager_ = new TextureManager();
}



/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {

	// 解放処理
	delete winApp_;
	delete dXCommon_;
	delete model_;
	delete camera_;
	delete imguiManager_;
	delete textureManager_;
}



/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize(const wchar_t* title, const int32_t Width, const int32_t Height) {

	// WinAppの初期化処理
	winApp_->Initialize(title, Width, Height);

	// DirectXCommonの初期化処理
	dXCommon_->Initialize(Width, Height, winApp_->GetHwnd());

	// TextureManagerの初期化処理
	textureManager_->Initialize(dXCommon_);

	// Modelの初期化処理
	model_->Initialize(dXCommon_, textureManager_);

	// Cameraの初期化処理
	camera_->Initialize(Width, Height);

	// ImGuiの初期化処理
	imguiManager_->Initialize(winApp_, dXCommon_);

	


	// 三角形の各要素を決める
	// Left Top Right Color
	element_ = {
		-0.5f, -0.5f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
	// SRT
	triangleTransform_ = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
}



/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update() {

	// Triangleの更新処理
	model_->Update(
		element_, triangleTransform_, camera_->transformationMatrixData_);



	// Cameraの更新処理
	camera_->Update();



	/* ---------- ImGui ---------- */

	// Triangle
	ImGui::Begin("Triangle");

	ImGui::SliderFloat4("scale", &triangleTransform_.scale.x, -1.0f, 1.0f);
	ImGui::SliderFloat4("rotate", &triangleTransform_.rotate.x, -1.0f, 1.0f);
	ImGui::SliderFloat4("translation", &triangleTransform_.translate.x, -1.0f, 1.0f);
	ImGui::ColorEdit4("color", &element_.color.x);

	ImGui::End();


	// Camera
	ImGui::Begin("Camera");

	ImGui::SliderFloat4("translation", &camera_->cameraTransform.translate.x, -30.0f, 10.0f);

	ImGui::End();
}



/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw() {

	// Triangleの描画
	model_->Draw();
}



/// <summary>
/// フレームの開始
/// </summary>
void GameScene::BeginFrame() {

	dXCommon_->PreDraw();
	imguiManager_->BeginFrame(dXCommon_);
}



/// <summary>
/// フレームの終了
/// </summary>
void GameScene::EndFrame() {

	imguiManager_->EndFrame(dXCommon_);
	dXCommon_->PostDraw();
}



/// <summary>
/// メッセージの処理
/// </summary>
bool GameScene::ProcessMessage() {

	if (winApp_->ProcessMessage()) {
		return true;
	}
	else {
		return false;
	}
}