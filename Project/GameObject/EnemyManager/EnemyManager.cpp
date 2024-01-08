#include "EnemyManager.h"
#include "GameManager.h"


/// <summary>
/// デストラクタ
/// <summary>
EnemyManager::~EnemyManager() {}


/// <summary>
/// 初期化処理
/// </summary>
void EnemyManager::Initialize() {

	worldTrans_.Initialize();

	scopeX_ = { -10.0f, 10.0f };
	scopeY_ = { 0.0f, 0.0f };
	scopeZ_ = { 10.0f, 50.0f };

	velocity_ = { 0.0f, 0.0f, -0.3f };

	specificPosition_ = { 0.0f, 0.0f, 0.0f };

	initEnemysCount_ = 5;
	intervalFrame_ = 250;
	spawnTimer_ = 0;
	instanceEnemyCount_ = 3;
	thresholdEnemysCount_ = 3;


	enemyModel_ = make_unique<Model>();
	enemyModel_->CreateFromObj("Enemy");

	for (int i = 0; i < initEnemysCount_; i++) {

		PushBackEnemy();
	}
}


/// <summary>
/// 更新処理
/// </summary>
void EnemyManager::Update() {

	// 定期的に敵を湧かせる
	//SpawnEnemysPeriodically();

	worldTrans_.UpdateMatrix();

#ifdef _DEBUG

	ImGui::Begin("EnemyManager");
	ImGui::Text("SpawnTimer = %d", spawnTimer_);
	ImGui::DragInt("SpaenInterval", &intervalFrame_, 1.0f, 0, 1000);
	ImGui::DragInt("Number of spawn", &instanceEnemyCount_, 1.0f, 0, 10);
	ImGui::DragInt("Minimum Enemys", &thresholdEnemysCount_, 1.0f, 0, 10);
	ImGui::DragFloat2("ScopeX", &scopeX_.x, 0.1f, 0.0f);
	ImGui::DragFloat2("ScopeY", &scopeY_.x, 0.1f, 0.0f);
	ImGui::DragFloat2("ScopeZ", &scopeZ_.x, 0.1f, 0.0f);
	ImGui::DragFloat3("Move", &velocity_.x, 0.1f, 0.0f, 10.0f);
	ImGui::DragFloat3("SpecificPosition", &specificPosition_.x, 0.1f);
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void EnemyManager::Draw(ViewProjection view) {
	view;
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
	Vector3 newPos = Add(worldTrans_.GetWorldPos(), RandomGenerator::getRandom(scopeX_, scopeY_, scopeZ_));
	Vector3 newVel = velocity_;

	newEnemy->Init((*enemyModel_), newPos, newVel);
	
	gameScene_->AddEnemyList(newEnemy);
}

