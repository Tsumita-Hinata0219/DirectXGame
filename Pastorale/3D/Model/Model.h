#pragma once
#include "Function.h"
#include "Struct.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
#include "NormalGraphicPipeline.h"
#include "CreateResource.h"



class Model {

public:

	~Model() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();


	/// <summary>
	/// 三角形の描画
	/// </summary>
	void Draw(WorldTransform worldTransform, Matrix4x4& viewMatrix);


	/// <summary>
	/// 頂点の初期化
	/// </summary>
	void SetVertex(WorldTransform worldTransform, Matrix4x4& viewMatrix);


	/// <summary>
	/// 色の変換
	/// </summary>
	Vector4 FloatColor(unsigned int color);


#pragma region Set 設定

	void SetWorldTransform(WorldTransform worldTransform) { worldTansform_ = worldTansform_; }
	void SetTextureHandle(uint32_t texHD) { useTexture_ = texHD; }
	void SetColor(Vector4 color) { color = color; }

#pragma endregion


private:

	// ワールドトランスフォーム
	WorldTransform worldTansform_;

	// 座標
	Vector3 pos_{};

	// サイズ
	float size_;

	// テクスチャ
	uint32_t useTexture_ = 1;

	// 色データ
	Vector4 color_;

	// リソース
	ResourcePeroperty resource_{};
};

