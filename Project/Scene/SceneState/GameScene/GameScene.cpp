#include "GameScene.h"



/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {


}



/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize() {

	viewProjection_.Initialize();

}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state) {


	viewProjection_.UpdateMatrix();




#ifdef _DEBUG

	ImGui::Begin("GameScene");
	ImGui::End();

	ImGui::Begin("Camera");
	ImGui::DragFloat3("Rotate", &viewProjection_.rotate.x, 0.005f);
	ImGui::DragFloat3("Translate", &viewProjection_.translate.x, 1.0f);
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void GameScene::BackSpriteDraw() {


}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void GameScene::ModelDraw() {


}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw() {


}