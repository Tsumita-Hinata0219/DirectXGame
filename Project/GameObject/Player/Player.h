#pragma once

#include "GameObject.h"
#include "PlayerBullet/PlayerBullet.h"


// GameSceneの前方宣言
class GameScene;

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


#pragma region Get

	/// <summary>
	/// WorldTransformの取得
	/// </summary>
	WorldTransform GetWorldTransform() { return worldTrans_; }

#pragma endregion


#pragma region Set

	/// <summary>
	/// GameSceneの設定
	/// </summary>
	void SetGameScene(GameScene* scene) { gameScene_ = scene; }

#pragma endregion


private:

	/// <summary>
	/// バレットの更新処理
	/// </summary>
	void UpdateBullet();

	/// <summary>
	/// ゲームパッドの入力処理
	/// </summary>
	void JoyStateCommand();

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// バレットリストの登録
	/// </summary>
	void PushBackBullet();

private:

	std::unique_ptr<Model> objModel_ = nullptr;
	WorldTransform worldTrans_{};

	// PlayerBulelt
	std::unique_ptr<Model> bulletModel_ = nullptr;
	const float kBulletSpeed_ = 1.5f;

	// 移動
	Vector3 move_{};
	float moveSpeed_;

	// 移動限界座標
	const float kMoveLimitX = 19.0f;
	const float kMoveLimitY = 9.0f;


	// ジョイコン
	XINPUT_STATE joyState_{};

	GameScene* gameScene_ = nullptr;
};

