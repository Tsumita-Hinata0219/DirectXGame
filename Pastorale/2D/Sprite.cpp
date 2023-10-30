#include "Sprite.h"



/// <summary>
/// コンストラクタ
/// </summary>
Sprite::Sprite() {}



/// <summary>
/// デストラクタ
/// </summary>
Sprite::~Sprite() {}



/// <summary>
/// 初期化処理
/// </summary>
void Sprite::Initialize() {}



/// <summary>
/// 更新処理
/// </summary>
void Sprite::Update(WorldTransform transform, SpriteData vertex) {

	//transform.translate.z = 0.0f;
	SetVertex(transform, vertex);
}



/// <summary>
/// 描画処理
/// </summary>
void Sprite::DrawSprite(uint32_t texhandle) {

	// 頂点の設定
	DirectXCommon::GetInstance()->GetCommands().List->IASetVertexBuffers(0, 1, &vertexBufferViewSprite_); // VBVを設定

	// 形状を設定
	DirectXCommon::GetInstance()->GetCommands().List->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 色用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());

	// wvp用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSprite_->GetGPUVirtualAddress());

	// DescriptorTableを設定する
	if (!texhandle == 0) {
		TextureManager::GetInstance()->SetGraphicsRootDescriptorTable(2, texhandle);
	}

	// 描画！(DrawCall/ドローコール)
	DirectXCommon::GetInstance()->GetCommands().List->DrawInstanced(6, 1, 0, 0);
}



/// <summary>
/// 頂点データを設定する
/// </summary>
void Sprite::SetVertex(WorldTransform transform, SpriteData vertex) {

	// Sprite用の頂点リソースを作る
	vertexResourceSprite_ = CreateBufferResource(DirectXCommon::GetInstance()->GetDevice(), sizeof(VertexData) * 6);
	// Material用のResourceを作る
	CreateMaterialResource();
	// TransformationMatrix用のResourceを作る
	CreateTransformationMatrix();
	// 頂点バッファビューを作成する
	vertexBufferViewSprite_ = CreateBufferView(vertexResourceSprite_, sizeof(VertexData) * 6);

	// Sprite用のWorldViewProjectonMatrixを作る
	CreateWVPMatrix(transform);


	// 色を決める
	*materialDate_ = FloatColor(0xffffffff);


	// 書き込むためのアドレスを取得
	vertexResourceSprite_->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSprite_));
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialDate_));


	/// 三角形
	// １枚目
	vertexDataSprite_[0].position = vertex.bottomLeft;  // 左下
	vertexDataSprite_[1].position = vertex.topLeft;	    // 左上
	vertexDataSprite_[2].position = vertex.bottomRight; // 右下
	// ２枚目
	vertexDataSprite_[3].position = vertex.topLeft;	    // 左上
	vertexDataSprite_[4].position = vertex.topRight;	// 右上
	vertexDataSprite_[5].position = vertex.bottomRight; // 右下

	/// テクスチャ
	// １枚目
	vertexDataSprite_[0].texCoord = { 0.0f, 1.0f };
	vertexDataSprite_[1].texCoord = { 0.0f, 0.0f };
	vertexDataSprite_[2].texCoord = { 1.0f, 1.0f };
	// ２枚目
	vertexDataSprite_[3].texCoord = { 0.0f, 0.0f };
	vertexDataSprite_[4].texCoord = { 1.0f, 0.0f };
	vertexDataSprite_[5].texCoord = { 1.0f, 1.0f };

}



/// <summary>
/// 頂点リソース用のヒープ設定
/// </summary>
ID3D12Resource* Sprite::CreateBufferResource(ID3D12Device* device, size_t sizeInBytes) {

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



/// <summary>
/// 頂点バッファビューを作成する
/// </summary>
D3D12_VERTEX_BUFFER_VIEW Sprite::CreateBufferView(ID3D12Resource* resource, size_t sizeInBytes) {

	D3D12_VERTEX_BUFFER_VIEW resultBufferView{};


	// 頂点バッファビューを作成する
	// リソースの先頭アドレスから使う
	resultBufferView.BufferLocation = resource->GetGPUVirtualAddress();

	// 使用するリソースのサイズは頂点3つ分のサイズ
	resultBufferView.SizeInBytes = UINT(sizeInBytes);

	// 1頂点あたりのサイズ
	resultBufferView.StrideInBytes = UINT(sizeInBytes / 6);


	return resultBufferView;
}



/// <summary>
/// TransformationMatrix用のResourceを作る
/// </summary>
void Sprite::CreateTransformationMatrix() {

	// Sprite用のTransfomationMatrix用のリソースを作る。Matrix4x4 １つ分のサイズを用意する
	transformationMatrixResourceSprite_ = CreateBufferResource(DirectXCommon::GetInstance()->GetDevice(), sizeof(Matrix4x4));

	/// データを書き込む
	// 書き込むためのアドレスを取得
	transformationMatrixResourceSprite_->Map(0, nullptr, reinterpret_cast<void**>(&transfomationMatrixDataSprite_));
	// 単位行列を書き込んでおく
	*transfomationMatrixDataSprite_ = MakeIdentity4x4();
}



/// <summary>
/// Sprite用のWorldViewProjectonMatrixを作る
/// </summary>
void Sprite::CreateWVPMatrix(WorldTransform transform) {

	// Sprite用のWorldViewProjectonMatrixを作る
	worldMatrixSprite = MakeAffineMatrix(transform.scale_, transform.rotate_, transform.translation_);
	viewMatrixSprite = MakeIdentity4x4();
	projectionMatrixSprite =
		MakeOrthographicMatrix(0.0f, 0.0f, float(WinApp::GetInstance()->GetClientWidth()), float(WinApp::GetInstance()->GetCliendHeight()), 0.0f, 100.0f);
	worldProjectionMatrixSprite =
		Multiply(worldMatrixSprite, Multiply(viewMatrixSprite, projectionMatrixSprite));

	*transfomationMatrixDataSprite_ = worldProjectionMatrixSprite;
}



/// <summary>
/// Material用のResourceを作る
/// </summary>
void Sprite::CreateMaterialResource() {

	// マテリアル用のリソースを作る。今回はcolor1つ分サイズを用意する
	materialResource_ = CreateBufferResource(DirectXCommon::GetInstance()->GetDevice(), sizeof(Vector4));

	// マテリアルにデータを書き込む
	// 書き込むためのアドレスを取得
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialDate_));
}



/// <summary>
/// 色の変換
/// </summary>
Vector4 Sprite::FloatColor(unsigned int color) {

	Vector4 colorf = {
		((color >> 24) & 0xff) / 255.0f, // R
		((color >> 16) & 0xff) / 255.0f, // G
		((color >> 8) & 0xff) / 255.0f,  // B
		((color >> 0) & 0xff) / 255.0f   // A
	};

	return colorf;
}