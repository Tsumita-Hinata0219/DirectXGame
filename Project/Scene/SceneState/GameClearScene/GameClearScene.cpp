#include "GameClearScene.h"



/// <summary>
/// デストラクタ
/// </summary>
GameClearScene::~GameClearScene() {


}


/// <summary>
/// 初期化処理
/// </summary>
void GameClearScene::Initialize() {

	/* ----- ViewProjection カメラ ----- */
	viewProjection_.Initialize();
	viewProjection_.translate = { 0.0f, 7.0f, 0.0f };



	/* ----- Skydome スカイドーム ----- */
	Skydome::Initialize();


	/* ----- Ground グラウンド ----- */
	Ground::Initialize();
}


/// <summary>
/// 更新処理
/// </summary>
void GameClearScene::Update(GameManager* Scene) {

	/* ----- ViewProjection カメラ ----- */
	viewProjection_.UpdateMatrix();



	/* ----- Skydome スカイドーム ----- */
	Skydome::Update();


	/* ----- Ground グラウンド ----- */
	Ground::Update();


	// ゲームパッドを見接続なら何もせず抜ける
	if (!Input::GetJoyStickState(joyState_)) {
		return;
	}

	if (Input::TriggerKey(DIK_P)) {
		Scene->ChangeSceneState(new TitleScene);
		return;
	}
	if (Input::IsButtonPress(joyState_, XINPUT_GAMEPAD_A)) {
		Scene->ChangeSceneState(new TitleScene);
		return;
	}


#ifdef _DEBUG

	ImGui::Begin("GameClearScene");
	ImGui::Text("Camera");
	ImGui::DragFloat3("CameraRotate", &viewProjection_.rotate.x, 0.005f);
	ImGui::DragFloat3("CameraTranslate", &viewProjection_.translate.x, 0.01f);
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void GameClearScene::BackSpriteDraw() {


}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void GameClearScene::ModelDraw() {

	


	/* ----- Skydome スカイドーム ----- */
	Skydome::Draw(viewProjection_);


	/* ----- Ground グラウンド ----- */
	Ground::Draw(viewProjection_);

}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameClearScene::FrontSpriteDraw() {


}
