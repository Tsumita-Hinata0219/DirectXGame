#include "GameScene.h"



/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {

	/* ----- プレイヤー Player ----- */
	for (PlayerBullet* bullet : playerBulelts_) {
		delete bullet;
	}

}


/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize() {

	viewProjection_.Initialize();
	viewProjection_.rotate = { 0.33f, 0.0f, 0.0f };
	viewProjection_.translate = { 0.0f, 19.0f, -50.0f };

	
	/* ----- プレイヤー Player ----- */
	player_ = make_unique<Player>();
	player_->Initialize();
	player_->SetGameScene(this);

}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state) {

	/* ----- カメラ ViewProjection ----- */
	viewProjection_.UpdateMatrix();


	/* ----- プレイヤー Player ----- */
	PlayerUpdate();



#ifdef _DEBUG

	ImGui::Begin("GameScene");
	ImGui::Text("Camera");
	ImGui::DragFloat3("CameraRotate", &viewProjection_.rotate.x, 0.005f);
	ImGui::DragFloat3("CameraTranslate", &viewProjection_.translate.x, 0.01f);
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

	for (PlayerBullet* bullet : playerBulelts_) {
		bullet->Draw(viewProjection_);
	}

}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw() {


}




/// <summary>
/// プレイヤー更新処理
/// </summary>
void GameScene::PlayerUpdate() {

	// プレイヤーの更新処理
	player_->Update();


	// プレイヤーバレットの更新処理
	for (PlayerBullet* bullet : playerBulelts_) {
		bullet->Update();
	}


	// 死亡フラグが立ったバレットを削除
	playerBulelts_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
}

