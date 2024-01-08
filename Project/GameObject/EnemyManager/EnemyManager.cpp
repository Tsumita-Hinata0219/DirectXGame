#include "EnemyManager.h"



/// <summary>
/// デストラクタ
/// <summary>
EnemyManager::~EnemyManager() {

	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
}


/// <summary>
/// 初期化処理
/// </summary>
void EnemyManager::Initialize() {


	scopeX_ = { -15.0f, 15.0f };
	scopeY_ = { 0.0f, 0.0f };
	scopeZ_ = { 50.0f, 150.0f };

	move_ = { 1.0f, 1.0f, 1.0f };

	specificPosition_ = { 0.0f, 0.0f, 0.0f };

	initEnemysCount_ = 5;
	intervalFrame_ = 250;
	spawnTimer_ = 0;
	instanceEnemyCount_ = 3;
	thresholdEnemysCount_ = 3;

	for (int i = 0; i < initEnemysCount_; i++) {

		PushBackEnemy();
	}
}


/// <summary>
/// 更新処理
/// </summary>
void EnemyManager::Update() {

	// 更新処理
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}

	// 移動終了フラグがっ立ったものは削除
	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->IsMoveFinish()) {
			delete enemy;
			return true;
		}
		return false;
		}
	);

	// 定期的に敵を湧かせる
	SpawnEnemysPeriodically();

	// 一定数以下になったら湧かせる
	if (CountEnemysList() < static_cast<uint32_t> (thresholdEnemysCount_)) {
		PushBackEnemy();
	}

	//if (Input::PushKeyPressed(DIK_SPACE)) {
	//	PushBackEnemy();
	//}

#ifdef _DEBUG

	ImGui::Begin("EnemyManager");
	ImGui::Text("EnemysList = %d", CountEnemysList());
	ImGui::Text("SpawnTimer = %d", spawnTimer_);
	ImGui::DragInt("SpaenInterval", &intervalFrame_, 1.0f, 0, 1000);
	ImGui::DragInt("Number of spawn", &instanceEnemyCount_, 1.0f, 0, 10);
	ImGui::DragInt("Minimum Enemys", &thresholdEnemysCount_, 1.0f, 0, 10);
	ImGui::DragFloat2("ScopeX", &scopeX_.x, 0.1f, 0.0f);
	ImGui::DragFloat2("ScopeY", &scopeY_.x, 0.1f, 0.0f);
	ImGui::DragFloat2("ScopeZ", &scopeZ_.x, 0.1f, 0.0f);
	ImGui::DragFloat3("Move", &move_.x, 0.1f, 0.0f, 10.0f);
	ImGui::DragFloat3("SpecificPosition", &specificPosition_.x, 0.1f);
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void EnemyManager::Draw(ViewProjection view) {

	for (Enemy* enemy : enemys_) {
		enemy->Draw(view);
	}
}



/// <summary>
/// 定期的に湧く処理
/// </summary>
void EnemyManager::SpawnEnemysPeriodically() {

	spawnTimer_++;

	if (spawnTimer_ >= intervalFrame_) {

		spawnTimer_ = 0;

		for (int i = 0; i < instanceEnemyCount_; i++) {
			PushBackEnemy();
		}
	}
}


/// <summary>
/// リストの登録
/// </summary>
void EnemyManager::PushBackEnemy() {

	Enemy* newEnemy = new Enemy();
	Vector3 newPos = RandomGenerator::getRandom(scopeX_, scopeY_, scopeZ_);

	newEnemy->Init(newPos, move_);
	newEnemy->SetSpecificPosition(specificPosition_);
	enemys_.push_back(newEnemy);
}


/// <summary>
/// リストのカウント
/// </summary>
uint32_t EnemyManager::CountEnemysList() {

	size_t count = enemys_.size();

	return static_cast<uint32_t> (count);
}