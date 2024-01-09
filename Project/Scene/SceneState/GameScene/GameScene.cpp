#include "GameScene.h"



/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {

	/* ----- プレイヤー Player ----- */
	for (PlayerBullet* bullet : playerBulelts_) {
		delete bullet;
	}

	/* ----- Enemy エネミー ----- */
	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
	for (EnemyBullet* eneBul : enemyBullets_) {
		delete eneBul;
	}
}


/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize() {

	/* ----- ViewProjection カメラ ----- */
	viewProjection_.Initialize();


	/* ----- DebugCamera デバッグカメラ ----- */
	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();


	/* ----- RailCamera レールカメラ ----- */
	railCamera_ = make_unique<RailCamera>();
	railCamera_->Initizlia();


	/* ----- Skydome スカイドーム ----- */
	skydome_ = make_unique<Skydome>();
	skydome_->Initialize();


	/* ----- Ground グラウンド ----- */
	ground_ = make_unique<Ground>();
	//ground_->Initialize();


	/* ----- Player プレイヤー ----- */
	player_ = make_unique<Player>();
	player_->SetGameScene(this);
	Vector3 initPlayerRotate = { 0.0f, 0.0f, 0.0f };
	Vector3 initPlayerTrasnlate = { 0.0f, -15.0f, 50.0f };
	player_->Initialize(initPlayerRotate, initPlayerTrasnlate);


	/* ----- Enemy エネミー ----- */
	enemyManager_ = make_unique<EnemyManager>();
	enemyManager_->SetGameScene(this);
	enemyManager_->SetPlayer(player_.get());
	Vector3 initEnemyTrasnlate = { 0.0f, -15.0f, 0.0f };
	enemyManager_->Initialize(initEnemyTrasnlate);


	/* ----- Parent ペアレント ----- */
	player_->SetParent(&railCamera_->GetWorldTransform());
	enemyManager_->SetParent(&railCamera_->GetWorldTransform());
}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state) {

	/* ----- ViewProjection カメラ ----- */
	viewProjection_.UpdateMatrix();


	/* ----- Skydome スカイドーム ----- */
	skydome_->Update();


	/* ----- Ground グラウンド ----- */
	//ground_->Update();


	/* ----- Player プレイヤー ----- */
	PlayerUpdate();


	/* ----- Enemy エネミー ----- */
	EnemyUpdate();


	// カメラの処理
	if (isDebugCaneraActive_) {

		/* ----- DebugCamera デバッグカメラ ----- */
		debugCamera_->Update();
		viewProjection_ = debugCamera_->GetViewProjection();
	}
	else {

		/* ----- RailCamera レールカメラ ----- */
		railCamera_->Update();
		viewProjection_ = railCamera_->GetViewProjection();
	}


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

	/* ----- Skydome スカイドーム ----- */
	skydome_->Draw(viewProjection_);


	/* ----- Ground グラウンド ----- */
	//ground_->Draw(viewProjection_);


	/* ----- Player プレイヤー ----- */
	player_->Draw(viewProjection_);
	for (PlayerBullet* bullet : playerBulelts_) {
		bullet->Draw(viewProjection_);
	}


	/* ----- Enemy エネミー ----- */
	for (Enemy* enemy : enemys_) {
		enemy->Draw(viewProjection_);
	}
	for (EnemyBullet* eneBul : enemyBullets_) {
		eneBul->Draw(viewProjection_);
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



/// <summary>
/// エネミー更新処理
/// </summary>
void GameScene::EnemyUpdate() {

	// エネミーマネージャーの更新処理
	enemyManager_->Update();

	// エネミーの更新処理
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}

	// エネミーバレットの更新処理
	for (EnemyBullet* eneBul : enemyBullets_) {
		eneBul->Update();
	}
}