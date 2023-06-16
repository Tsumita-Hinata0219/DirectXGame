#include "Triangle.h"


/// <summary>
/// 初期化処理
/// </summary>
void Triangle::Initialize(DirectXCommon* directX) {

	// DirectX
	directX_ = directX;

	/* ----- 頂点データの作成とビュー ----- */

	CreateVertexResource();
	MakeVertexBufferView();
}


/// <summary>
/// 描画処理
/// </summary>
void Triangle::Draw() {

	// 左下
	vertexData_[0] = { -0.5f, -0.5f, 0.0f, 1.0f };

	// 上
	vertexData_[1] = { 0.0f, 0.5f, 0.0f, 1.0f };

	// 右下
	vertexData_[2] = { 0.5f, -0.5f, 0.0f, 1.0f };


	// VBVを設定
	directX_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);
	// 形状を設定
	directX_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// 描画！(DrawCall / ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	directX_->GetCommandList()->DrawInstanced(3, 1, 0, 0);
}


/// <summary>
/// 解放処理
/// </summary>
void Triangle::Relese() {


}



/* ----- 頂点リソース用のヒープ設定 ----- */

void Triangle::CreateVertexResource() {

	// 頂点リソース用のヒープ設定
	uploadHeapProperties_.Type = D3D12_HEAP_TYPE_UPLOAD; // UploadHeapを使う
	// バッファリソース。テクスチャの場合はまた別の設定をする
	vertexResourceDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertexResourceDesc_.Width = sizeof(Vector4) * 3; // リソースのサイズ。今回はVector4を3頂点文
	// バッファの場合はこれらは1にする決まり
	vertexResourceDesc_.Height = 1;
	vertexResourceDesc_.DepthOrArraySize = 1;
	vertexResourceDesc_.MipLevels = 1;
	vertexResourceDesc_.SampleDesc.Count = 1;
	// バッファの場合はこれにする決まり
	vertexResourceDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	// 実際に頂点リソースを作る
	hr_ = directX_->GetDevice()->CreateCommittedResource(&uploadHeapProperties_, D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc_, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&vertexResource_));
	assert(SUCCEEDED(hr_));
}


/* ----- 頂点リソース用のヒープ設定 ----- */

void Triangle::MakeVertexBufferView() {

	// 頂点バッファビューを作成する
	// リソースの先頭アドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView_.SizeInBytes = sizeof(Vector4) * 3;
	// 1頂点あたりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(Vector4);
}

