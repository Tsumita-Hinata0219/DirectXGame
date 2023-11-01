#include "Sphere.h"



/// <summary>
/// 初期化処理
/// </summary>
void Sphere::Initialize() {

	// ワールドトランスフォームの設定
	worldTansform_.scale_ = { 1.0f, 1.0f, 1.0f };
	worldTansform_.rotate_ = { 0.0f, 0.0f, 0.0f };
	worldTansform_.translation_ = { 0.0f, 0.0f, 0.0f };

	// テクスチャの設定
	// デフォルトではuvCheckerを使う
	useTexture_ = 1;

	// 色の設定
	material_.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	// Lightingを有効にする
	material_.enableLightting = false;
	// 光の設定
	light_.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	light_.direction = { 0.0f, -1.0f, 0.0f };
	light_.intensity = 1.0f;

	// リソースの作成
	resource_.Vertex = CreateResource::CreateBufferResource(sizeof(VertexData) * subdivision_ * subdivision_ * 6);
	resource_.TransformationMatrix = CreateResource::CreateBufferResource(sizeof(TransformationMatrix));
	resource_.Material = CreateResource::CreateBufferResource(sizeof(Material));
	resource_.Lighting = CreateResource::CreateBufferResource(sizeof(DirectionalLight));
	resource_.BufferView = CreateResource::CreateBufferView(sizeof(VertexData) * 6 * subdivision_ * subdivision_, resource_.Vertex, 6 * subdivision_ * subdivision_);
}



/// <summary>
/// 描画処理
/// </summary>
void Sphere::Draw(WorldTransform worldTransform, Matrix4x4& viewMatrix) {

	// 頂点の設定
	SetVertex(worldTransform, viewMatrix);

	// RootSignatureを設定。
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootSignature(LightGraphicPipeline::GetInstance()->GetPsoProperty().rootSignature);
	// PSOを設定
	DirectXCommon::GetInstance()->GetCommands().List->SetPipelineState(LightGraphicPipeline::GetInstance()->GetPsoProperty().graphicsPipelineState);

	/// コマンドを積む
	// 頂点の設定 (VBVを設定)
	DirectXCommon::GetInstance()->GetCommands().List->IASetVertexBuffers(0, 1, &resource_.BufferView);

	//形状を設定
	DirectXCommon::GetInstance()->GetCommands().List->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 色用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());
	
	// wvp用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootConstantBufferView(1, resource_.TransformationMatrix->GetGPUVirtualAddress());

	// DescriptorTableを設定する
	if (!useTexture_ == 0) {
		TextureManager::GetInstance()->SetGraphicsRootDescriptorTable(2, useTexture_);
	}

	// 光用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootConstantBufferView(3, resource_.Lighting->GetGPUVirtualAddress());

	// 描画！ (DrawCall / ドローコール)
	DirectXCommon::GetInstance()->GetCommands().List->DrawInstanced(subdivision_ * subdivision_ * 6, 1, 0, 0);
}



/// <summary>
/// 頂点データを設定する
/// </summary>
void Sphere::SetVertex(WorldTransform worldTransform, Matrix4x4& viewMatrix) {

	VertexData* vertexData = nullptr;
	TransformationMatrix* transformaationMatData = nullptr;
	Material* materialData = nullptr;
	DirectionalLight* lightData = nullptr;

	// 書き込みができるようにする
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.TransformationMatrix->Map(0, nullptr, reinterpret_cast<void**>(&transformaationMatData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Lighting->Map(0, nullptr, reinterpret_cast<void**>(&lightData));

	// Sphere用のWorldViewProjectionMatrixを作る
	Matrix4x4 worldMatrixSphere = MakeAffineMatrix(worldTransform.scale_, worldTransform.rotate_, worldTransform.translation_);
	transformaationMatData->WVP = Multiply(worldMatrixSphere, viewMatrix);
	transformaationMatData->World = MakeIdentity4x4();


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
			vertexData[start_].position.x = radius_ * (cos(lat) * cos(lon));
			vertexData[start_].position.y = radius_ * (sin(lat));
			vertexData[start_].position.z = radius_ * (cos(lat) * sin(lon));
			vertexData[start_].position.w = 1.0f;
			vertexData[start_].texCoord = { u, v + uvLength };
			vertexData[start_].normal.x = vertexData[start_].position.x;
			vertexData[start_].normal.y = vertexData[start_].position.y;
			vertexData[start_].normal.z = vertexData[start_].position.z;

			// 点B(左上)
			vertexData[start_ + 1].position.x = radius_ * (cos(lat + latEvery)) * cos(lon);
			vertexData[start_ + 1].position.y = radius_ * (sin(lat + latEvery));
			vertexData[start_ + 1].position.z = radius_ * (cos(lat + latEvery)) * sin(lon);
			vertexData[start_ + 1].position.w = 1.0f;
			vertexData[start_ + 1].texCoord = { u, v };
			vertexData[start_ + 1].normal.x = vertexData[start_ + 1].position.x;
			vertexData[start_ + 1].normal.y = vertexData[start_ + 1].position.y;
			vertexData[start_ + 1].normal.z = vertexData[start_ + 1].position.z;

			// 点C(右下)
			vertexData[start_ + 2].position.x = radius_ * (cos(lat) * cos(lon + lonEvery));
			vertexData[start_ + 2].position.y = radius_ * (sin(lat));
			vertexData[start_ + 2].position.z = radius_ * (cos(lat) * sin(lon + lonEvery));
			vertexData[start_ + 2].position.w = 1.0f;
			vertexData[start_ + 2].texCoord = { u + uvLength, v + uvLength };
			vertexData[start_ + 2].normal.x = vertexData[start_ + 2].position.x;
			vertexData[start_ + 2].normal.y = vertexData[start_ + 2].position.y;
			vertexData[start_ + 2].normal.z = vertexData[start_ + 2].position.z;

#pragma endregion

#pragma region Triangle２枚目

			// 点D(右上)
			vertexData[start_ + 3].position.x = radius_ * (cos(lat + latEvery) * cos(lon + lonEvery));
			vertexData[start_ + 3].position.y = radius_ * (sin(lat + latEvery));
			vertexData[start_ + 3].position.z = radius_ * (cos(lat + latEvery) * sin(lon + lonEvery));
			vertexData[start_ + 3].position.w = 1.0f;
			vertexData[start_ + 3].texCoord = { u + uvLength, v };
			vertexData[start_ + 3].normal.x = vertexData[start_ + 3].position.x;
			vertexData[start_ + 3].normal.y = vertexData[start_ + 3].position.y;
			vertexData[start_ + 3].normal.z = vertexData[start_ + 3].position.z;

			// 点C(右下)
			vertexData[start_ + 4].position.x = radius_ * (cos(lat) * cos(lon + lonEvery));
			vertexData[start_ + 4].position.y = radius_ * (sin(lat));
			vertexData[start_ + 4].position.z = radius_ * (cos(lat) * sin(lon + lonEvery));
			vertexData[start_ + 4].position.w = 1.0f;
			vertexData[start_ + 4].texCoord = { u + uvLength, v + uvLength };
			vertexData[start_ + 4].normal.x = vertexData[start_ + 4].position.x;
			vertexData[start_ + 4].normal.y = vertexData[start_ + 4].position.y;
			vertexData[start_ + 4].normal.z = vertexData[start_ + 4].position.z;

			// 点B(左上)
			vertexData[start_ + 5].position.x = radius_ * (cos(lat + latEvery) * cos(lon));
			vertexData[start_ + 5].position.y = radius_ * (sin(lat + latEvery));
			vertexData[start_ + 5].position.z = radius_ * (cos(lat + latEvery) * sin(lon));
			vertexData[start_ + 5].position.w = 1.0f;
			vertexData[start_ + 5].texCoord = { u, v };
			vertexData[start_ + 5].normal.x = vertexData[start_ + 5].position.x;
			vertexData[start_ + 5].normal.y = vertexData[start_ + 5].position.y;
			vertexData[start_ + 5].normal.z = vertexData[start_ + 5].position.z;

#pragma endregion
		}
	}

	materialData->color = material_.color;
	materialData->enableLightting = material_.enableLightting;
	lightData->color = light_.color;
	lightData->direction = light_.direction;
	lightData->intensity = light_.intensity;
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