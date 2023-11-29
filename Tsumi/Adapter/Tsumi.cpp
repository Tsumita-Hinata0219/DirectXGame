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
	WinApp::Initialize(L"LE2B_20_ツミタ_ヒナタ_CG2");

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

	// Inputの初期化処理
	Input::Initialize();
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
	Input::BeginFrame();
}


/// <summary>
/// フレームの終了
/// </summary>
void Tsumi::EndFlame() {

	ImGuiManager::EndFrame();
	DirectXCommon::PostDraw();
}