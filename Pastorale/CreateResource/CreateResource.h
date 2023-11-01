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
	static D3D12_VERTEX_BUFFER_VIEW CreateBufferView(size_t sizeInbyte, ID3D12Resource* resource, int size);

private:

	

};


struct ResourcePeroperty {
	// 頂点リソース用のヒープ設定
	ID3D12Resource* Vertex;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW BufferView;
	// 
	ID3D12Resource* TransformationMatrix;
	// 
	ID3D12Resource* Material;
	// 
	ID3D12Resource* Lighting;

};