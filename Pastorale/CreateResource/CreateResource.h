#pragma once
#include "DirectXCommon.h"



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

// 頂点データ
struct VertexData {
	Vector4 position;
	Vector2 texCoord;
	Vector3 normal;
};

// 
struct TransformationMatrix {
	Matrix4x4 WVP;
	Matrix4x4 World;
};

// マテリアル
struct Material {
	Vector4 color;
	int32_t enableLightting;
};

// 平行光源
struct DirectionalLight {
	Vector4 color;     // ライトの色
	Vector3 direction; // ライトの向き
	float intensity;   // 輝度
};


struct ResourcePeroperty {
	// 頂点リソース用のヒープ設定
	ID3D12Resource* BufferResource;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW BufferView;
	// 
	ID3D12Resource* TransformationMatrix;
	// 
	ID3D12Resource* Material;
	// 
	ID3D12Resource* Lighting;

};