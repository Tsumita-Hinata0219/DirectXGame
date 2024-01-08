#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Function.h"
#include "ImGuiManager.h"


class DebugCamera {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	DebugCamera() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DebugCamera() {};

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static DebugCamera* GetInstance();

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
	static void Draw();


#pragma region Get

	/// <summary>
	/// ViewProjectionの取得
	/// </summary>
	ViewProjection GetViewProjection() { return viewProjection_; }

#pragma endregion


private:

	WorldTransform worldTransform_{};
	ViewProjection viewProjection_{};
	
	Matrix4x4 matRotate_{};

	Vector3 offset_;

	bool isDebugCamera_ = false;

};