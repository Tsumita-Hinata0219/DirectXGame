#include "Sphere.h"



/// <summary>
/// コンストラクタ
/// </summary>
Sphere::Sphere() {}



/// <summary>
/// デストラクタ
/// </summary>
Sphere::~Sphere() {}



/// <summary>
/// 初期化処理
/// </summary>
void Sphere::Initialize() {

	// 初期設定中心と半径
	sphereElemnt_ = {
		{0.0f, 0.0f, 0.0f},
		{10.0f},
	};

	// 頂点の設定
	SetVertex();

	// 何も設定しなかったらuvCheckerになる
	useTexture_ = TextureManager::LoadTexture("Resources/uvChecker.png");
}



/// <summary>
/// 更新処理
/// </summary>
void Sphere::Update() {

	ImGui::Begin("directionalLight");
	ImGui::DragFloat4("color", &directionalLightData_.color.x, 0.01f);
	ImGui::DragFloat3("direction", &directionalLightData_.direction.x, 0.01f);

	ImGui::End();
}



/// <summary>
/// 描画処理
/// </summary>
void Sphere::Draw(WorldTransform transform, Matrix4x4& viewMatrix) {

	// Sphere用のWorldViewProjectionMatrixを作る
	CreateWVPMatrix(transform, viewMatrix);

	// RootSignatureを設定。
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootSignature(LightGraphicPipeline::GetInstance()->GetPsoProperty().rootSignature);
	// PSOを設定
	DirectXCommon::GetInstance()->GetCommands().List->SetPipelineState(LightGraphicPipeline::GetInstance()->GetPsoProperty().graphicsPipelineState);

	/// コマンドを積む
	// 頂点の設定 (VBVを設定)
	DirectXCommon::GetInstance()->GetCommands().List->IASetVertexBuffers(0, 1, &vertexBufferViewSphere_);

	//形状を設定
	DirectXCommon::GetInstance()->GetCommands().List->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 色用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootConstantBufferView(0, materialResourceSphere_->GetGPUVirtualAddress());
	
	// wvp用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSphere_->GetGPUVirtualAddress());

	// DescriptorTableを設定する
	if (!useTexture_ == 0) {
		TextureManager::GetInstance()->SetGraphicsRootDescriptorTable(2, useTexture_);
	}

	// 光用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootConstantBufferView(3, directionalLightingResource_->GetGPUVirtualAddress());

	// 描画！ (DrawCall / ドローコール)
	DirectXCommon::GetInstance()->GetCommands().List->DrawInstanced(subdivision_ * subdivision_ * 6, 1, 0, 0);
}



/// <summary>
/// 頂点データを設定する
/// </summary>
void Sphere::SetVertex() {

	// 色の設定
	materialDataSphere_.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	// Lightingを有効にする
	materialDataSphere_.enableLightting = true;

	// 光の設定
	directionalLightData_.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	directionalLightData_.direction = { 0.0f, -1.0f, 0.0f };
	directionalLightData_.intensity = 1.0f;


	// vertexResourceを生成する
	CreateVertexResource();
	// TransformationMatrix用のResourceを作る
	CreateTransformationMatrixResource();
	// Material用のResourceを作る
	CreateMaterialResource();
	// DirectionalLight用のResourceを作る
	CreateDirectionalLightingResource();
	//vertexBufferViewを生成する
	vertexBufferViewSphere_ = CreateBufferView(vertexResourceSphere_);

	// vertexBufferViewを生成する
	vertexResourceSphere_->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSphere_));
	

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
			vertexDataSphere_[start_].position.x = sphereElemnt_.radius * (cos(lat) * cos(lon));
			vertexDataSphere_[start_].position.y = sphereElemnt_.radius * (sin(lat));
			vertexDataSphere_[start_].position.z = sphereElemnt_.radius * (cos(lat) * sin(lon));
			vertexDataSphere_[start_].position.w = 1.0f;
			vertexDataSphere_[start_].texCoord = { u, v + uvLength };
			vertexDataSphere_[start_].normal.x = vertexDataSphere_[start_].position.x;
			vertexDataSphere_[start_].normal.y = vertexDataSphere_[start_].position.y;
			vertexDataSphere_[start_].normal.z = vertexDataSphere_[start_].position.z;

			// 点B(左上)
			vertexDataSphere_[start_ + 1].position.x = sphereElemnt_.radius * (cos(lat + latEvery)) * cos(lon);
			vertexDataSphere_[start_ + 1].position.y = sphereElemnt_.radius * (sin(lat + latEvery));
			vertexDataSphere_[start_ + 1].position.z = sphereElemnt_.radius * (cos(lat + latEvery)) * sin(lon);
			vertexDataSphere_[start_ + 1].position.w = 1.0f;
			vertexDataSphere_[start_ + 1].texCoord = { u, v };
			vertexDataSphere_[start_ + 1].normal.x = vertexDataSphere_[start_ + 1].position.x;
			vertexDataSphere_[start_ + 1].normal.y = vertexDataSphere_[start_ + 1].position.y;
			vertexDataSphere_[start_ + 1].normal.z = vertexDataSphere_[start_ + 1].position.z;

			// 点C(右下)
			vertexDataSphere_[start_ + 2].position.x = sphereElemnt_.radius * (cos(lat) * cos(lon + lonEvery));
			vertexDataSphere_[start_ + 2].position.y = sphereElemnt_.radius * (sin(lat));
			vertexDataSphere_[start_ + 2].position.z = sphereElemnt_.radius * (cos(lat) * sin(lon + lonEvery));
			vertexDataSphere_[start_ + 2].position.w = 1.0f;
			vertexDataSphere_[start_ + 2].texCoord = { u + uvLength, v + uvLength };
			vertexDataSphere_[start_ + 2].normal.x = vertexDataSphere_[start_ + 2].position.x;
			vertexDataSphere_[start_ + 2].normal.y = vertexDataSphere_[start_ + 2].position.y;
			vertexDataSphere_[start_ + 2].normal.z = vertexDataSphere_[start_ + 2].position.z;

#pragma endregion

#pragma region Triangle２枚目

			// 点D(右上)
			vertexDataSphere_[start_ + 3].position.x = sphereElemnt_.radius * (cos(lat + latEvery) * cos(lon + lonEvery));
			vertexDataSphere_[start_ + 3].position.y = sphereElemnt_.radius * (sin(lat + latEvery));
			vertexDataSphere_[start_ + 3].position.z = sphereElemnt_.radius * (cos(lat + latEvery) * sin(lon + lonEvery));
			vertexDataSphere_[start_ + 3].position.w = 1.0f;
			vertexDataSphere_[start_ + 3].texCoord = { u + uvLength, v };
			vertexDataSphere_[start_ + 3].normal.x = vertexDataSphere_[start_ + 3].position.x;
			vertexDataSphere_[start_ + 3].normal.y = vertexDataSphere_[start_ + 3].position.y;
			vertexDataSphere_[start_ + 3].normal.z = vertexDataSphere_[start_ + 3].position.z;

			// 点C(右下)
			vertexDataSphere_[start_ + 4].position.x = sphereElemnt_.radius * (cos(lat) * cos(lon + lonEvery));
			vertexDataSphere_[start_ + 4].position.y = sphereElemnt_.radius * (sin(lat));
			vertexDataSphere_[start_ + 4].position.z = sphereElemnt_.radius * (cos(lat) * sin(lon + lonEvery));
			vertexDataSphere_[start_ + 4].position.w = 1.0f;
			vertexDataSphere_[start_ + 4].texCoord = { u + uvLength, v + uvLength };
			vertexDataSphere_[start_ + 4].normal.x = vertexDataSphere_[start_ + 4].position.x;
			vertexDataSphere_[start_ + 4].normal.y = vertexDataSphere_[start_ + 4].position.y;
			vertexDataSphere_[start_ + 4].normal.z = vertexDataSphere_[start_ + 4].position.z;

			// 点B(左上)
			vertexDataSphere_[start_ + 5].position.x = sphereElemnt_.radius * (cos(lat + latEvery) * cos(lon));
			vertexDataSphere_[start_ + 5].position.y = sphereElemnt_.radius * (sin(lat + latEvery));
			vertexDataSphere_[start_ + 5].position.z = sphereElemnt_.radius * (cos(lat + latEvery) * sin(lon));
			vertexDataSphere_[start_ + 5].position.w = 1.0f;
			vertexDataSphere_[start_ + 5].texCoord = { u, v };
			vertexDataSphere_[start_ + 5].normal.x = vertexDataSphere_[start_ + 5].position.x;
			vertexDataSphere_[start_ + 5].normal.y = vertexDataSphere_[start_ + 5].position.y;
			vertexDataSphere_[start_ + 5].normal.z = vertexDataSphere_[start_ + 5].position.z;

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
	hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&uploadHeapProperties_, D3D12_HEAP_FLAG_NONE,
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
	transformationMatrixResourceSphere_ = CreateBufferResource(sizeof(TransformationMatrix));

	// 書き込むためのアドレスを取得
	transformationMatrixResourceSphere_->Map(0, nullptr, reinterpret_cast<void**>(&transfomationMatrixDataSphere_));
}



/// <summary>
/// Sphere用のWorldViewProjectonMatrixを作る
/// </summary>
void Sphere::CreateWVPMatrix(WorldTransform transform, Matrix4x4& viewMatrix) {

	// Sprite用のWorldViewProjectonMatrixを作る
	worldMatrixSphere = MakeAffineMatrix(transform.scale_, transform.rotate_, Add(transform.translation_, sphereElemnt_.center));

	transfomationMatrixDataSphere_->WVP = Multiply(worldMatrixSphere, viewMatrix);
	transfomationMatrixDataSphere_->World = MakeIdentity4x4();
}


/// <summary>
/// vertexResourceを生成する
/// </summary>
void Sphere::CreateVertexResource() {

	// vertexResourceを生成する
	vertexResourceSphere_ = CreateBufferResource(sizeof(VertexData) * subdivision_ * subdivision_ * 6);

	// vertexBufferViewを生成する
	vertexResourceSphere_->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSphere_));
}

/// <summary>
/// Material用のResourceを作る
/// </summary>
void Sphere::CreateMaterialResource() {

	// マテリアル用のリソースを作る。今回はcolor1つ分サイズを用意する
	materialResourceSphere_ = CreateBufferResource(sizeof(Material));

	// マテリアルにデータを書き込む
	// 書き込むためのアドレスを取得
	materialResourceSphere_->Map(0, nullptr, reinterpret_cast<void**>(&materialDataSphere_));
}

/// <summary>
/// DirectionalLight用のResourceを作る
/// </summary>
void Sphere::CreateDirectionalLightingResource() {

	directionalLightingResource_ = CreateBufferResource(sizeof(DirectionalLight));

	directionalLightingResource_->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData_));
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