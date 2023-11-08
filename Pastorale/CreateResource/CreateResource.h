#pragma once
#include "DirectXCommon.h"
#include "Struct.h"



class CreateResource {

public:

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static CreateResource* GetInstance();

	/// <summary>
	/// 頂点バッファリソースを作成する
	/// </summary>
	static ID3D12Resource* CreateBufferResource(size_t sizeInBytes);

	/// <summary>
	/// 頂点バッファビューを作成する
	/// </summary>
	static D3D12_VERTEX_BUFFER_VIEW CreateVertexBufferView(size_t sizeInbyte, ID3D12Resource* resource, int size);
	static D3D12_INDEX_BUFFER_VIEW CreateIndexBufferview(size_t sizeInbyte, ID3D12Resource* resource);

private:

	

};


struct ResourcePeroperty {
	// 頂点リソース用のヒープ設定
	ID3D12Resource* Vertex;
	// 
	ID3D12Resource* Index;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
	// 頂点バッファビュー
	D3D12_INDEX_BUFFER_VIEW IndexBufferView;
	// 
	ID3D12Resource* TransformationMatrix;
	// 
	ID3D12Resource* Material;
	// 
	ID3D12Resource* Lighting;

};