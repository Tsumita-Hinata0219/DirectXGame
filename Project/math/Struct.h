#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>

#include <vector>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix4x4.h>



// 頂点データ
struct VertexData {
	Vector4 position;
	Vector2 texCoord;
	Vector3 normal;
};


// スプライト構造体
struct SpriteData {
	Vector4 topLeft;
	Vector4 bottomLeft;
	Vector4 topRight;
	Vector4 bottomRight;
};


// uvTransform
struct UVTransform {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};


// 
struct TransformationMatrix {
	Matrix4x4 WVP;
	Matrix4x4 World;
};


// 球
struct SphereData {
	Vector3 center;
	float radius;
};


// マテリアル
struct Material {
	Vector4 color;
	int32_t enableLightting;
};
struct MaterialSprite {
	Vector4 color;
	Matrix4x4 uvTransform;
};


// モデルデータ
struct ModelData {
	std::vector<VertexData> vertices;
};


// 平行光源
struct DirectionalLight {
	Vector4 color;     // ライトの色
	Vector3 direction; // ライトの向き
	float intensity;   // 輝度
};


// コマンド
struct Commands {
	ID3D12CommandQueue* Queue;		   // コマンドキュー
	ID3D12CommandAllocator* Allocator; // コマンドアロケータ
	ID3D12GraphicsCommandList* List;   // コマンドリスト
};


// スワップチェーン
struct SwapChains {
	IDXGISwapChain4* swapChain;				// スワップチェーン
	ID3D12Resource* Resources[2];	// スワップチェーンリソース
	DXGI_SWAP_CHAIN_DESC1 Desc{}; // スワップチェーンデスク
};


// RTV
struct RTV {
	ID3D12DescriptorHeap* DescriptorHeap;
	D3D12_RENDER_TARGET_VIEW_DESC Desc{};
	D3D12_CPU_DESCRIPTOR_HANDLE Handles[2];
	D3D12_CPU_DESCRIPTOR_HANDLE StartHandle;
};


// CompileShader
struct CompileShaders {
	IDxcBlobEncoding* Source;
	DxcBuffer SourceBuffer{};
	IDxcResult* Result;
	IDxcBlobUtf8* Error;
	IDxcBlob* Blob;
};


// PSO
struct PsoProperty {
	ID3D12PipelineState* graphicsPipelineState = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
};


struct SPSO {
	PsoProperty normal;
	PsoProperty Sprite;
	PsoProperty Light;
};



// 直線
struct Line {
	Vector3 origin; // !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};


// 半直線
struct Ray {
	Vector3 origin; // !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};


// 線分
struct Segment {
	Vector3 origin; // !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};


// 平面
struct Plane {
	Vector3 normal; // !< 法線
	float distance; // !< 距離
};


// 三角形
//struct Triangle {
//	Vector3 vertices[3]; // !< 頂点
//};


// AABB
struct AABB {
	Vector3 min; // !< 最少点
	Vector3 max; // !< 最大点
};