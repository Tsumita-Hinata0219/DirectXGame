#pragma once
#include "Function.h"
#include "Struct.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteGraphicPipeline.h"
#include "CreateResource.h"




class Sprite {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Sprite() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sprite() {};


	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Vector2 pos, Vector2 size);


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(WorldTransform& transform);


	/// <summary>
	/// 頂点データを設定する
	/// </summary>
	void SetVertex(WorldTransform transform);


	/// <summary>
	/// 色の変換
	/// </summary>
	Vector4 FloatColor(unsigned int color);


#pragma region Set 設定

	void SetWorldTransform(WorldTransform worldTransform) { worldTansform_ = worldTansform_; }
	void SetPosition(Vector2 position) { position_ = position; }
	void SetTextureHandle(uint32_t texHD) { useTexture_ = texHD; }
	void SetSize(Vector2 size) { size_ = size; }
	void SetColor(Vector4 color) { color_ = color; }

#pragma endregion


private:

	// ワールドトランスフォーム
	WorldTransform worldTansform_;

	// 座標
	Vector2 position_;

	// 画像サイズ
	Vector2 size_;

	// テクスチャ
	uint32_t useTexture_;

	// 色データ
	Vector4 color_;

	// リソース
	ResourcePeroperty resource_{};
};