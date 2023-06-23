#include "Model.h"



Model::~Model() {

	vertexResource_->Release();
	commandList_->Release();
	device_->Release();
}



// 初期化処理
void Model::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {

	// デバイスとコマンドリストを設定
	SetDirectXDevice(device);
	SetDirectXCommandList(commandList);
}



// 頂点リソース用のヒープ設定
void Model::CreateVertexResource() {

	// 頂点リソース用のヒープ設定
	uploadHeapProperties_.Type = D3D12_HEAP_TYPE_UPLOAD; // UploadHeapを使う

	// バッファリソース。テクスチャの場合はまた別の設定をする
	vertexResourceDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;

	// リソースのサイズ。今回はVector4を3頂点文
	vertexResourceDesc_.Width = sizeof(Vector4) * 3;

	// バッファの場合はこれらは1にする決まり
	vertexResourceDesc_.Height = 1;
	vertexResourceDesc_.DepthOrArraySize = 1;
	vertexResourceDesc_.MipLevels = 1;
	vertexResourceDesc_.SampleDesc.Count = 1;

	// バッファの場合はこれにする決まり
	vertexResourceDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 実際に頂点リソースを作る
	hr_ = device_->CreateCommittedResource(&uploadHeapProperties_, D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc_, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&vertexResource_));
	assert(SUCCEEDED(hr_));
}



// 頂点バッファビューを作成する
void Model::MakeVertexBufferView() {

	// 頂点バッファビューを作成する
	// リソースの先頭アドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();

	// 使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView_.SizeInBytes = sizeof(Vector4) * 3;

	// 1頂点あたりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(Vector4);

	// 書き込むためのアドレスを取得
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));
}



// 三角形の描画
void Model::DrawTriangle(Vector4 bottomLeft, Vector4 top, Vector4 bottomRight) {

	// 頂点データの作成とビュー
	CreateVertexResource();
	MakeVertexBufferView();

	vertexData_[0] = bottomLeft;   // 左下
	vertexData_[1] = top;          // 上
	vertexData_[2] = bottomRight; // 右下


	// いざ描画！！！！！
	// VBVを設定
	commandList_->IASetVertexBuffers(0, 1, &vertexBufferView_);

	// 形状を設定
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 描画！(DrawCall / ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	commandList_->DrawInstanced(3, 1, 0, 0);
}



// アクセッサ
void Model::SetDirectXDevice(ID3D12Device* device) {
	device_ = device;
}
void Model::SetDirectXCommandList(ID3D12GraphicsCommandList* commandList) {
	commandList_ = commandList;
}
