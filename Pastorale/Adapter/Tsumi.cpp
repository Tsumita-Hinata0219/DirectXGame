#include "Tsumi.h"



/// <summary>
/// インスタンスの取得
/// </summary>
Tsumi* Tsumi::GetInstance() {
	static Tsumi instance;
	return &instance;
}


/// <summary>
/// 初期化処理
/// </summary>
void Tsumi::Initialize() {

	Tsumi::GetInstance();

	// WinAppの初期化処理
	WinApp::Initialize(kWindowTitle);

	// DirectXCommonの初期化処理
	DirectXCommon::Initialize();

	// ShaderManagerの初期化処理
	ShaderManager::Initialize();

	// GraphicPiplelineManagerの初期化処理
	GraphicPipelineManager::Initialize();

	// TextureManagerの初期化処理
	TextureManager::Initialize();

	// ImGuiの初期化処理
	ImGuiManager::Initialize();
}


/// <summary>
/// 解放処理
/// </summary>
void Tsumi::Finalize() {


}


/// <summary>
/// フレームの開始
/// </summary>
void Tsumi::BeginFlame() {

	DirectXCommon::PreDraw();
	ImGuiManager::BeginFrame();
}


/// <summary>
/// フレームの終了
/// </summary>
void Tsumi::EndFlame() {

	ImGuiManager::EndFrame();
	DirectXCommon::PostDraw();
}