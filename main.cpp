#include "WinApp.h"
#include "DirectXCommon.h"


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// 出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX\n");


	// WindowsClassを用意
	WinApp* windows_ = new WinApp();
	// DirectXClassを用意
	DirectXCommon* dXCommon_ = new DirectXCommon();


	// クライアント領域を設定
	const int32_t ClientWidth = 500;
	const int32_t ClientHeight = 500;



	// WinAppの初期化処理
	windows_->Initialize(L"CG2", ClientWidth, ClientHeight);

	// DirectXClassの初期化処理
	dXCommon_->Initialize(ClientWidth, ClientHeight, windows_->GetHwnd());



	MSG msg{};

	
	/* ----- メインループ ----- */

	// ウィンドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		
		// Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else {
			// ゲームの処理
			dXCommon_->PreDraw();





			dXCommon_->PostDraw();
		}

	}


	// 解放処理
	delete windows_;
	delete dXCommon_;


	return 0;
}
