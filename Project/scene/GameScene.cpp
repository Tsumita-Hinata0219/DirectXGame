#include "GameScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() {

	// 生成
	camera_ = new Camera();
	pastorale_ = new Pastorale();
	triangle_ = new Triangle();
	sprite_ = new Sprite();
}



/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {

	// 解放処理
	delete camera_;
	delete pastorale_;
	delete triangle_;
	delete sprite_;
}



/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize(const wchar_t* title) {

	// WinAppの初期化処理
	WinApp::Initialize(title);

	// DirectXCommonの初期化処理
	DirectXCommon::Initialize();

	// ShaderManagerの初期化処理
	ShaderManager::Initialize();

	// GraphicPiplelineManagerの初期化処理
	GraphicPipelineManager::Initialize();

	// Pastoraleの初期化処理
	pastorale_->Initialize();

	// Triangleの初期化処理
	triangle_->Initialize(pastorale_);

	// Cameraの初期化処理
	camera_->Initialize();

	// ImGuiの初期化処理
	ImGuiManager::Initialize();

	// Spriteの初期化処理
	WorldTransform transformSprite{ {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} };
	
}



/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update() {

	// Triangleの更新処理
	triangle_->Update();

	// Cameraの更新処理
	camera_->Update();


	/* ---------- ImGui ---------- */

	// Camera
	ImGui::Begin("Camera");

	ImGui::SliderFloat4("translation", &camera_->cameraTransform.translation_.x, -1000.0f, 10.0f);

	ImGui::End();
}



/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw3D() {

	// Triangleの描画処理
	triangle_->Draw3D(camera_->transformationMatrixData_);
}

void GameScene::Draw2D() {

	// Spriteの描画処理
	triangle_->Draw2D();
}



/// <summary>
/// フレームの開始
/// </summary>
void GameScene::BeginFrame() {

	DirectXCommon::PreDraw();
	ImGuiManager::BeginFrame();
}



/// <summary>
/// フレームの終了
/// </summary>
void GameScene::EndFrame() {

	ImGuiManager::EndFrame();
	DirectXCommon::PostDraw();
}



/// <summary>
/// メッセージの処理
/// </summary>
bool GameScene::ProcessMessage() {

	if (WinApp::ProcessMessage()) {
		return true;
	}
	else {
		return false;
	}
}