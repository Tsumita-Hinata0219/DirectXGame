#pragma once
#include "Function.h"


class Model {

public:

	~Model();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(DirectXCommon* directX, Vector4 bottomLeft, Vector4 top, Vector4 bottomRight);

	/// <summary>
	/// 三角形の描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 頂点リソース用のヒープ設定
	/// </summary>
	void CreateVertexResource();

	/// <summary>
	/// 頂点バッファビューを作成する
	/// </summary>
	void MakeVertexBufferView();

	/// <summary>
	/// 頂点の初期化
	/// </summary>
	/// <param name="bottomLeft"></param>
	/// <param name="top"></param>
	/// <param name="bottoomRight"></param>
	void SetVertex(Vector4 bottomLeft, Vector4 top, Vector4 bottomRight);


private:


	DirectXCommon* directX_ = nullptr;


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

