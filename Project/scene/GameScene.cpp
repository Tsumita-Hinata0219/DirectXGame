#include "GameScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() {

	// 生成
	dXCommon_ = new DirectXCommon();
	camera_ = new Camera();
	imguiManager_ = new ImGuiManager();
	pastorale_ = new Pastorale();
	triangle_ = new Triangle();
	sprite_ = new Sprite();
}



/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {

	// 解放処理
	delete dXCommon_;
	delete camera_;
	delete imguiManager_;
	delete pastorale_;
	delete triangle_;
	delete sprite_;
}



/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize() {

	// DirectXCommonの初期化処理
	dXCommon_->Initialize();

	// Pastoraleの初期化書影
	pastorale_->Initialize(dXCommon_);

	// Triangleの初期化処理
	triangle_->Initialize(pastorale_, dXCommon_);

	// Cameraの初期化処理
	camera_->Initialize();

	// ImGuiの初期化処理
	imguiManager_->Initialize(dXCommon_);

	// Spriteの初期化処理
	WorldTransform transformSprite{ {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} };
	
}



/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update() {

	// Triangleの更新処理
	triangle_->Update(camera_->transformationMatrixData_);

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
	triangle_->Draw3D();
}

void GameScene::Draw2D() {

	// Spriteの描画処理
	triangle_->Draw2D();
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