#include "Pastorale.h"


const wchar_t* kWindowTitle = L"LE2B_20_ツミタ_ヒナタ_CG2";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Pastorale* pastorale_ = new Pastorale();

	// クライアント領域を設定
	const int32_t ClientWidth = 800;
	const int32_t ClientHeight = 700;
	pastorale_->Initialize(kWindowTitle, ClientWidth, ClientHeight);



	// 三角形描画の各要素
	struct TriangleElement {
		Vector4 bottomLeft;  // 左下座標
		Vector4 top;		 // 上座標
		Vector4 bottomRight; // 右下座標
		unsigned int color;	 // 色
	};

	// 三角形を複数用意
	// 各要素を決めていく
	TriangleElement triangle = {
		{ -0.5f, -0.5f, 0.0f, 1.0f },
		{ 0.0f, 0.5f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, 0.0f, 1.0f },
		{0x00ff00ff}
	};


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

		// 三角形複数描画
		pastorale_->DrawTriangle(triangle.bottomLeft, triangle.top, triangle.bottomRight, triangle.color);
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		pastorale_->EndFrame();
	}

	// 解放処理
	delete pastorale_;
}
