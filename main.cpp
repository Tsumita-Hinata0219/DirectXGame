#include "Pastorale.h"
#include "Model.h"
#include "Transform.h"
#include "GameScene.h"



const wchar_t* kWindowTitle = L"LE2B_20_ツミタ_ヒナタ_CG2";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Pastorale* pastorale_ = new Pastorale();
	GameScene* gameScene = new GameScene();

	// クライアント領域を設定
	const int32_t ClientWidth = 1280;
	const int32_t ClientHeight = 720;
	pastorale_->Initialize(kWindowTitle, ClientWidth, ClientHeight);


	// 三角形を複数用意
	// 各要素を決めていく
	Model* triangle;
	Transform transform{};

	// STR + Color
	Triangle element{
		-0.5f, -0.5f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};


	// 頂点の初期化
	// 生成
	triangle = new Model();

	transform = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};

	triangle->Initialize(
		pastorale_->GetDirectXCommon());



	// ウィンドウの×ボタンが押されるまでループ
	while (pastorale_->ProcessMessage() == 0) {
		// フレームの開始
		pastorale_->BeginFrame();

		///
		/// ↓更新処理ここから
		///

		pastorale_->Update();


		triangle->Update(
			element, transform, pastorale_->GetCamera()->transformationMatrixData_);



		ImGui::Begin("Triangle");

		ImGui::SliderFloat4("scale", &transform.scale.x, -1.0f, 1.0f);
		ImGui::SliderFloat4("rotate", &transform.rotate.x, -1.0f, 1.0f);
		ImGui::SliderFloat4("translation", &transform.translate.x, -1.0f, 1.0f);
		ImGui::ColorEdit4("color", &element.color.x);

		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 三角形複数描画
		triangle->Draw();
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		pastorale_->EndFrame();
	}

	// 解放処理
	delete pastorale_;
	delete gameScene;
}
