#include "Pastorale.h"


const wchar_t* kWindowTitle = L"LE2B_20_ツミタ_ヒナタ_CG2";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Pastorale* pastorale_ = new Pastorale();

	// クライアント領域を設定
	const int32_t ClientWidth = 500;
	const int32_t ClientHeight = 500;
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
	const int MaxTriangle = 10;
	TriangleElement triangle[MaxTriangle] = {
		// 1
		{{-0.4f,0.7f,0.0f,1.0f},
		{-0.3f,0.8f,0.0f,1.0f},
		{-0.2f,0.7f,0.0f,1.0f},
		{0xffffffff}},

		// 2
		{{-0.4f,0.5f,0.0f,1.0f},
		{-0.3f,0.6f,0.0f,1.0f},
		{-0.2f,0.5f,0.0f,1.0f},
		{0xff0000ff}},

		// 3
		{{0.2f,0.7f,0.0f,1.0f},
		{0.3f,0.8f,0.0f,1.0f},
		{0.4f,0.7f,0.0f,1.0f},
		{0x0000ffff}},

		// 4
		{{0.2f,0.5f,0.0f,1.0f},
		{0.3f,0.6f,0.0f,1.0f},
		{0.4f,0.5f,0.0f,1.0f},
		{0xffff00ff}},

		// 5
		{{-0.1f,0.6f,0.0f,1.0f},
		{0.0f,0.7f,0.0f,1.0f},
		{0.1f,0.6f,0.0f,1.0f},
		{0xff7f00ff}},

		// 6
		{{-0.4f,0.2f,0.0f,1.0f},
		{-0.3f,0.3f,0.0f,1.0f},
		{-0.2f,0.2f,0.0f,1.0f},
		{0x00ff00ff}},

		// 7
		{{-0.4f,0.0f,0.0f,1.0f},
		{-0.3f,0.1f,0.0f,1.0f},
		{-0.2f,0.0f,0.0f,1.0f},
		{0xff33ccff}},

		// 8
		{{0.2f,0.2f,0.0f,1.0f},
		{0.3f,0.3f,0.0f,1.0f},
		{0.4f,0.2f,0.0f,1.0f},
		{0x7f00ffff}},

		// 9
		{{0.2f,0.0f,0.0f,1.0f},
		{0.3f,0.1f,0.0f,1.0f},
		{0.4f,0.0f,0.0f,1.0f},
		{0x000000ff}},

		// 10
		{{-0.1f,0.1f,0.0f,1.0f},
		{0.0f,0.2f,0.0f,1.0f},
		{0.1f,0.1f,0.0f,1.0f},
		{0x663300ff}},
	};

	// 頂点の初期化
	for (int i = 0; i < MaxTriangle; i++) {
		pastorale_->TriangleVertexIni(triangle[i].bottomLeft, triangle[i].top, triangle[i].bottomRight, triangle[i].color);
	}



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
		for (int i = 0; i < MaxTriangle; i++) {
			pastorale_->DrawTriangle(triangle[i].bottomLeft, triangle[i].top, triangle[i].bottomRight, triangle[i].color);
		}
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		pastorale_->EndFrame();
	}

	// 解放処理
	delete pastorale_;
}
