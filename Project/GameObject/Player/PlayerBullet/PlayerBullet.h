#pragma once

#include "GameObject.h"

class PlayerBullet {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerBullet();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerBullet();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(Vector3& position, Vector3& velocity);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);


private:



private:

	unique_ptr<Model> model_ = nullptr;
	WorldTransform worldTrans_{};
	Vector3 velocity_{};

};

