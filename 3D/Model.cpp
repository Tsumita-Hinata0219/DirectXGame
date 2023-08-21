#include "Model.h"



// 解放処理
Model::~Model() {

	vertexResource_->Release();
}



// 初期化処理
void Model::Initialize(DirectXCommon* dXCommon) {

	dXCommon_ = dXCommon;
}



// 更新処理
void Model::Update(Triangle element, Transform& transform, Matrix4x4& ViewMatrix) {

	SetVertex(element, transform, ViewMatrix);
}



// 頂点リソース用のヒープ設定
ID3D12Resource* Model::CreateBufferResource(ID3D12Device* device, size_t sizeInBytes) {

	ID3D12Resource* resultResource;


	// 頂点リソース用のヒープ設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties_{};

	D3D12_RESOURCE_DESC vertexResourceDesc_{};

	// 頂点リソース用のヒープ設定
	uploadHeapProperties_.Type = D3D12_HEAP_TYPE_UPLOAD; // UploadHeapを使う

	// バッファリソース。テクスチャの場合はまた別の設定をする
	vertexResourceDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;

	// リソースのサイズ。今回はVector4を3頂点文
	vertexResourceDesc_.Width = sizeInBytes;

	// バッファの場合はこれらは1にする決まり
	vertexResourceDesc_.Height = 1;
	vertexResourceDesc_.DepthOrArraySize = 1;
	vertexResourceDesc_.MipLevels = 1;
	vertexResourceDesc_.SampleDesc.Count = 1;

	// バッファの場合はこれにする決まり
	vertexResourceDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 実際に頂点リソースを作る
	HRESULT hr_;
	hr_ = device->CreateCommittedResource(&uploadHeapProperties_, D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc_, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&resultResource));
	assert(SUCCEEDED(hr_));


	return resultResource;
}



// 頂点バッファビューを作成する
D3D12_VERTEX_BUFFER_VIEW Model::MakeBufferView(ID3D12Resource* resource, size_t sizeInBytes) {

	D3D12_VERTEX_BUFFER_VIEW resultBufferView{};


	// 頂点バッファビューを作成する
	// リソースの先頭アドレスから使う
	resultBufferView.BufferLocation = resource->GetGPUVirtualAddress();

	// 使用するリソースのサイズは頂点3つ分のサイズ
	resultBufferView.SizeInBytes = UINT(sizeInBytes);

	// 1頂点あたりのサイズ
	resultBufferView.StrideInBytes = UINT(sizeInBytes / 3);


	return resultBufferView;
}



// Material用のResourceを作る
void Model::MakeMaterialResource() {

	// マテリアル用のリソースを作る。今回はcolor1つ分サイズを用意する
	materialResource_ = CreateBufferResource(dXCommon_->GetDevice(), sizeof(Vector4));

	// マテリアルにデータを書き込む
	// 書き込むためのアドレスを取得
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialDate_));
}



// TransformationMatrix用のResoureを作る
void Model::MakeTransformationMatResource() {

	// WVP用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	wvpResource_ = CreateBufferResource(dXCommon_->GetDevice(), sizeof(Matrix4x4));

	// データを書き込む
	// 書き込むためのアドレスを取得
	wvpResource_->Map(0, nullptr, reinterpret_cast<void**>(&wvpData_));

}



void Model::SetVertex(Triangle element, Transform& transform, Matrix4x4& ViewMatrix) {

	//行列を作る
	worldMatrix_ = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);


	// VertexResourceを生成する
	vertexResource_ = CreateBufferResource(dXCommon_->GetDevice(), sizeof(VertexData) * 3);
	// Material用のResourceを作る
	MakeMaterialResource();
	// TransformationMatrix用のResourceを作る
	MakeTransformationMatResource();
	// vertexBufferViewを作成する
	vertexBufferView_ = MakeBufferView(vertexResource_, sizeof(VertexData) * 3);
	

	// 引数の色コードをVector4に変換してmaterialDate_に送る
	*materialDate_ = element.color;
	// 単位行列を書き込んでおく
	*wvpData_ = Multiply(worldMatrix_, ViewMatrix);


	// 書き込むためのアドレスを取得
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialDate_));


	// Triangle
	vertexData_[0].position = element.bottomLeft;   // 左下
	vertexData_[1].position = element.top;          // 上
	vertexData_[2].position = element.bottomRight; // 右下

	// Texture
	vertexData_[0].texCoord = { 0.0f, 1.0f };  // 左下
	vertexData_[1].texCoord = { 0.5f, 0.0f };  // 上
	vertexData_[2].texCoord = { 1.0f, 1.0f }; // 右下
}



// 三角形の描画
void Model::Draw() {

	///// いざ描画！！！！！
	// VBVを設定
	dXCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);

	// 形状を設定
	dXCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// CBVを設定する
	dXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());

	// wvp用のCBufferの場所を設定
	dXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource_->GetGPUVirtualAddress());

	// 描画！(DrawCall / ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	dXCommon_->GetCommandList()->DrawInstanced(3, 1, 0, 0);
}



// 色(RGBA)を決める
Vector4 Model::FloatColor(unsigned int color) {

	Vector4 colorf = {
		((color >> 24) & 0xff) / 255.0f, // R
		((color >> 16) & 0xff) / 255.0f, // G
		((color >> 8) & 0xff) / 255.0f,  // B
		((color >> 0) & 0xff) / 255.0f   // A
	};

	return colorf;
}


