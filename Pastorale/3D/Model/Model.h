#pragma once
#include "IModelState.h"
#include "ModelPlaneState.h"
#include "ModelSphereState.h"
#include "ModelObjState.h"



/* Modelクラス */
class Model {

public: // メンバ関数

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(IModelState* state);

	/// <summary>
	/// Objファイルの読み込み & 初期化処理
	/// </summary>
	void CreateFromObj(const std::string& directoryPath);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(WorldTransform worldTransform, Matrix4x4& viewMatrix);

#pragma region Get 取得

	WorldTransform GetWorldTransform() { return worldTansform_; }
	uint32_t GetUseTexture() { return useTexture_; }
	Vector4 GetColor() { return color_; }
	Material GetMaterial() { return material_; }
	DirectionalLight GetDirectionalLight() { return light_; }
	float GetRadius() { return radius_; }
	const std::string GetObjeDirectoryPaht() { return directoryPath_; }

#pragma endregion

#pragma region Set 設定

	void SetTexHandle(uint32_t texHandle) { useTexture_ = texHandle; }
	void SetColor(Vector4 color) { color_ = color; }
	void SetDirectionalLight(DirectionalLight light) { light_ = light; }
	void SetIsLighting(uint32_t isLight) { material_.enableLightting = isLight; }
	void SetRadius(float radius) { radius_ = radius; }

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

	// スフィアのマテリアル
	Material material_;

	// 光データ
	DirectionalLight light_;

	// スフィアの半径
	float radius_ = 1.0f;

	// Objのファイルパス
	std::string directoryPath_{};
};

