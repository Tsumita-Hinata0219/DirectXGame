#pragma once
#include "Function.h"


class DirectXCommon {

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(int32_t ClientWidth, int32_t ClientHeight, HWND hwnd);

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();

	/// <summary>
	/// 解放処理
	/// </summary>
	void Release();



	// DXGIファクトリーの生成
	void CreateDxgiFactory();

	// D3D12Deviceの生成
	void CreateDevice();

	// コマンドキューを生成する
	void CreateCommandQueue();

	// エラーと警告の抑制
	void DebugErrorInfoQueue();

	// コマンドアロケータを作成
	void CreateCommandAllocator();

	// コマンドリストを生成する
	void CreateCommandList();

	// スワップチェーンを生成する
	void CreateSwapChain();

	// ディスクリプタヒープを生成する
	void CreateRtvDescriptorHeap();

	// SwapChainからResourceを引っ張ってくる
	void CreateSwapChainResources();

	// RTVを作る
	void SettingRTV();

	// 状態を遷移する
	void ChanegResourceState();

	// Fenceを生成する
	void MakeFence();




private:

	int32_t ClientWidth_;
	int32_t ClientHeight_;
	HWND hwnd_;


	// デバッグレイヤー
	ID3D12Debug1* debugController_ = nullptr;


	// DXGIFactory
	IDXGIFactory7* dxgiFactory_ = nullptr;


	// なにこれ↓
	HRESULT hr_;


	// 使用するアダプタ用の変数
	IDXGIAdapter4* useAdapter_ = nullptr;

	ID3D12Device* device_ = nullptr;


	// エラー・警告・即ち停止
	ID3D12InfoQueue* infoQueue_ = nullptr;

	// なにこれ↓
	D3D12_INFO_QUEUE_FILTER filter_{};


	// コマンドキュー
	ID3D12CommandQueue* commandQueue_ = nullptr;

	// コマンドアロケータ
	ID3D12CommandAllocator* commandAllocator_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// バックバッファインデックス
	UINT backBufferIndex_;


	// TransitionBarrierの設定
	D3D12_RESOURCE_BARRIER barrier_{};


	// スワップチェーン
	IDXGISwapChain4* swapChain_ = nullptr;

	// ディスクリプタヒープ
	ID3D12DescriptorHeap* rtvDescriptorHeap_ = nullptr;

	// スワップチェーンリソース
	ID3D12Resource* swapChainResources_[2] = { nullptr };


	// RTV
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_{};

	// RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles_[2] = {};


	// Fence
	ID3D12Fence* fence_ = nullptr;
	uint64_t fenceValue_ = 0;


	// Event
	HANDLE fenceEvent_;
};