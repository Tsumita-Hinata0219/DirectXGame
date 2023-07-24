#include "Pastorale.h"
#include "Model.h"


const wchar_t* kWindowTitle = L"LE2B_20_ツミタ_ヒナタ_CG2";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Pastorale* pastorale_ = new Pastorale();

	// クライアント領域を設定
	const int32_t ClientWidth = 500;
	const int32_t ClientHeight = 500;
	pastorale_->Initialize(kWindowTitle, ClientWidth, ClientHeight);



	// 三角形
	//const int MaxTriangle = 10;
	//Model* triangle[MaxTriangle]{};

	////Model* triangle = new Model();
	////triangle->transform_.left = { 0.0f, 0.0f, 0.0f, 0.0f };
	////triangle->transform_.top = { 0.0f, 0.0f, 0.0f, 0.0f };
	////triangle->transform_.right = { 0.0f, 0.0f, 0.0f, 0.0f };
	////triangle->Initialize(pastorale_->GetDirectXCommon(), triangle->transform_);


	//// 三角形の各要素を用意(左下、上、右下)
	//triangle[MaxTriangle]->vertexData_[0] = {
	//	{-0.4f,0.7f,0.0f,1.0f},
	//	{-0.4f,0.5f,0.0f,1.0f},
	//	{0.2f,0.7f,0.0f,1.0f},
	//	{0.2f,0.5f,0.0f,1.0f},
	//	{-0.1f,0.6f,0.0f,1.0f},
	//	{-0.4f,0.2f,0.0f,1.0f},
	//	{-0.4f,0.0f,0.0f,1.0f},
	//	{0.2f,0.2f,0.0f,1.0f},
	//	{0.2f,0.0f,0.0f,1.0f},
	//	{-0.1f,0.1f,0.0f,1.0f}
	//};
	//Vector4 top[MaxTriangle] = {
	//	{-0.3f,0.8f,0.0f,1.0f},
	//	{-0.3f,0.6f,0.0f,1.0f},
	//	{0.3f,0.8f,0.0f,1.0f},
	//	{0.3f,0.6f,0.0f,1.0f},
	//	{0.0f,0.7f,0.0f,1.0f},
	//	{-0.3f,0.3f,0.0f,1.0f},
	//	{-0.3f,0.1f,0.0f,1.0f},
	//	{0.3f,0.3f,0.0f,1.0f},
	//	{0.3f,0.1f,0.0f,1.0f},
	//	{0.0f,0.2f,0.0f,1.0f}
	//};
	//Vector4 bottomRight[MaxTriangle] = {
	//	{-0.2f,0.7f,0.0f,1.0f},
	//	{-0.2f,0.5f,0.0f,1.0f},
	//	{0.4f,0.7f,0.0f,1.0f},
	//	{0.4f,0.5f,0.0f,1.0f},
	//	{0.1f,0.6f,0.0f,1.0f},
	//	{-0.2f,0.2f,0.0f,1.0f},
	//	{-0.2f,0.0f,0.0f,1.0f},
	//	{0.4f,0.2f,0.0f,1.0f},
	//	{0.4f,0.0f,0.0f,1.0f},
	//	{0.1f,0.1f,0.0f,1.0f},
	//};
	//for (int i = 0; i < MaxTriangle; i++) {
	//
	//}

	Model* triangle = new Model;
	triangle->Initialize(pastorale_->GetDirectXCommon());
	triangle->vertexData_[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	triangle->vertexData_[1] = { 0.0f, 0.5f, 0.0f, 1.0f };
	triangle->vertexData_[2] = { 0.5f, -0.5f, 0.0f, 1.0f };


	// ウィンドウの×ボタンが押されるまでループ
	while (pastorale_->ProcessMessage() == 0) {
		// フレームの開始
		pastorale_->BeginFrame();

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 三角形描画
		triangle->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		pastorale_->EndFrame();
	}

	delete pastorale_;
}

