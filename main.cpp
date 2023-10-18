#include "GameScene.h"


const wchar_t* kWindowTitle = L"LE2B_20_ツミタ_ヒナタ_CG2";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);

	GameScene* gameScene = new GameScene();

	// クライアント領域を設定
	gameScene->Initialize(kWindowTitle);


	while (gameScene->ProcessMessage() == 0) {
		// フレームの開始
		gameScene->BeginFrame();

		///
		/// ↓更新処理ここから
		///

		gameScene->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		gameScene->Draw3D();
		gameScene->Draw2D();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		gameScene->EndFrame();
	}


	// 解放処理
	delete gameScene;

	// COMの終了処理
	CoUninitialize();
}
