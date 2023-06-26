#pragma once
#include "Function.h"


class Model {

public:

	~Model();

	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// 頂点リソース用のヒープ設定
	/// </summary>
	void CreateVertexResource();

	/// <summary>
	/// 頂点バッファビューを作成する
	/// </summary>
	void MakeVertexBufferView();

	/// <summary>
	/// 三角形の描画
	/// </summary>
	/// <param name="bottomLeft"></param>
	/// <param name="top"></param>
	/// <param name="bottoomRight"></param>
	void Triangle(Vector4 bottomLeft, Vector4 top, Vector4 bottoomRight);

	/// <summary>
	/// アクセッサ
	/// </summary>
	void SetDirectXDevice(ID3D12Device* device);
	void SetDirectXCommandList(ID3D12GraphicsCommandList* commandList);


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

