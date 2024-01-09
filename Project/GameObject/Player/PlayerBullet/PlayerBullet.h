#pragma once

#include "GameObject.h"
#include "Collider.h"


// プレイヤークラスの前方宣言
class Player;

/* PlayerBulletクラス */
class PlayerBullet : public OBBCollider {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerBullet() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerBullet() {};

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

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	void OnCollision(uint32_t id) override;


#pragma region Get

	/// <summary>
	/// 生存フラグの取得
	/// </summary>
	bool IsAlive() { return life_.IsAlive; }
	bool IsDead() { return life_.IsDead; }

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
	/// 寿命の処理
	/// </summary>
	void UpdateLifeStatus();

	/// <summary>
	/// OBBのセッティング
	/// </summary>
	void SetupOBBProperties();

	/// <summary>
	/// フィルターのセッティング
	/// </summary>
	void SettingColliderAttributeAndMask();


private:

	Player* player_ = nullptr;

	unique_ptr<Model> model_ = nullptr;
	WorldTransform worldTrans_{};
	Vector3 velocity_{};
	float rotateVelocity_;
	Vector3 size_{};

	MortalityInfo life_{};
};
