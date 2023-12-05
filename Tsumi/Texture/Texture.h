#pragma once


#include "DirectXTex.h"

#include "DirectXCommon.h"
#include "Function.h"
#include "Struct.h"

#include <cassert>



struct TextureDescriptorHandle {
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle_CPU;
	D3D12_GPU_DESCRIPTOR_HANDLE srvHandle_GPU;
	ComPtr<ID3D12Resource> Resource;
};
struct DescriptorSize {
	uint32_t SRV;
	uint32_t RTV;
	uint32_t DSV;
};


/* Textureクラス */
class Texture {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Texture() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Texture() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 解放処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// Textuerデータを読み込む
	/// </summary>
	uint32_t LoadTexture(const std::string& filePath);

	/// <summary>
	/// DescriptorTableを設定する
	/// </summary>
	void SetGraphicsRootDescriptorTable(UINT rootPatramerterIndex, uint32_t texhandle);

	/// <summary>
	/// DescriptorHandleを取得する
	/// </summary>
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);


private: // メンバ関数

	/// <summary>
	/// Textureファイルを開く
	/// </summary>
	DirectX::ScratchImage CreateMipImage(const std::string& filePath);

	/// <summary>
	/// DirectX12のTExtureResourceを作る
	/// </summary>
	ComPtr<ID3D12Resource> CreateTextureResource(const DirectX::TexMetadata& metadata);

	/// <summary>
	/// TextureResourceにデータを転送する
	/// </summary>
	void UpdateTextureData(const DirectX::ScratchImage& mipImage);

	/// <summary>
	/// metadataを基にResourceの設定
	/// </summary>
	D3D12_RESOURCE_DESC SettingResource(const DirectX::TexMetadata& metadata);

	/// <summary>
	/// 利用するHeapの設定
	/// </summary>
	D3D12_HEAP_PROPERTIES SettingUseHeap();

	/// <summary>
	/// Resourceを生成する
	/// </summary>
	ComPtr<ID3D12Resource> CreateResource(D3D12_RESOURCE_DESC resourceDesc, D3D12_HEAP_PROPERTIES heapProperties);


private: // メンバ変数

	// ロードできるテクスチャの最大数
	const static uint32_t TexLoadMax = 128;

	// デスクリプターヒープの場所指定のインデックス
	uint32_t LoadTextureIndex_ = 0;

	// テクスチャの情報持っているやつ
	TextureDescriptorHandle tex_[TexLoadMax];
};
