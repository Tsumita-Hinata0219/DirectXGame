#include "TitleScene.h"




/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene() {


}


/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize() {

	/* ----- ViewProjection カメラ ----- */
	viewProjection_.Initialize();


	/* ----- Skydome スカイドーム ----- */
	Skydome::Initialize();
}


/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update(GameManager* state) {

	/* ----- ViewProjection カメラ ----- */
	viewProjection_.UpdateMatrix();


	/* ----- Skydome スカイドーム ----- */
	Skydome::Update();
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void TitleScene::BackSpriteDraw() {


}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void TitleScene::ModelDraw() {


	/* ----- Skydome スカイドーム ----- */
	Skydome::Draw(viewProjection_);

}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void TitleScene::FrontSpriteDraw() {


}
