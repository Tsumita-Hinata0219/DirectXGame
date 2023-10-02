#include "Sphere.h"



/// <summary>
/// コンストラクタ
/// </summary>
Sphere::Sphere() {}



/// <summary>
/// デストラクタ
/// </summary>
Sphere::~Sphere(){}



/// <summary>
/// 初期化処理
/// </summary>
void Sphere::Initialize(const int32_t Width, const int32_t Height, DirectXCommon* dXCommon, WorldTransform transform) {

	ClientWidth_ = 0;
	ClientHeight_ = 0;

	dXCommon_ = dXCommon;
}



/// <summary>
/// 更新処理
/// </summary>
void Sphere::Update(SphereData sphere, WorldTransform transform, Matrix4x4& viewMatrix) {

	SetVertex(sphere, transform, viewMatrix);

}



/// <summary>
/// 描画処理
/// </summary>
void Sphere::Draw(TextureManager* textureManager) {

	/// コマンドを積む
	// 頂点の設定 (VBVを設定)
	dXCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSphere_);

	//形状を設定
	dXCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 色用のCBufferの場所を設定
	dXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResourceSphere_->GetGPUVirtualAddress());
	
	// wvp用のCBufferの場所を設定
	dXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSphere_->GetGPUVirtualAddress());

	// DescriptorTableを設定する
	dXCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureManager->GetTextureSrvHandleGPU());

	// 描画！ (DrawCall / ドローコール)
	dXCommon_->GetCommandList()->DrawInstanced(subdivision_ * subdivision_ * 6, 1, 0, 0);
}



/// <summary>
/// 頂点データを設定する
/// </summary>
void Sphere::SetVertex(SphereData sphere, WorldTransform transform, Matrix4x4& viewMatrix) {

	// vertexResourceを生成する
	vertexResourceSphere_ = CreateBufferResource(sizeof(VertexData) * subdivision_ * subdivision_ * 6);
	// Material用のResourceを作る
	CreateMaterialResource();
	// vertexBufferViewを生成する
	vertexBufferViewSphere_ = CreateBufferView(vertexResourceSphere_);
	// TransformationMatrix用のResourceを作る
	CreateTransformationMatrixResource();
	// Sphere用のWorldViewProjectionMatrixを作る
	CreateWVPMatrix(sphere, transform, viewMatrix);


	// 色の設定
	*materialDate_ = { 1.0f, 1.0f, 1.0f, 1.0f };


	// 書き込むためのアドレスを用意
	vertexResourceSphere_->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSphere_));
	materialResourceSphere_->Map(0, nullptr, reinterpret_cast<void**>(&materialDate_));


	// 経度分割の1つ分の角度
	const float lonEvery = float(std::numbers::pi) * 2.0f / float(subdivision_);
	// 緯度分割１つ分の角度
	const float latEvery = float(std::numbers::pi) / float(subdivision_);


	// 緯度方向に分割
	for (int32_t latIndex = 0; latIndex < subdivision_; ++latIndex) {

		float lat = -float(std::numbers::pi) / 2.0f + latEvery * latIndex;
		float uvLength = 1.0f / subdivision_;

		// 経度方向に分割
		for (int32_t lonIndex = 0; lonIndex < subdivision_; ++lonIndex) {

			uint32_t start_ = (latIndex * subdivision_ + lonIndex) * 6;
			float lon = lonIndex * lonEvery;
			float u = float(lonIndex) / float(subdivision_);
			float v = 1.0f - float(latIndex) / float(subdivision_);


#pragma region Trinagle１枚目

			// 点A(左下)
			vertexDataSphere_[start_].position.x = sphere.radius * (cos(lat) * cos(lon));
			vertexDataSphere_[start_].position.y = sphere.radius * (sin(lat));
			vertexDataSphere_[start_].position.z = sphere.radius * (cos(lat) * sin(lon));
			vertexDataSphere_[start_].position.w = 1.0f;
			vertexDataSphere_[start_].texCoord = { u, v + uvLength };

			// 点B(左上)
			vertexDataSphere_[start_ + 1].position.x = sphere.radius * (cos(lat + latEvery)) * cos(lon);
			vertexDataSphere_[start_ + 1].position.y = sphere.radius * (sin(lat + latEvery));
			vertexDataSphere_[start_ + 1].position.z = sphere.radius * (cos(lat + latEvery)) * sin(lon);
			vertexDataSphere_[start_ + 1].position.w = 1.0f;
			vertexDataSphere_[start_ + 1].texCoord = { u, v };

			// 点C(右下)
			vertexDataSphere_[start_ + 2].position.x = sphere.radius * (cos(lat) * cos(lon + lonEvery));
			vertexDataSphere_[start_ + 2].position.y = sphere.radius * (sin(lat));
			vertexDataSphere_[start_ + 2].position.z = sphere.radius * (cos(lat) * sin(lon + lonEvery));
			vertexDataSphere_[start_ + 2].position.w = 1.0f;
			vertexDataSphere_[start_ + 2].texCoord = { u + uvLength, v + uvLength };

#pragma endregion

#pragma region Triangle２枚目

			// 点D(右上)
			vertexDataSphere_[start_ + 3].position.x = sphere.radius * (cos(lat + latEvery) * cos(lon + lonEvery));
			vertexDataSphere_[start_ + 3].position.y = sphere.radius * (sin(lat + latEvery));
			vertexDataSphere_[start_ + 3].position.z = sphere.radius * (cos(lat + latEvery) * sin(lon + lonEvery));
			vertexDataSphere_[start_ + 3].position.w = 1.0f;
			vertexDataSphere_[start_ + 3].texCoord = { u + uvLength, v };

			// 点C(右下)
			vertexDataSphere_[start_ + 4].position.x = sphere.radius * (cos(lat) * cos(lon + lonEvery));
			vertexDataSphere_[start_ + 4].position.y = sphere.radius * (sin(lat));
			vertexDataSphere_[start_ + 4].position.z = sphere.radius * (cos(lat) * sin(lon + lonEvery));
			vertexDataSphere_[start_ + 4].position.w = 1.0f;
			vertexDataSphere_[start_ + 4].texCoord = { u + uvLength, v + uvLength };

			// 点B(左上)
			vertexDataSphere_[start_ + 5].position.x = sphere.radius * (cos(lat + latEvery) * cos(lon));
			vertexDataSphere_[start_ + 5].position.y = sphere.radius * (sin(lat + latEvery));
			vertexDataSphere_[start_ + 5].position.z = sphere.radius * (cos(lat + latEvery) * sin(lon));
			vertexDataSphere_[start_ + 5].position.w = 1.0f;
			vertexDataSphere_[start_ + 5].texCoord = { u, v };

#pragma endregion

		}
	}

}



/// <summary>
/// 頂点リソース用のヒープ設定
/// </summary>
ID3D12Resource* Sphere::CreateBufferResource(size_t sizeInBytes) {

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
	hr_ = dXCommon_->GetDevice()->CreateCommittedResource(&uploadHeapProperties_, D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc_, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&resultResource));
	assert(SUCCEEDED(hr_));


	return resultResource;
}



/// <summary>
/// 頂点バッファビューを作成する
/// </summary>
D3D12_VERTEX_BUFFER_VIEW Sphere::CreateBufferView(ID3D12Resource* resource) {

	D3D12_VERTEX_BUFFER_VIEW resultBufferView{};


	// 頂点バッファビューを作成する
	// リソースの先頭アドレスから使う
	resultBufferView.BufferLocation = resource->GetGPUVirtualAddress();

	// 使用するリソースのサイズは頂点3つ分のサイズ
	resultBufferView.SizeInBytes = sizeof(VertexData) * 6 * subdivision_ * subdivision_;

	// 1頂点あたりのサイズ
	resultBufferView.StrideInBytes = sizeof(VertexData);


	return resultBufferView;
}



/// <summary>
/// TransformationMatrix用のResoureを作る
/// </summary>
void Sphere::CreateTransformationMatrixResource() {
	
	// WVP用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	transformationMatrixResourceSphere_ = CreateBufferResource(sizeof(Matrix4x4));

	// 書き込むためのアドレスを取得
	transformationMatrixResourceSphere_->Map(0, nullptr, reinterpret_cast<void**>(&transfomationMatrixDataSphere_));

}



/// <summary>
/// Sphere用のWorldViewProjectonMatrixを作る
/// </summary>
void Sphere::CreateWVPMatrix(SphereData sphere, WorldTransform transform, Matrix4x4& viewMatrix) {

	// Sprite用のWorldViewProjectonMatrixを作る
	worldMatrixSphere = MakeAffineMatrix(transform.scale, transform.rotate, Add(transform.translate, sphere.center));


	*transfomationMatrixDataSphere_ = Multiply(worldMatrixSphere, viewMatrix);

}



/// <summary>
/// Material用のResourceを作る
/// </summary>
void Sphere::CreateMaterialResource() {

	// マテリアル用のリソースを作る。今回はcolor1つ分サイズを用意する
	materialResourceSphere_ = CreateBufferResource(sizeof(Vector4));

	// マテリアルにデータを書き込む
	// 書き込むためのアドレスを取得
	materialResourceSphere_->Map(0, nullptr, reinterpret_cast<void**>(&materialDate_));
}



/// <summary>
/// 色の変換
/// </summary>
Vector4 Sphere::FloatColor(unsigned int color) {

	Vector4 colorf = {
		((color >> 24) & 0xff) / 255.0f, // R
		((color >> 16) & 0xff) / 255.0f, // G
		((color >> 8) & 0xff) / 255.0f,  // B
		((color >> 0) & 0xff) / 255.0f   // A
	};

	return colorf;
}