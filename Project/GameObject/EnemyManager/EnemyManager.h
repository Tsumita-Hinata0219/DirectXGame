#pragma once

#include "Enemy/Enemy.h"
#include "RandomGenerator.h"


// GameSceneの前方宣言
class GameScene;
// Playerの前方宣言
class Player;

/* EnemyManager */
class EnemyManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyManager() {};

	/// <summary>
	/// デストラクタ
	/// <summary>
	~EnemyManager();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);


#pragma region Get

#pragma endregion


#pragma region Set

	/// <summary>
	/// GameSceneの設定
	/// </summary>
	void SetGameScene(GameScene* scene) { gameScene_ = scene; }

	/// <summary>
	/// Playerの設定
	/// </summary>
	void SetPlayer(Player* player) { player_ = player; }

	/// <summary>
	/// 親子関係を結ぶ
	/// </summary>
	void SetParent(const WorldTransform* parent) { worldTrans_.SetParent(parent); }

#pragma endregion


private:

	/// <summary>
	/// 定期的に湧く処理
	/// </summary>
	void SpawnEnemysPeriodically();

	/// <summary>
	/// リストの登録
	/// </summary>
	void PushBackEnemy();


private:

	GameScene* gameScene_ = nullptr;
	Player* player_ = nullptr;

	WorldTransform worldTrans_{};


	std::unique_ptr<Model> enemyModel_ = nullptr;
	std::unique_ptr<Model> enemyBulletModel_ = nullptr;
	Vector3 velocity_{};

	Vector2 scopeX_;
	Vector2 scopeY_;
	Vector2 scopeZ_;

	Vector3 battlePosition_{};

	int initEnemysCount_ = 0;
	int intervalFrame_ = 0;
	int instanceEnemyCount_ = 0;
	int spawnTimer_ = 0;
	int thresholdEnemysCount_ = 0;
};

