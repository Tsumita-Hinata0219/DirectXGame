#pragma once

#include "GameObject.h"


struct EnemyBulletPropeties {

	int32_t FireInterval;
	int32_t FireTimer; 
};


// Enemyの前方宣言
class Enemy;

/* EnemyBulletクラス */
class EnemyBullet {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyBullet() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyBullet() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(Model& model, Vector3& position, Vector3& velocity);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);


#pragma region Get

	/// <summary>
	/// 生存フラグの取得
	/// </summary>
	bool IsAlive() { return life_.IsAlive; }
	bool IsDead() { return life_.IsDead; }

#pragma endregion


#pragma region Set

	/// <summary>
	/// Playerの設定
	/// </summary>
	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }

#pragma endregion


private:

	/// <summary>
	/// 寿命の処理
	/// </summary>
	void UpdateLifeStatus();

private:

	Enemy* enemy_ = nullptr;

	unique_ptr<Model> model_ = nullptr;
	WorldTransform worldTrans_{};
	Vector3 velocity_{};
	float rotateVelocity_;

	MortalityInfo life_{};

};

