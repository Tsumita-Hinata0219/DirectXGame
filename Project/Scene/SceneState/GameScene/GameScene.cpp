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
	viewProjection_.rotate = { 0.45f, 0.0f, 0.0f };
	viewProjection_.translate = { 0.0f, 11.0f, -15.0f };

	
	/* ----- プレイヤー Player ----- */
	player_ = make_unique<Player>();
	player_->Initialize();

}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state) {


	viewProjection_.UpdateMatrix();


	/* ----- プレイヤー Player ----- */
	player_->Update();




#ifdef _DEBUG

	ImGui::Begin("GameScene");
	ImGui::End();
	ImGui::Begin("Camera");
	ImGui::DragFloat3("Rotate", &viewProjection_.rotate.x, 0.005f);
	ImGui::DragFloat3("Translate", &viewProjection_.translate.x, 0.01f);
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

	/* ----- プレイヤー Player ----- */
	player_->Draw(viewProjection_);

}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw() {


}