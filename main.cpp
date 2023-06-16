#include "WinApp.h"
#include "DirectXCommon.h"
#include "Triangle.h"


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// 出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX\n");


	// WindowsClassを用意
	WinApp* windows_ = new WinApp();
	// DirectXClassを用意
	DirectXCommon* dXCommon_ = new DirectXCommon();
	//// TriangleClassを用意
	//Triangle* triangle_ = new Triangle();


	// クライアント領域を設定
	const int32_t ClientWidth = 500;
	const int32_t ClientHeight = 500;



	// WinAppの初期化処理
	windows_->Initialize(L"CG2", ClientWidth, ClientHeight);

	// DirectXCommonの初期化処理
	dXCommon_->Initialize(ClientWidth, ClientHeight, windows_->GetHwnd());

	//// Triangleの初期化処理
	//triangle_->Initialize(dXCommon_->GetDevice(), dXCommon_->GetCommandList());

	//Vector4 bottomLeft = { -0.1f,0.9f,0.0f,1.0f };
	//Vector4 top = { 0.0f,1.0f,0.0f,1.0f };
	//Vector4 bottomRight = { 0.1f,0.9f,0.0f,1.0f };


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

			//// 描画前処理
			//dXCommon_->PreDraw();


			//// 三角形描画
			//triangle_->Draw(bottomLeft, top, bottomRight);
			//

			//// 描画後処理
			//dXCommon_->PostDraw();
		}


	}


	// 解放処理
	delete windows_;
	/*delete triangle_;*/
	delete dXCommon_;


	return 0;
}
