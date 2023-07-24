#pragma once
#include "Function.h"


class Model {

public:

	~Model();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

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
	/// 頂点の初期化
	/// </summary>
	/// <param name="bottomLeft"></param>
	/// <param name="top"></param>
	/// <param name="bottoomRight"></param>
	void SetVertex(Vector4 bottomLeft, Vector4 top, Vector4 bottomRight, unsigned int color);

	/// <summary>
	/// 三角形の描画
	/// </summary>
	void DrawTriangle(Vector4 bottomLeft, Vector4 top, Vector4 bottomRight, unsigned int color);
	
	/// <summary>
	/// 色の変換
	/// </summary>
	Vector4 FloatColor(unsigned int color);


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


	ID3D12Resource* materialResource_ = nullptr;
	Vector4* materialDate_ = nullptr;

};

