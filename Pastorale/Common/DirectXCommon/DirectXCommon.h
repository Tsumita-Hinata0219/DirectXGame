#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

#include "WinApp.h"
#include "DirectXCommon.h"
#include "GraphicPipelineManager.h"
#include "Function.h"
#include "Struct.h"




/// <summary>
/// DirectXCommonクラス
/// </summary>
class DirectXCommon {

public: // メンバ関数

	/// <summary>
	/// DirectXCommonのインスタンスの取得
	/// </summary>
	static DirectXCommon* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// 描画前処理
	/// </summary>
	static void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 解放処理
	/// </summary>
	static void Release();

	/// <summary>
	/// CompileShader関数
	/// </summary>
	static IDxcBlob* CompileShader(
		// CompilerするShaderファイルへのパス
		const std::wstring& filePath,
		// Compilerに使用するProfile
		const wchar_t* profile,
		// 初期化で生成したものを3つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler);


#pragma region Get 取得

	/// <summary>
	/// 
	/// </summary>
	ID3D12Device* const GetDevice() { return DirectXCommon::GetInstance()->device_; };

	/// <summary>
	/// 
	/// </summary>
	Commands const GetCommands() { return DirectXCommon::GetInstance()->commands_; }

	/// <summary>
	/// 
	/// </summary>
	SwapChains const GetSwapChains() { return DirectXCommon::GetInstance()->swapChains_; }

	/// <summary>
	/// 
	/// </summary>
	RTV const GetRTV() { return DirectXCommon::GetInstance()->rtv_; }

	/// <summary>
	/// 
	/// </summary>
	ID3D12DescriptorHeap* const GetSrvDescriptorHeap() { return DirectXCommon::GetInstance()->srvDescriptorHeap_; }

	/// <summary>
	/// 
	/// </summary>
	D3D12_DEPTH_STENCIL_DESC const GetDepthStencilDesc() { return DirectXCommon::GetInstance()->depthStencilDesc_; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	IDxcUtils* const GetDxcUtils() { return DirectXCommon::GetInstance()->dxcUtils_; }

	/// <summary>
	/// 
	/// </summary>
	IDxcCompiler3* const GetDxcCompiler() { return DirectXCommon::GetInstance()->dxcCompiler_; }

	/// <summary>
	/// 
	/// </summary>
	IDxcIncludeHandler* const GetIncludeHandler() { return DirectXCommon::GetInstance()->includeHandler_; }

	/// <summary>
	/// DescriptorHandleを取得する
	/// </summary>
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

#pragma endregion


#pragma region Set 設定

	/// <summary>
	/// 
	/// </summary>
	void SetDepthStencilDesc(D3D12_DEPTH_STENCIL_DESC depthStencilDesc) { DirectXCommon::GetInstance()->depthStencilDesc_ = depthStencilDesc; }

	/// <summary>
	/// 
	/// </summary>
	void SetUsePso(UsePSO usePso) { DirectXCommon::GetInstance()->usePso_ = usePso; }

#pragma endregion


private: // メンバ関数

	// DXGIファクトリーの生成
	static void CreateDxgiFactory();

	// D3D12Deviceの生成
	static void CreateDevice();

	// コマンドキューを生成する
	static void CreateCommandQueue();

	// エラーと警告の抑制
	static void DebugErrorInfoQueue();

	// コマンドアロケータを作成
	static void CreateCommandAllocator();

	// コマンドリストを生成する
	static void CreateCommandList();

	// スワップチェーンを生成する
	static void CreateSwapChain();

	// ディスクリプタヒープを生成する
	static void SetDescriptorHeap();

	// SwapChainからResourceを引っ張ってくる
	static void CreateSwapChainResources();

	// RTVを作る
	static void SettingRTV();

	// 状態を遷移する
	static void ChanegResourceState();

	// Fenceを生成する
	static void MakeFence();

	// DXCの初期化
	//static void InitializeDXC();


	// ViewportとScissor
	static void SetViewport();

	static void SetScissor();


	// 
	static ID3D12DescriptorHeap* CreateDescriptorHeap(
		ID3D12Device* device,
		D3D12_DESCRIPTOR_HEAP_TYPE heapType,
		UINT numDescriptors,
		bool shaderVisible);


	// Textureの深度の設定をしていく
	static ID3D12Resource* CreateDepthStencilTexturerResource(int32_t width, int32_t height);


	// depthStencilResourceを作る
	static void CreateDepthStencilResource();


private: // メンバ変数

	// デバッグレイヤー
	ID3D12Debug1* debugController_ = nullptr;


	// DXGIFactory
	IDXGIFactory7* dxgiFactory_ = nullptr;


	// 使用するアダプタ用の変数
	IDXGIAdapter4* useAdapter_ = nullptr;

	ID3D12Device* device_ = nullptr;


	// エラー・警告・即ち停止
	ID3D12InfoQueue* infoQueue_ = nullptr;

	// なにこれ↓
	D3D12_INFO_QUEUE_FILTER filter_{};

	// コマンド
	Commands commands_;


	// バックバッファインデックス
	UINT backBufferIndex_;


	// TransitionBarrierの設定
	D3D12_RESOURCE_BARRIER barrier_{};


	// スワップチェーン
	SwapChains swapChains_;


	// ディスクリプタヒープ
	ID3D12DescriptorHeap* srvDescriptorHeap_ = nullptr;


	// RTV
	RTV rtv_;


	// Fence
	ID3D12Fence* fence_ = nullptr;
	uint64_t fenceValue_ = 0;


	// Event
	HANDLE fenceEvent_;


	// dxcCompilerを初期化
	IDxcUtils* dxcUtils_ = nullptr;

	IDxcCompiler3* dxcCompiler_ = nullptr;

	IDxcIncludeHandler* includeHandler_ = nullptr;


	// CompileShader関数
	CompileShaders shaders_;


	// PSOを生成する
	UsePSO usePso_;


	// ビューポート
	D3D12_VIEWPORT viewport_{};


	// シザー矩形
	D3D12_RECT scissorRect_{};


	// 
	ID3D12DescriptorHeap* descriptorHeap_ = nullptr;

	D3D12_DESCRIPTOR_HEAP_DESC DescriptorHeapDesc_{};


	// 深度
	ID3D12Resource* depthStencilResource_ = nullptr;


	// DepthStencilState
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc_{};

	ID3D12DescriptorHeap* dsvDescriptorHeap_ = nullptr;
};