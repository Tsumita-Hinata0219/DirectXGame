#pragma once

#include "Enemy/Enemy.h"
#include "RandomGenerator.h"

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

private:

	/// <summary>
	/// 定期的に湧く処理
	/// </summary>
	void SpawnEnemysPeriodically();

	/// <summary>
	/// リストの登録
	/// </summary>
	void PushBackEnemy();

	/// <summary>
	/// リストのカウント
	/// </summary>
	uint32_t CountEnemysList();


private:

	std::list<Enemy*> enemys_;
	Vector2 scopeX_;
	Vector2 scopeY_;
	Vector2 scopeZ_;

	Vector3 move_{};

	Vector3 specificPosition_{};

	int initEnemysCount_ = 0;
	int intervalFrame_ = 0;
	int instanceEnemyCount_ = 0;
	int spawnTimer_ = 0;
	int thresholdEnemysCount_ = 0;
};

