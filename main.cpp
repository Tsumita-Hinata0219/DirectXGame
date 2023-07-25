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




	// 三角形描画の各要素
	struct TriangleElement {
		Vector4 bottomLeft;  // 左下座標
		Vector4 top;		 // 上座標
		Vector4 bottomRight; // 右下座標
	};

	// 三角形を複数用意
	// 各要素を決めていく
	const int MaxTriangle = 10;
	Model* triangle[MaxTriangle]{};

	TriangleElement triangleEle[MaxTriangle] = {
		// 1
		{{-0.4f,0.7f,0.0f,1.0f},
		{-0.3f,0.8f,0.0f,1.0f},
		{-0.2f,0.7f,0.0f,1.0f}},

		// 2
		{{-0.4f,0.5f,0.0f,1.0f},
		{-0.3f,0.6f,0.0f,1.0f},
		{-0.2f,0.5f,0.0f,1.0f}},

		// 3
		{{0.2f,0.7f,0.0f,1.0f},
		{0.3f,0.8f,0.0f,1.0f},
		{0.4f,0.7f,0.0f,1.0f}},

		// 4
		{{0.2f,0.5f,0.0f,1.0f},
		{0.3f,0.6f,0.0f,1.0f},
		{0.4f,0.5f,0.0f,1.0f}},

		// 5
		{{-0.1f,0.6f,0.0f,1.0f},
		{0.0f,0.7f,0.0f,1.0f},
		{0.1f,0.6f,0.0f,1.0f}},

		// 6
		{{-0.4f,0.2f,0.0f,1.0f},
		{-0.3f,0.3f,0.0f,1.0f},
		{-0.2f,0.2f,0.0f,1.0f}},

		// 7
		{{-0.4f,0.0f,0.0f,1.0f},
		{-0.3f,0.1f,0.0f,1.0f},
		{-0.2f,0.0f,0.0f,1.0f}},

		// 8
		{{0.2f,0.2f,0.0f,1.0f},
		{0.3f,0.3f,0.0f,1.0f},
		{0.4f,0.2f,0.0f,1.0f}},

		// 9
		{{0.2f,0.0f,0.0f,1.0f},
		{0.3f,0.1f,0.0f,1.0f},
		{0.4f,0.0f,0.0f,1.0f}},

		// 10
		{{-0.1f,0.1f,0.0f,1.0f},
		{0.0f,0.2f,0.0f,1.0f},
		{0.1f,0.1f,0.0f,1.0f}},
	};

	// 頂点の初期化
	for (int i = 0; i < MaxTriangle; i++) {

		triangle[i] = new Model();

		// 初期化処理
		triangle[i]->Initialize(
			pastorale_->GetDirectXCommon(),
			triangleEle[i].bottomLeft,
			triangleEle[i].top,
			triangleEle[i].bottomRight);
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

		// 三角形描画
		for (int i = 0; i < MaxTriangle; i++) {
			triangle[i]->Draw();
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		pastorale_->EndFrame();
	}

	delete pastorale_;
}

