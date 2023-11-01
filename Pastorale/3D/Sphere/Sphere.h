#pragma once
#include "Function.h"
#include "Struct.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include "LightGraphicPipeline.h"
#include "CreateResource.h"



class Sphere {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Sphere() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sphere() {};


	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(WorldTransform worldTransform, Matrix4x4& viewMatrix);


	/// <summary>
	/// 頂点データを設定する
	/// </summary>
	void SetVertex(WorldTransform worldTransform, Matrix4x4& viewMatrix);


	/// <summary>
	/// 色の変換
	/// </summary>
	Vector4 FloatColor(unsigned int color);


#pragma region Set 設定

	void SetWorldTransform(WorldTransform worldTransform) { worldTansform_ = worldTansform_; }
	void SetRadius(float radius) { radius_ = radius; }
	void SetTextureHandle(uint32_t texHD) { useTexture_ = texHD; }
	void SetColor(Vector4 color) { material_.color = color; }
	void SetIsLighting(uint32_t isLight) { material_.enableLightting = isLight; }
	void SetDirectionalLight(DirectionalLight light) { light_ = light; }

#pragma endregion



private:

	// ワールドトランスフォーム
	WorldTransform worldTansform_;

	// 半径
	float radius_ = 1.0f;

	// テクスチャ
	uint32_t useTexture_;

	// 色データ
	Material material_;

	// 光データ
	DirectionalLight light_;

	// 分割数
	int32_t subdivision_ = 32;

	// リソース
	ResourcePeroperty resource_{};
};