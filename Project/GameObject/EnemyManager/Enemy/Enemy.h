#pragma once

#include "GameObject.h"

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
	void Init(Vector3 position, Vector3 move);

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
	/// 移動終了フラグ
	/// </summary>
	bool IsMoveFinish() { return isMoveFinish_; }

#pragma endregion 


#pragma region Set

	/// <summary>
	/// 移動先の座標設定
	/// </summary>
	void SetSpecificPosition(Vector3 position) { specificPosition_ = position; }

#pragma endregion 


private:

	/// <summary>
	/// 移動処理
	/// </summary>
	void MoveToSpecificPos();

private:

	unique_ptr<Model> object_ = nullptr;
	WorldTransform worldTransform_{};

	// 移動
	Vector3 vel_{};
	Vector3 move_{};
	Vector3 specificPosition_{ 0.0f, 0.0f, 0.0f };

	bool isMoveStart_ = false;
	bool isMoveFinish_ = false;

};
