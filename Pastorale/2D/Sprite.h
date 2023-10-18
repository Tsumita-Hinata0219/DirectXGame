#pragma once
#include "Function.h"
#include "Struct.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
#include "WinApp.h"



class Sprite {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Sprite();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sprite();


	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(WorldTransform transform, SpriteData vertex);


	/// <summary>
	/// 描画処理
	/// </summary>
	void DrawSprite(TextureManager* textureManager);


	/// <summary>
	/// 頂点データを設定する
	/// </summary>
	void SetVertex(WorldTransform transform, SpriteData vertex);


	/// <summary>
	/// 頂点リソース用のヒープ設定
	/// </summary>
	static ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);


	/// <summary>
	/// 頂点バッファビューを作成する
	/// </summary>
	static D3D12_VERTEX_BUFFER_VIEW CreateBufferView(ID3D12Resource* resource, size_t sizeInBytes);


	/// <summary>
	/// TransformationMatrix用のResourceを作る
	/// </summary>
	void CreateTransformationMatrix();


	/// <summary>
	/// Sprite用のWorldViewProjectonMatrixを作る
	/// </summary>
	void CreateWVPMatrix(WorldTransform transform);


	/// <summary>
	/// Material用のResourceを作る
	/// </summary>
	void CreateMaterialResource();


	/// <summary>
	/// 色の変換
	/// </summary>
	Vector4 FloatColor(unsigned int color);




private:

	SpriteData vertex_;


	// 頂点リソースにデータを書き込む
	VertexData* vertexDataSprite_ = nullptr;


	// 頂点リソース用のヒープ設定
	ID3D12Resource* vertexResourceSprite_ = nullptr;


	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite_{};


	// TransformationMatrix用のResource
	ID3D12Resource* transformationMatrixResourceSprite_ = nullptr;

	Matrix4x4* transfomationMatrixDataSprite_ = nullptr;


	// Sprite用のworldViewProjectionMatrix
	Matrix4x4 worldMatrixSprite{};

	Matrix4x4 viewMatrixSprite{};

	Matrix4x4 projectionMatrixSprite{};

	Matrix4x4 worldProjectionMatrixSprite{};


	// Material用のResource
	ID3D12Resource* materialResource_ = nullptr;

	Vector4* materialDate_ = nullptr;


};