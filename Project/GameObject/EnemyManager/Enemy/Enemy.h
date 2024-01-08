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
	void Init(Model& model, Vector3 position, Vector3 velocity);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);


#pragma region Get

#pragma endregion 


#pragma region Set

#pragma endregion 


private:



private:

	unique_ptr<Model> modle_ = nullptr;
	WorldTransform worldTrans_{};
	Vector3 velocity_{};

	Vector3 specificPosition_{};
};
