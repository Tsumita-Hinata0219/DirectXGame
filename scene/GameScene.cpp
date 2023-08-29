#include "GameScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() {

	// 生成
	winApp_ = new WinApp();
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
	delete winApp_;
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
void GameScene::Initialize(const wchar_t* title, const int32_t Width, const int32_t Height) {

	// WinAppの初期化処理
	winApp_->Initialize(title, Width, Height);

	// DirectXCommonの初期化処理
	dXCommon_->Initialize(Width, Height, winApp_->GetHwnd());

	// Pastoraleの初期化書影
	pastorale_->Initialize(dXCommon_);

	// Triangleの初期化処理
	triangle_->Initialize(pastorale_, dXCommon_);

	// Cameraの初期化処理
	camera_->Initialize(Width, Height);

	// ImGuiの初期化処理
	imguiManager_->Initialize(winApp_, dXCommon_);

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

	ImGui::SliderFloat4("translation", &camera_->cameraTransform.translate.x, -30.0f, 10.0f);

	ImGui::End();
}



/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw() {

	// Triangleの描画処理
	triangle_->Draw();

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