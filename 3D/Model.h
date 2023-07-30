#pragma once
#include "Function.h"
#include <Matrix4x4.h>
#include "Transform.h"


// 三角形描画の各要素
struct Triangle {
	Vector4 bottomLeft;  // 左下座標
	Vector4 top;		 // 上座標
	Vector4 bottomRight; // 右下座標
	unsigned int color;	 // 色
};


class Model {

public:

	~Model();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(DirectXCommon* dXCommon);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(Triangle element, Transform& transform, Matrix4x4& ViewMatrix);

	/// <summary>
	/// 三角形の描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 頂点リソース用のヒープ設定
	/// </summary>
	static ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);

	/// <summary>
	/// 頂点バッファビューを作成する
	/// </summary>
	static D3D12_VERTEX_BUFFER_VIEW MakeBufferView(ID3D12Resource* resource, size_t sizeInBytes);

	/// <summary>
	/// Material用のResourceを作る
	/// </summary>
	void MakeMaterialResource();

	/// <summary>
	/// TransformationMatrix用のResoureを作る
	/// </summary>
	void MakeTransformationMatResource();

	/// <summary>
	/// 頂点の初期化
	/// </summary>
	void SetVertex(Triangle element, Transform& transform, Matrix4x4& ViewMatrix);

	/// <summary>
	/// 色の変換
	/// </summary>
	Vector4 FloatColor(unsigned int color);


	Matrix4x4 SetWorldMatrix(Matrix4x4 worldMatrix) { worldMatrix_ = worldMatrix; }


public:

	Triangle element;

private:

	DirectXCommon* dXCommon_ = nullptr;


	HRESULT hr_;


	// 頂点リソースにデータを書き込む
	Vector4* vertexData_ = nullptr;


	// 頂点リソース用のヒープ設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties_{};

	D3D12_RESOURCE_DESC vertexResourceDesc_{};

	ID3D12Resource* vertexResource_ = nullptr;


	// 頂点リソース用のヒープ設定
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};


	ID3D12Resource* materialResource_ = nullptr;
	Vector4* materialDate_ = nullptr;


	ID3D12Resource* wvpResource_ = nullptr;
	Matrix4x4* wvpData_ = nullptr;


	Matrix4x4 worldMatrix_;

};

