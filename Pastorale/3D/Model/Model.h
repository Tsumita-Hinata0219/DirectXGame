#pragma once
#include "IModelState.h"
#include "Plane/ModelPlane.h"



/* Modelクラス */
class Model {

public: // メンバ関数

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(IModelState* state);


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(WorldTransform worldTransform, Matrix4x4& viewMatrix);

#pragma region Get 取得

	WorldTransform GetWorldTransform() { return worldTansform_; }
	uint32_t GetUseTexture() { return useTexture_; }
	Vector4 GetColor() { return color_; }

#pragma endregion
	

private: // メンバ変数

	// モデルのステートパターン
	IModelState* state_ = nullptr;


	// ワールドトランスフォーム
	WorldTransform worldTansform_;

	// テクスチャ
	uint32_t useTexture_;

	// 色データ
	Vector4 color_;

};

