#pragma once
#include "Function.h"


class Triangle {

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);


	/// <summary>
	/// 三角形の描画
	/// </summary>
	void Draw(Vector4 bottomLeft, Vector4 top, Vector4 bottoomRight);


	/// <summary>
	/// 解放処理
	/// </summary>
	void Release();



	// 頂点リソース用のヒープ設定
	void CreateVertexResource();

	// 頂点バッファビューを作成する
	void MakeVertexBufferView();


private:

	// 使用するアダプタ
	ID3D12Device* device_ = nullptr;


	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;


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

