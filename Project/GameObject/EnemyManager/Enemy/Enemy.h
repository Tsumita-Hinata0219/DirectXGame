#pragma once

#include "GameObject.h"

#include "EnemyManager/PhaseState/IEnemyPhaseState.h"
#include "EnemyManager/PhaseState/Approach/IEnemyApproachState.h"
#include "EnemyManager/PhaseState/Leave/IEnemyLeaveState.h"

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
	void Init(Model& model, Vector3 position, Vector3 velocity);

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
	/// WorldTransformの設定
	/// </summary>
	void SetWorldTransform(WorldTransform worldTransform) { worldTrans_ = worldTransform; }

#pragma endregion 


private:



private:

	unique_ptr<Model> modle_ = nullptr;
	WorldTransform worldTrans_{};
	Vector3 velocity_{};

	// ステートパターン
	IEnemyPhaseState* phaseState_;

	Vector3 specificPosition_{};
};
