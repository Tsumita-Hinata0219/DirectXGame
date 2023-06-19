#include "WinApp.h"
#include "DirectXCommon.h"
#include "Triangle.h"


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// 出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX\n");


	// クライアント領域を設定
	const int32_t ClientWidth = 500;
	const int32_t ClientHeight = 500;


	// WinAppを用意
	WinApp* windows_ = new WinApp();
	// WinAppの初期化処理
	windows_->Initialize(L"CG2", ClientWidth, ClientHeight);


	// DirectXCommonを用意
	DirectXCommon* dXCommon_ = new DirectXCommon();
	// DirectXCommonの初期化処理
	dXCommon_->Initialize(ClientWidth, ClientHeight, windows_->GetHwnd());


	// Triangleを用意
	const int maxTriangle = 10;
	Triangle* triangle_[maxTriangle]{};
	// Triangleの初期化処理
	for (int i = 0; i < maxTriangle; i++) {
		triangle_[i] = new Triangle();
		triangle_[i]->Initialize(dXCommon_->GetDevice(), dXCommon_->GetCommandList());
	}


	// 三角形の各要素を用意(左下、上、右下)
	Vector4 bottomLeft[maxTriangle] = {
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
	Vector4 top[maxTriangle] = {
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
	Vector4 bottomRight[maxTriangle] = {
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


	MSG msg{};


	/* ----- メインループ ----- */

	// ウィンドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		
		// Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else { // ゲームの処理

			// 描画前処理
			dXCommon_->PreDraw();


			// 三角形描画
			for (int i = 0; i < maxTriangle; i++) {
				triangle_[i]->Draw(bottomLeft[i], top[i], bottomRight[i]);
			}


			// 描画後処理
			dXCommon_->PostDraw();
		}
	}


	// 解放処理
	delete windows_;
	for (int i = 0; i < maxTriangle; i++) {
		delete triangle_[i];
	}
	delete dXCommon_;


	return 0;
}

