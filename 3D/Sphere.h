#pragma once
#include "Function.h"
#include "Struct.h"
#include "Transform.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"



class Sphere {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Sphere();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sphere();


	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(const int32_t Width, const int32_t Height, DirectXCommon* dXCommon, WorldTransform transform);


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(SphereData sphere, WorldTransform transform, Matrix4x4& viewMatrix);


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(TextureManager* textureManager);


	/// <summary>
	/// 頂点データを設定する
	/// </summary>
	void SetVertex(SphereData sphere, WorldTransform transform, Matrix4x4& viewMatrix);


	/// <summary>
	/// 頂点リソース用のヒープ設定
	/// </summary>
	ID3D12Resource* CreateBufferResource(size_t sizeInBytes);


	/// <summary>
	/// 頂点バッファビューを作成する
	/// </summary>
	D3D12_VERTEX_BUFFER_VIEW CreateBufferView(ID3D12Resource* resource);


	/// <summary>
	/// TransformationMatrix用のResoureを作る
	/// </summary>
	void CreateTransformationMatrixResource();


	/// <summary>
	/// Sphere用のWorldViewProjectonMatrixを作る
	/// </summary>
	void CreateWVPMatrix(SphereData sphere, WorldTransform transform, Matrix4x4& viewMatrix);


	/// <summary>
	/// Material用のResourceを作る
	/// </summary>
	void CreateMaterialResource();


	/// <summary>
	/// 色の変換
	/// </summary>
	Vector4 FloatColor(unsigned int color);


private:

	int32_t ClientWidth_;
	int32_t ClientHeight_;

	DirectXCommon* dXCommon_ = nullptr;

	WorldTransform transformSphere_;


	// 分割数
	int32_t subdivision_ = 16;

	// 頂点リソースにデータを書き込む
	VertexData* vertexDataSphere_ = nullptr;


	// 頂点リソース用のヒープ設定
	ID3D12Resource* vertexResourceSphere_ = nullptr;


	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSphere_{};


	// TransformationMatrix用のResource
	ID3D12Resource* transformationMatrixResourceSphere_ = nullptr;

	Matrix4x4* transfomationMatrixDataSphere_ = nullptr;


	// Sphere用のworldViewProjectionMatrix
	Matrix4x4 worldMatrixSphere{};

	Matrix4x4 viewMatrixSphere{};

	Matrix4x4 projectionMatrixSphere{};

	Matrix4x4 worldProjectionMatrixSphere{};


	// Material用のResource
	ID3D12Resource* materialResourceSphere_ = nullptr;

	Vector4* materialDate_ = nullptr;


	// テクスチャの切り替え
	bool useMonsterBall = true;

};