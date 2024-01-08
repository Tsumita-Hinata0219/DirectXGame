#pragma once

#include "GameObject.h"

#include "EnemyManager/PhaseState/IEnemyPhaseState.h"
#include "EnemyManager/PhaseState/Approach/IEnemyApproachState.h"
#include "EnemyManager/PhaseState/Leave/IEnemyLeaveState.h"
#include "EnemyBullet/EnemyBullet.h"


// GameSceneの前方宣言
class GameScene;
// Playerの前方宣言
class Player;

/* Enemyクラス */
class Enemy {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy() {};

	/// <summary>
	/// デストラクタ
	/// <summary>
	~Enemy() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(Model& modelEne, Model& modelBullet, Vector3 position, Vector3 velocity);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);

	/// <summary>
	/// フェーズの変更
	/// </summary>
	void ChangePhaseState(IEnemyPhaseState* newState);

	/// <summary>
	/// ステートパターン内で使用する移動用関数(加算 減算) 
	/// </summary>
	void AddTransform(const Vector3& velocity);
	void SubtractTransform(const Vector3& velocity);

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack();


#pragma region Get

	/// <summary>
	/// WorldTransformの取得
	/// </summary>
	/// <returns></returns>
	WorldTransform GetWorldTransform() { return worldTrans_; }

	/// <summary>
	/// Velocityの取得
	/// </summary>
	Vector3 GetVelocity() { return velocity_; }

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
	/// WorldTransformの設定
	/// </summary>
	void SetWorldTransform(WorldTransform worldTransform) { worldTrans_ = worldTransform; }

#pragma endregion 


private:

	/// <summary>
	/// 射撃準備処理
	/// </summary>
	void FirePreparation();

	/// <summary>
	/// 弾の射撃処理
	/// </summary>
	void FireBullet();

private:

	GameScene* gameScene_ = nullptr;
	Player* player_ = nullptr;

	unique_ptr<Model> modle_ = nullptr;
	WorldTransform worldTrans_{};
	Vector3 velocity_{};

	unique_ptr<Model> modleBullet_ = nullptr;
	Vector3 bulletVel_{};
	const float kBulletSpeed_ = 0.5f;
	EnemyBulletPropeties bullet_{};

	// ステートパターン
	IEnemyPhaseState* phaseState_;

	Vector3 specificPosition_{};
	

};
