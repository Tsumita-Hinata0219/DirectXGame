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
	DirectX::ScratchImage LoadTexture(const std::string& filePath);


	/// <summary>
	/// DirectX12のTExtureResourceを作る
	/// </summary>
	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);


	/// <summary>
	/// TextureResourceにデータを転送する
	/// </summary>
	void UpdateTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImage);





private:


};

