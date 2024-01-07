#pragma once

#include "GameObject.h"


/* Playerクラス */
class Player {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

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
	/// ゲームパッドの入力処理
	/// </summary>
	void JoyStateCommand();

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

private:

	std::unique_ptr<Model> objModel_ = nullptr;
	WorldTransform worldTrans_{};

	// 移動
	Vector3 move_{};
	float moveSpeed_;

	// 移動限界座標
	const float kMoveLimitX = 13.0f;
	const float kMoveLimitY = 7.0f;

	// ジョイコン
	XINPUT_STATE joyState_{};
};

