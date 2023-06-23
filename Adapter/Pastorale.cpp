#include "Pastorale.h"



/// <summary>
/// コンストラクタ
/// </summary>
Pastorale::Pastorale() {

	winApp_ = new WinApp();
	dXCommon_ = new DirectXCommon();
	model_ = new Model();
}



/// <summary>
/// デストラクタ
/// </summary>
Pastorale::~Pastorale() {

	// 解放処理
	delete winApp_;
	delete dXCommon_;
	delete model_;
}



/// <summary>
/// 初期化処理
/// </summary>
void Pastorale::Initialize(const wchar_t* title, const int32_t Width, const int32_t Height) {

	// WinAppの初期化処理
	winApp_->Initialize(title, Width, Height);

	// DirectXCommonの初期化処理
	dXCommon_->Initialize(Width, Height, winApp_->GetHwnd());

	// Modelの初期化処理
	model_->Initialize(dXCommon_->GetDevice(), dXCommon_->GetCommandList());

}



/// <summary>
/// フレームの開始
/// </summary>
void Pastorale::BeginFrame() {

	dXCommon_->PreDraw();;
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



/// <summary>
/// 三角形の描画
/// </summary>
void Pastorale::DrawTriangle(Vector4 bottomLeft, Vector4 top, Vector4 bottoomRight) {

	model_->DrawTriangle(bottomLeft, top, bottoomRight);

//	// 左下
//	vertexData_[0] = bottomLeft;
//
//	// 上
//	vertexData_[1] = top;
//
//	// 右下
//	vertexData_[2] = bottoomRight;
//
//
//	// いざ描画！！！！！
//	// VBVを設定
//	dXCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);
//
//	// 形状を設定
//	dXCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//	// 描画！(DrawCall / ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
//	dXCommon_->GetCommandList()->DrawInstanced(3, 1, 0, 0);
}

