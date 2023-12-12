#include "DebugScene.h"



/// <summary>
/// デストラクタ
/// </summary>
DebugScene::~DebugScene() {}



/// <summary>
/// 初期化処理
/// </summary>
void DebugScene::Initialize() {

	viewProjection_.Initialize();

	engineManual_ = std::make_unique<EngineManual>();
	engineManual_->Initialize();
}



/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update(GameManager* state) {

	engineManual_->Update();

	viewProjection_.UpdateMatrix();


#ifdef _DEBUG

	ImGui::Begin("DebugScene");
	ImGui::End();

#endif // _DEBUG
}



/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void DebugScene::BackSpriteDraw() {

	engineManual_->BackSpriteDraw();
}



/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void DebugScene::ModelDraw() {

	engineManual_->ModelDraw(viewProjection_);
}



/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DebugScene::FrontSpriteDraw() {


}


