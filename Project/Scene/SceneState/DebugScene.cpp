#include "DebugScene.h"



/// <summary>
/// 初期化処理
/// </summary>
void DebugScene::Initialize() {



}


/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update(GameManager* state) {


#ifdef _DEBUG

	ImGui::Begin("DebugScene");
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