﻿#pragma once
#include "Function.h"
#include "Struct.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include "LightGraphicPipeline.h"



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
	void Initialize();


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(WorldTransform transform, Matrix4x4& viewMatrix);


	/// <summary>
	/// 頂点データを設定する
	/// </summary>
	void SetVertex();


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
	void CreateWVPMatrix(WorldTransform transform, Matrix4x4& viewMatrix);


	/// <summary>
	/// Material用のResourceを作る
	/// </summary>
	void CreateVertexResource();


	/// <summary>
	/// Material用のResourceを作る
	/// </summary>
	void CreateMaterialResource();


	/// <summary>
	/// DirectionalLight用のResourceを作る
	/// </summary>
	void CreateDirectionalLightingResource();


	/// <summary>
	/// 色の変換
	/// </summary>
	Vector4 FloatColor(unsigned int color);


private:

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

	TransformationMatrix* transfomationMatrixDataSphere_ = nullptr;


	// Sphere用のworldViewProjectionMatrix
	Matrix4x4 worldMatrixSphere{};

	Matrix4x4 viewMatrixSphere{};

	Matrix4x4 projectionMatrixSphere{};

	Matrix4x4 worldProjectionMatrixSphere{};


	// Material用のResource
	ID3D12Resource* materialResourceSphere_ = nullptr;

	Material materialDataSphere_{};
	

	// 光
	ID3D12Resource* directionalLightingResource_ = nullptr;

	DirectionalLight directionalLightData_{};


	// テクスチャの切り替え
	uint32_t useTexture_ = true;

	SphereData sphereElemnt_;

};