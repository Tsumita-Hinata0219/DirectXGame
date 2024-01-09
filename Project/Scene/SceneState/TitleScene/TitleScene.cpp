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
	viewProjection_.translate = { 0.0f, 7.0f, 0.0f };


	/* ----- TitleBar タイトルバー ----- */
	titleBarModel_ = make_unique<Model>();
	titleBarModel_->CreateFromObj("TitleBar");
	titleTransform_.Initialize();
	titleTransform_.scale = { 60.0f, 60.0f, 60.0f };
	titleTransform_.rotate = { 0.0f, 0.0f, 0.0f };
	titleTransform_.translate = { 00.0f, 50.0f, 400.0f };


	/* ----- Skydome スカイドーム ----- */
	Skydome::Initialize();


	/* ----- Ground グラウンド ----- */
	Ground::Initialize();
}


/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update(GameManager* Scene) {

	/* ----- ViewProjection カメラ ----- */
	viewProjection_.UpdateMatrix();


	/* ----- TitleBar タイトルバー ----- */
	titleTransform_.UpdateMatrix();


	/* ----- Skydome スカイドーム ----- */
	Skydome::Update();


	/* ----- Ground グラウンド ----- */
	Ground::Update();


	if (Input::TriggerKey(DIK_P)) {
		Scene->ChangeSceneState(new GameScene);
	}


#ifdef _DEBUG

	ImGui::Begin("TitleScene");
	ImGui::Text("Camera");
	ImGui::DragFloat3("CameraRotate", &viewProjection_.rotate.x, 0.005f);
	ImGui::DragFloat3("CameraTranslate", &viewProjection_.translate.x, 0.01f);
	ImGui::End();
	ImGui::Begin("TitleBar");
	ImGui::DragFloat3("Scale", &titleTransform_.scale.x, 0.05f);
	ImGui::DragFloat3("Rotate", &titleTransform_.rotate.x, 0.005f);
	ImGui::DragFloat3("Translate", &titleTransform_.translate.x, 0.1f);
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

	/* ----- TitleBar タイトルバー ----- */
	titleBarModel_->Draw(titleTransform_, viewProjection_);


	/* ----- Skydome スカイドーム ----- */
	Skydome::Draw(viewProjection_);


	/* ----- Ground グラウンド ----- */
	Ground::Draw(viewProjection_);

}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void TitleScene::FrontSpriteDraw() {


}
