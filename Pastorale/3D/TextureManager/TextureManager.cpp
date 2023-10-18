#include "TextureManager.h"



/// <summary>
/// コンストラク
/// </summary>
TextureManager::TextureManager(){}



/// <summary>
/// デストラクタ
/// </summary>
TextureManager::~TextureManager(){}



void TextureManager::Initialize() {}



/// <summary>
/// Textuerデータを読み込む
/// </summary>
void TextureManager::LoadTexture(const std::string& filePath1, const std::string& filePath2) {

	// Textureを読んで転送する
	// 1枚目のTextureを読んで転送する
	DirectX::ScratchImage mipImages1 = ImageFileOpen(filePath1);
	const DirectX::TexMetadata& metadata1 = mipImages1.GetMetadata();
	ID3D12Resource* textureResource1 = CreateTextureResource(metadata1);
	UpdateTextureData(textureResource1, mipImages1);

	// 2枚目のTextureを読んで転送する
	DirectX::ScratchImage mipImages2 = ImageFileOpen(filePath2);
	const DirectX::TexMetadata& metadata2 = mipImages2.GetMetadata();
	ID3D12Resource* textureResource2 = CreateTextureResource(metadata2);
	UpdateTextureData(textureResource2, mipImages2);


	// metaDataを基にSRVの設定
	// 1枚目
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc1{};
	srvDesc1.Format = metadata1.format;
	srvDesc1.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc1.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc1.Texture2D.MipLevels = UINT(metadata1.mipLevels);

	// 2枚目
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc2{};
	srvDesc2.Format = metadata2.format;
	srvDesc2.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc2.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc2.Texture2D.MipLevels = UINT(metadata2.mipLevels);


	// SRVを作成するDescriptorHeapの場所を決める
	// 1枚目
	textureSrvHandleCPU1_ = DirectXCommon::GetInstance()->GetCPUDescriptorHandle(
		DirectXCommon::GetInstance()->GetSrvDescriptorHeap(), 
		DirectXCommon::GetInstance()->GetDescriptorSize().SRV, 1);
	textureSrvHandleGPU1_ = DirectXCommon::GetInstance()->GetGPUDescriptorHandle(
		DirectXCommon::GetInstance()->GetSrvDescriptorHeap(), 
		DirectXCommon::GetInstance()->GetDescriptorSize().SRV, 1);

	// 2枚目
	textureSrvHandleCPU2_ = DirectXCommon::GetInstance()->GetCPUDescriptorHandle(
		DirectXCommon::GetInstance()->GetSrvDescriptorHeap(), 
		DirectXCommon::GetInstance()->GetDescriptorSize().SRV, 2);
	textureSrvHandleGPU2_ = DirectXCommon::GetInstance()->GetGPUDescriptorHandle(
		DirectXCommon::GetInstance()->GetSrvDescriptorHeap(), 
		DirectXCommon::GetInstance()->GetDescriptorSize().SRV, 2);


	// 先頭はImGuiが使っているのでその次を使う
	// 1枚目
	textureSrvHandleCPU1_.ptr += DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	textureSrvHandleGPU1_.ptr += DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	
	// 2枚目
	textureSrvHandleCPU2_.ptr += DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	textureSrvHandleGPU2_.ptr += DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// SRVの生成
	DirectXCommon::GetInstance()->GetDevice()->CreateShaderResourceView(textureResource1, &srvDesc1, textureSrvHandleCPU1_);
	DirectXCommon::GetInstance()->GetDevice()->CreateShaderResourceView(textureResource2, &srvDesc2, textureSrvHandleCPU2_);
};



/// <summary>
/// Textureファイルを開く
/// </summary>
DirectX::ScratchImage TextureManager::ImageFileOpen(const std::string& filePath) {

	// テクスチャファイルを読み込んでプログラムで扱えるようにする
	// Textureデータを読み込む
	DirectX::ScratchImage image{};
	std::wstring filePathw = ConverString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathw.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));

	// ミニマップの作成
	DirectX::ScratchImage mipImages{};
	hr = DirectX::GenerateMipMaps(
		image.GetImages(), image.GetImageCount(), image.GetMetadata(), 
		DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr));

	// ミニマップ付きのデータを探す	
	return mipImages;
}



/// <summary>
/// DirectX12のTExtureResourceを作る
/// </summary>
ID3D12Resource* TextureManager::CreateTextureResource(const DirectX::TexMetadata& metadata) {

	// 1.metadataを基にResourceの設定
	// metadataを基にResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(metadata.width);								// Textureの幅
	resourceDesc.Height = UINT(metadata.height);							// Textureの高さ
	resourceDesc.MipLevels = UINT(metadata.mipLevels);						// mipmapの数
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);			// 奥行き or 配列Textureの配列数
	resourceDesc.Format = metadata.format;									// TextureのFormat
	resourceDesc.SampleDesc.Count = 1;										// サンプリングカウント。1固定
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension); // Textureの次元数。普段使っているのは2次元

	// 2. 利用するHeapの設定
	// 利用するHeapの設定。非常に特殊な運用 ※02_04exで一般的なケース版がある
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM; // 細かい設定を行う
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK; // WriteBackポリシーでCPUアクセス可能
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;	// プロセッサの近くに配置

	// 3. Resourceを作る
	// Resourceを生成する
	ID3D12Resource* resource;
	HRESULT hr = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProperties,				   // Heapの設定
		D3D12_HEAP_FLAG_NONE,			   // Heapの特殊な設定。特になし
		&resourceDesc,					   // Resourceの設定
		D3D12_RESOURCE_STATE_GENERIC_READ, // 初回のResourceState。Textureは基本読むだけ
		nullptr,						   // Clear最適地。使わないのでnullptr
		IID_PPV_ARGS(&resource));		   // 作成するResourceポインタへのポインタ
	assert(SUCCEEDED(hr));

	return resource;
}



/// <summary>
/// TextureResourceにデータを転送する
/// </summary>
void TextureManager::UpdateTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImage) {

	// Meta情報を取得
	const DirectX::TexMetadata& metadata = mipImage.GetMetadata();

	// 全MipMapについて
	for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel) {
		
		//MipMapLevelを指定して各Imageを取得
		const DirectX::Image* img = mipImage.GetImage(mipLevel, 0, 0);

		// Textureに転送
		HRESULT hr_ = texture->WriteToSubresource(
			UINT(mipLevel),
			nullptr,			  // 全領域へコピー
			img->pixels,		  // 元データアドレス
			UINT(img->rowPitch),  // 1ラインサイズ
			UINT(img->slicePitch) // 1枚サイズ
		);
		assert(SUCCEEDED(hr_));
	}
}




