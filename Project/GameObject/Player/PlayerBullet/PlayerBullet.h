#pragma once

#include "GameObject.h"


// プレイヤークラスの前方宣言
class Player;

/* PlayerBulletクラス */
class PlayerBullet {

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

private:

	Player* player_ = nullptr;

	unique_ptr<Model> model_ = nullptr;
	WorldTransform worldTrans_{};
	Vector3 velocity_{};
	float rotateVelocity_;

	MortalityInfo life_{};
};
