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
	void Initialize();

	
	/// <summary>
	/// Textuerデータを読み込む
	/// </summary>
	void LoadTexture(const std::string& filePath1, const std::string& filePath2);


	/// <summary>
	/// Textureファイルを開く
	/// </summary>
	DirectX::ScratchImage ImageFileOpen(const std::string& filePath);


	/// <summary>
	/// DirectX12のTExtureResourceを作る
	/// </summary>
	ID3D12Resource* CreateTextureResource(const DirectX::TexMetadata& metadata);


	/// <summary>
	/// TextureResourceにデータを転送する
	/// </summary>
	void UpdateTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImage);


	/// <summary>
	/// アクセッサ
	/// </summary>
	D3D12_GPU_DESCRIPTOR_HANDLE GetTextureSrvHandleGPU1() { return textureSrvHandleGPU1_; }
	D3D12_GPU_DESCRIPTOR_HANDLE GetTextureSrvHandleGPU2() { return textureSrvHandleGPU2_; }


private:

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU1_;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU1_;

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU2_;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU2_;
};

