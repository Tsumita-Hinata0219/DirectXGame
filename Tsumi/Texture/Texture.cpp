#include "Texture.h"



static uint32_t texIndex;
static DescriptorSize descriptorSize;

// 初期化処理
void Texture::Initialize() {

	descriptorSize.SRV = DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	descriptorSize.RTV = DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	descriptorSize.DSV = DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	texIndex = 0;
}


// 解放処理
void Texture::Finalize() {


}


// テクスチャデータを読み込む
uint32_t Texture::LoadTexture(const std::string& filePath) {


}