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
};


// スプライト構造体
struct SpriteData {
	Vector4 topLeft;
	Vector4 bottomLeft;
	Vector4 topRight;
	Vector4 bottomRight;
};


// 球
struct SphereData {
	Vector3 center;
	float radius;
};
//
//// 直線
//struct Line {
//	Vector3 origin; // !< 始点
//	Vector3 diff;   // !< 終点への差分ベクトル
//};
//
//// 半直線
//struct Ray {
//	Vector3 origin; // !< 始点
//	Vector3 diff;   // !< 終点への差分ベクトル
//};
//
//// 線分
//struct Segment {
//	Vector3 origin; // !< 始点
//	Vector3 diff;   // !< 終点への差分ベクトル
//};
//
//// 平面
//struct Plane {
//	Vector3 normal; // !< 法線
//	float distance; // !< 距離
//};
//
//// 三角形
//struct Triangle {
//	Vector3 vertices[3]; // !< 頂点
//};
//
//struct AABB {
//	Vector3 min; // !< 最少点
//	Vector3 max; // !< 最大点
//};
//



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
struct UsePSO {
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	D3D12_ROOT_PARAMETER rootParameters[3]{};
	D3D12_DESCRIPTOR_RANGE descriptorRange[1]{};
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[2]{};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	IDxcBlob* vertexShaderBlob;
	IDxcBlob* pixelShaderBlob;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	ID3D12PipelineState* graphicsPipelineState = nullptr;
	D3D12_STATIC_SAMPLER_DESC staticSamplers[1]{};
};