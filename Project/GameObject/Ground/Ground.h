#pragma once

#include "GameObject.h"

/* Skydomeクラス */
class Ground {

public:

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static Ground* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	static void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	static void Draw(ViewProjection view);

private:

private:

	unique_ptr<Model> model_ = nullptr;
	WorldTransform worldTrans_{};
};



