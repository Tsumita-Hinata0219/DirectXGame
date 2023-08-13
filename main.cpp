#include "GameScene.h"


const wchar_t* kWindowTitle = L"LE2B_20_ツミタ_ヒナタ_CG2";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//Pastorale* pastorale_ = new Pastorale();
	GameScene* gameScene = new GameScene();

	// クライアント領域を設定
	const int32_t ClientWidth = 1280;
	const int32_t ClientHeight = 720;
	gameScene->Initialize(kWindowTitle, ClientWidth, ClientHeight);


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

		gameScene->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		gameScene->EndFrame();
	}


	// 解放処理
	delete gameScene;
}
