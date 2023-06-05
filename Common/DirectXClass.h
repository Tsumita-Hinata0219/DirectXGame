#pragma once
#include "Function.h"
#include "WindowsClass.h"


class DirectXClass
{
public:
	/// <summary>
	/// インストラクタ
	/// </summary>
	DirectXClass();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~DirectXClass();


	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(const int32_t kClientWidth, const int32_t kClientHeight);




	// DXGIファクトリーの生成
	void CreateDxgiFactory();

	// D3D12Deviceの生成
	void CreateDevice();

	// コマンドを生成する
	void CreateCommands();

	// スワップチェーンを生成する
	void CreateSwapChain(const int32_t kClientWidth, const int32_t kClientHeight, HWND hwnd_);

	// ディスクリプタヒープを生成する
	void CreateRtvDescriptorHeap();

	// SwapChainからResourceを引っ張ってくる
	void CreateSwapChainResources();

	// RTVを作る
	void SettingRTV();

	//コマンドを詰め込んで確定する
	void LoadConfirmCommand();
	
	
	// コマンドをキックする
	void KickCommands();


public:

	WindowsClass* windows_ = nullptr;

	// デバッグレイヤー
	ID3D12Debug1* debugController_ = nullptr;

	// DXGIFactory
	IDXGIFactory7* dxgiFactory_ = nullptr;

	HRESULT hr_;

	// 使用するアダプタ用の変数
	IDXGIAdapter4* useAdapter_ = nullptr;

	ID3D12Device* device_ = nullptr;

	// コマンドキュー
	ID3D12CommandQueue* commandQueue_ = nullptr;

	// コマンドアロケータ
	ID3D12CommandAllocator* commandAllocator_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

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

};

