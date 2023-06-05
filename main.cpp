#include "WindowsClass.h"
#include "DirectXClass.h"


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// 出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX\n");


	// WindowsClassを用意
	// クライアント領域を設定
	const int32_t kClientWidth = 500;
	const int32_t kClientHeight = 500;
	WindowsClass* windows_ = new WindowsClass(L"CG2", kClientWidth, kClientHeight);

	// DirectXClassを用意
	DirectXClass* directX_ = nullptr;


	// WindowsClassの初期化処理
	windows_->Initialize();

	// DirectXClassの初期化処理
	directX_->Initialize(kClientWidth, kClientHeight);



	/* ----- メインループ ----- */
	
	MSG msg{};

	// ウィンドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		
		// Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ゲームの処理


		}
	}


	// 解放処理
	directX_->~DirectXClass();


	delete windows_;
	delete directX_;

	return 0;
}