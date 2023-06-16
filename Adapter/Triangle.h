#pragma once
#include "Function.h"


class Triangle {

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(DirectXCommon* directX);


	/// <summary>
	/// 三角形の描画
	/// </summary>
	void Draw();


	/// <summary>
	/// 解放処理
	/// </summary>
	void Relese();



	// 頂点リソース用のヒープ設定
	void CreateVertexResource();

	// 頂点バッファビューを作成する
	void MakeVertexBufferView();


private:

	// DirectX
	DirectXCommon* directX_;


	// なにこれ↓
	HRESULT hr_;


	// 頂点リソースにデータを書き込む
	Vector4* vertexData_ = nullptr;


	// 頂点リソース用のヒープ設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties_{};

	D3D12_RESOURCE_DESC vertexResourceDesc_{};

	ID3D12Resource* vertexResource_ = nullptr;


	// 頂点リソース用のヒープ設定
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
};