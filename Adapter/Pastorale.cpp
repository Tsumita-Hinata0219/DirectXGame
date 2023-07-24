#include "Pastorale.h"



/// <summary>
/// コンストラクタ
/// </summary>
Pastorale::Pastorale() {

	winApp_ = new WinApp();
	dXCommon_ = new DirectXCommon();
}



/// <summary>
/// デストラクタ
/// </summary>
Pastorale::~Pastorale() {

	// 解放処理
	delete winApp_;
	delete dXCommon_;
}



/// <summary>
/// 初期化処理
/// </summary>
void Pastorale::Initialize(const wchar_t* title, const int32_t Width, const int32_t Height) {

	// WinAppの初期化処理
	winApp_->Initialize(title, Width, Height);

	// DirectXCommonの初期化処理
	dXCommon_->Initialize(Width, Height, winApp_->GetHwnd());

}



/// <summary>
/// フレームの開始
/// </summary>
void Pastorale::BeginFrame() {

	dXCommon_->PreDraw();
}



/// <summary>
/// フレームの終了
/// </summary>
void Pastorale::EndFrame() {

	dXCommon_->PostDraw();
}



/// <summary>
/// メッセージの処理
/// </summary>
bool Pastorale::ProcessMessage() {

	if (winApp_->ProcessMessage()) {
		return true;
	}
	else {
		return false;
	}
}

