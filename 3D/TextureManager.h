#pragma once
#include "DirectXTex.h"
#include "DirectXCommon.h"
#include "Function.h"
#include <cassert>




class TextureManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TextureManager();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~TextureManager();


	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(DirectXCommon* dXCommon);

	
	/// <summary>
	/// Textuerデータを読み込む
	/// </summary>
	void LoadTexture(const std::string& filePath);


	/// <summary>
	/// Textureファイルを開く
	/// </summary>
	DirectX::ScratchImage ImageFileOpen(const std::string& filePath);


	/// <summary>
	/// DirectX12のTExtureResourceを作る
	/// </summary>
	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);


	/// <summary>
	/// TextureResourceにデータを転送する
	/// </summary>
	void UpdateTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImage);


	D3D12_GPU_DESCRIPTOR_HANDLE GetTextureSrvHandleGPU() { return textureSrvHandleGPU_; }


private:

	DirectXCommon* dXCommon_;

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_;


};

