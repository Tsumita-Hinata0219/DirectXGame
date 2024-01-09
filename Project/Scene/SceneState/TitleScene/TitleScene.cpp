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
void TitleScene::Update(GameManager* Scene) {

	/* ----- ViewProjection カメラ ----- */
	viewProjection_.UpdateMatrix();


	/* ----- Skydome スカイドーム ----- */
	Skydome::Update();


	if (Input::TriggerKey(DIK_P)) {
		Scene->ChangeSceneState(new GameScene);
	}


#ifdef _DEBUG

	ImGui::Begin("TitleScene");
	ImGui::Text("Camera");
	ImGui::DragFloat3("CameraRotate", &viewProjection_.rotate.x, 0.005f);
	ImGui::DragFloat3("CameraTranslate", &viewProjection_.translate.x, 0.01f);
	ImGui::End();

#endif // _DEBUG
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
