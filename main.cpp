#include "WindowsClass.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// 出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX\n");


	// ウィンドウクラスのインストラクタ
	// クライアント領域を設定
	WindowsClass* windows_ = new WindowsClass(L"CG2", 500, 500);

	// ウィンドウクラスの更新処理
	windows_->Initialize();

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


	return 0;
}