#include "DebugScene.h"



/// <summary>
/// 初期化処理
/// </summary>
void DebugScene::Initialize() {


	sound1_ = Audio::LoadSound("kakkoii.wav");
	volum_ = 1.0f;
}


/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update(GameManager* state) {

	if (Input::TriggerKey(DIK_SPACE)) {
		Audio::PlayOnSound(sound1_, true, volum_);
	}
	if (Input::TriggerKey(DIK_RETURN)) {
		Audio::StopOnSound(sound1_);
	}

#ifdef _DEBUG

	ImGui::Begin("DebugScene");
	ImGui::End();

	ImGui::Begin("Sound");
	ImGui::DragFloat("volum", &volum_, 0.001f, 0.0f, 1.0f);
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void DebugScene::BackSpriteDraw() {


}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void DebugScene::ModelDraw() {


}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DebugScene::FrontSpriteDraw() {


}