#pragma once

#include "GameObject.h"

#include "EnemyManager/PhaseState/IEnemyPhaseState.h"
#include "EnemyManager/PhaseState/Approach/IEnemyApproachState.h"
#include "EnemyManager/PhaseState/Leave/IEnemyLeaveState.h"
#include "EnemyBullet/EnemyBullet.h"

#include "Collider.h"


// GameSceneの前方宣言
class GameScene;
// Playerの前方宣言
class Player;

/* Enemyクラス */
class Enemy : public OBBCollider {

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
	/// 衝突時コールバック関数
	/// </summary>
	void OnCollision(uint32_t id) override;

	/// <summary>
	/// フェーズの変更
	/// </summary>
	void ChangePhaseState(IEnemyPhaseState* newState);

	/// <summary>
	/// ステートパターン内で使用する移動用関数(加算 減算) 
	/// </summary>
	void Approach2BattlePosition();

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack();

	/// <summary>
	/// Vec3Vec3の比較関数
	/// 適当に作ったやつ
	/// </summary>
	bool compareVectors(const Vector3& v1, const Vector3& v2) {
		return std::tie(v1.x, v1.y, v1.z) == std::tie(v2.x, v2.y, v2.z);
	}


#pragma region Get

	/// <summary>
	/// PlayerWorldPosの取得
	/// </summary>
	Vector3 GetPlayerWorldPos() { return playerWorldPos_; }

	/// <summary>
	/// WorldTransformの取得
	/// </summary>
	WorldTransform GetWorldTransform() { return worldTrans_; }

	/// <summary>
	/// Velocityの取得
	/// </summary>
	Vector3 GetVelocity() { return velocity_; }

	/// <summary>
	/// バトルポジション
	/// </summary>
	Vector3 GetBattelPosition() { return battlePosition_; }

	/// <summary>
	/// 初期移動フラグ
	/// </summary>
	/// <returns></returns>
	bool GetInitMoveFlag() { return initMoveFlag_; }


	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	Vector3 GetWorldPosition() override { return worldTrans_.GetWorldPos(); }

	/// <summary>
	/// Sizeの取得
	/// </summary>
	Vector3 GetSize() override { return size_; }

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

	/// <summary>
	/// バトルポジション
	/// </summary>
	void SetBattlePosition(Vector3 position) { battlePosition_ = position; }

	/// <summary>
	/// 親子関係を結ぶ
	/// </summary>
	void SetParent(const WorldTransform* parent) { worldTrans_.SetParent(parent); }


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

	/// <summary>
	/// OBBのセッティング
	/// </summary>
	void SetupOBBProperties();

	/// <summary>
	/// フィルターのセッティング
	/// </summary>
	void SettingColliderAttributeAndMask();


private:

	GameScene* gameScene_ = nullptr;
	Player* player_ = nullptr;
	Vector3 playerWorldPos_{};
	Vector3 size_{};

	unique_ptr<Model> modle_ = nullptr;
	WorldTransform worldTrans_{};
	Vector3 velocity_{};
	float moveSpeed_;

	unique_ptr<Model> modleBullet_ = nullptr;
	Vector3 bulletVel_{};
	const float kBulletSpeed_ = 0.5f;
	EnemyBulletPropeties bullet_{};

	// ステートパターン
	IEnemyPhaseState* phaseState_;

	Vector3 battlePosition_{};

	bool initMoveFlag_ = false;

};
