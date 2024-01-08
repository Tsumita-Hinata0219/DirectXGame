#pragma once

#include "GameObject.h"

/* Skydomeクラス */
class Skydome {

public:

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

private:

	unique_ptr<Model> model_ = nullptr;
	WorldTransform worldTrans_{};
};

