#include "Pastorale.h"
#include "Model.h"
#include "Transform.h"


const wchar_t* kWindowTitle = L"LE2B_20_ツミタ_ヒナタ_CG2";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Pastorale* pastorale_ = new Pastorale();

	// クライアント領域を設定
	const int32_t ClientWidth = 1280;
	const int32_t ClientHeight = 720;
	pastorale_->Initialize(kWindowTitle, ClientWidth, ClientHeight);


	// 三角形を複数用意
	// 各要素を決めていく
	const int MaxTriangle = 10;
	Model* triangle[MaxTriangle]{};
	Transform transform[MaxTriangle]{};

	Triangle element[MaxTriangle] = {

		// 1
		{{-0.4f,0.7f,0.0f,1.0f},
		{-0.3f,0.8f,0.0f,1.0f},
		{-0.2f,0.7f,0.0f,1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}},

		// 2
		{{-0.4f,0.5f,0.0f,1.0f},
		{-0.3f,0.6f,0.0f,1.0f},
		{-0.2f,0.5f,0.0f,1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}},

		// 3
		{{0.2f,0.7f,0.0f,1.0f},
		{0.3f,0.8f,0.0f,1.0f},
		{0.4f,0.7f,0.0f,1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}},

		// 4
		{{0.2f,0.5f,0.0f,1.0f},
		{0.3f,0.6f,0.0f,1.0f},
		{0.4f,0.5f,0.0f,1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}},

		// 5
		{{-0.1f,0.6f,0.0f,1.0f},
		{0.0f,0.7f,0.0f,1.0f},
		{0.1f,0.6f,0.0f,1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}},

		// 6
		{{-0.4f,0.2f,0.0f,1.0f},
		{-0.3f,0.3f,0.0f,1.0f},
		{-0.2f,0.2f,0.0f,1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}},

		// 7
		{{-0.4f,0.0f,0.0f,1.0f},
		{-0.3f,0.1f,0.0f,1.0f},
		{-0.2f,0.0f,0.0f,1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}},

		// 8
		{{0.2f,0.2f,0.0f,1.0f},
		{0.3f,0.3f,0.0f,1.0f},
		{0.4f,0.2f,0.0f,1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}},

		// 9
		{{0.2f,0.0f,0.0f,1.0f},
		{0.3f,0.1f,0.0f,1.0f},
		{0.4f,0.0f,0.0f,1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}},

		// 10
		{{-0.1f,0.1f,0.0f,1.0f},
		{0.0f,0.2f,0.0f,1.0f},
		{0.1f,0.1f,0.0f,1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}},
	};

	const char* rabel[] = {
		"triangle1",
		"triangle2",
		"triangle3",
		"triangle4",
		"triangle5",
		"triangle6",
		"triangle7",
		"triangle8",
		"triangle9",
		"triangle10",
	};

	// 頂点の初期化
	for (int i = 0; i < MaxTriangle; i++) {

		// 生成
		triangle[i] = new Model();

		transform[i] = {
			{1.0f,1.0f,1.0f},
			{0.0f,0.0f,0.0f},
			{0.0f,0.0f,0.0f},
		};

		// 初期化処理
		triangle[i]->Initialize(
			pastorale_->GetDirectXCommon());
	}



	// ウィンドウの×ボタンが押されるまでループ
	while (pastorale_->ProcessMessage() == 0) {
		// フレームの開始
		pastorale_->BeginFrame();

		///
		/// ↓更新処理ここから
		///

		pastorale_->Update();

		for (int i = 1; i < MaxTriangle; i++) {

			//transform[i].rotate.y += 0.03f;
		}

		for (int i = 0; i < MaxTriangle; i++) {
			triangle[i]->Update(
				element[i], transform[i], pastorale_->GetCamera()->transformationMatrixData_);
		}



		ImGui::Begin("Translation");

		ImGui::SliderFloat4("scale", &transform[0].scale.x, -1.0f, 1.0f);
		ImGui::SliderFloat4("rotate", &transform[0].rotate.x, -1.0f, 1.0f);
		ImGui::SliderFloat4("translation", &transform[0].translate.x, -1.0f, 1.0f);

		ImGui::End();



		ImGui::Begin("Color");

		for (int i = 0; i < MaxTriangle; i++) {

			ImGui::ColorEdit4(rabel[i], &element[i].color.x);
		}

		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 三角形複数描画
		for (int i = 0; i < MaxTriangle; i++) {
			triangle[i]->Draw();
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
