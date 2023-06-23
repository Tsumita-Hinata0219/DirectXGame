#include "Pastorale.h"
//#include "Triangle.h"
//#include "DirectXCommon.h"


const wchar_t* kWindowTitle = L"LE2B_20_ツミタ_ヒナタ_CG2";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Pastorale* pastorale_ = new Pastorale();

	// クライアント領域を設定
	const int32_t ClientWidth = 500;
	const int32_t ClientHeight = 500;
	pastorale_->Initialize(kWindowTitle, ClientWidth, ClientHeight);


	//	
	const int MaxTriangle = 10;
	// 三角形の各要素を用意(左下、上、右下)
	Vector4 bottomLeft[MaxTriangle] = {
		{-0.4f,0.7f,0.0f,1.0f},
		{-0.4f,0.5f,0.0f,1.0f},
		{0.2f,0.7f,0.0f,1.0f},
		{0.2f,0.5f,0.0f,1.0f},
		{-0.1f,0.6f,0.0f,1.0f},
		{-0.4f,0.2f,0.0f,1.0f},
		{-0.4f,0.0f,0.0f,1.0f},
		{0.2f,0.2f,0.0f,1.0f},
		{0.2f,0.0f,0.0f,1.0f},
		{-0.1f,0.1f,0.0f,1.0f}
	};
	Vector4 top[MaxTriangle] = {
		{-0.3f,0.8f,0.0f,1.0f},
		{-0.3f,0.6f,0.0f,1.0f},
		{0.3f,0.8f,0.0f,1.0f},
		{0.3f,0.6f,0.0f,1.0f},
		{0.0f,0.7f,0.0f,1.0f},
		{-0.3f,0.3f,0.0f,1.0f},
		{-0.3f,0.1f,0.0f,1.0f},
		{0.3f,0.3f,0.0f,1.0f},
		{0.3f,0.1f,0.0f,1.0f},
		{0.0f,0.2f,0.0f,1.0f}
	};
	Vector4 bottomRight[MaxTriangle] = {
		{-0.2f,0.7f,0.0f,1.0f},
		{-0.2f,0.5f,0.0f,1.0f},
		{0.4f,0.7f,0.0f,1.0f},
		{0.4f,0.5f,0.0f,1.0f},
		{0.1f,0.6f,0.0f,1.0f},
		{-0.2f,0.2f,0.0f,1.0f},
		{-0.2f,0.0f,0.0f,1.0f},
		{0.4f,0.2f,0.0f,1.0f},
		{0.4f,0.0f,0.0f,1.0f},
		{0.1f,0.1f,0.0f,1.0f},
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

		// 三角形描画
		for (int i = 0; i < MaxTriangle; i++) {
			pastorale_->DrawTriangle(bottomLeft[i], top[i], bottomRight[i]);
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

//	MSG msg{};
//
//
//	/* ----- メインループ ----- */
//
//	// ウィンドウの×ボタンが押されるまでループ
//	while (msg.message != WM_QUIT) {
//		
//		// Windowにメッセージが来てたら最優先で処理させる
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//
//		}
//		else { // ゲームの処理
//
//			// 描画前処理
//			dXCommon_->PreDraw();
//
//
//			// 三角形描画
//			for (int i = 0; i < maxTriangle; i++) {
//				triangle_[i]->Draw(bottomLeft[i], top[i], bottomRight[i]);
//			}
//
//
//			// 描画後処理
//			dXCommon_->PostDraw();
//		}
//	}
//
//
//	// 解放処理
//	delete windows_;
//	for (int i = 0; i < maxTriangle; i++) {
//		delete triangle_[i];
//	}
//	delete dXCommon_;
//
//
//	return 0;
//}

