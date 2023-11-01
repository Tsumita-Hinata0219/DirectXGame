#include "Sprite.h"



/// <summary>
/// 初期化処理
/// </summary>
void Sprite::Initialize(Vector2 pos, Vector2 size) {

	// 座標の設定
	pos_ = pos;

	// 座標の設定
	size_ = size;

	// テクスチャの設定
	// デフォルトではuvCheckerを使う
	useTexture_ = 1;

	// 色の設定
	color_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// リソースの作成
	resource_.Vertex = CreateResource::CreateBufferResource(sizeof(VertexData) * 4);
	resource_.TransformationMatrix = CreateResource::CreateBufferResource(sizeof(Matrix4x4));
	resource_.Material = CreateResource::CreateBufferResource(sizeof(Vector4));
	resource_.VertexBufferView = CreateResource::CreateVertexBufferView(sizeof(VertexData) * 4, resource_.Vertex, 4);

	resource_.Index = CreateResource::CreateBufferResource(sizeof(uint32_t) * 6);
	resource_.IndexBufferView = CreateResource::CreateIndexBufferview(sizeof(uint32_t) * 6, resource_.Index);
}



/// <summary>
/// 描画処理
/// </summary>
void Sprite::Draw(WorldTransform& transform) {

	// 頂点データを設定する
	SetVertex(transform);

	// RootSignatureを設定。
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootSignature(SpriteGraphicPipeline::GetInstance()->GetPsoProperty().rootSignature);
	// PSOを設定
	DirectXCommon::GetInstance()->GetCommands().List->SetPipelineState(SpriteGraphicPipeline::GetInstance()->GetPsoProperty().graphicsPipelineState);

	// 頂点の設定
	DirectXCommon::GetInstance()->GetCommands().List->IASetVertexBuffers(0, 1, &resource_.VertexBufferView); // VBVを設定
	DirectXCommon::GetInstance()->GetCommands().List->IASetIndexBuffer(&resource_.IndexBufferView);

	// 形状を設定
	DirectXCommon::GetInstance()->GetCommands().List->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 色用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	// wvp用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootConstantBufferView(1, resource_.TransformationMatrix->GetGPUVirtualAddress());

	// DescriptorTableを設定する
	if (!useTexture_ == 0) {
		TextureManager::GetInstance()->SetGraphicsRootDescriptorTable(2, useTexture_);
	}

	// 描画！(DrawCall/ドローコール)
	DirectXCommon::GetInstance()->GetCommands().List->DrawIndexedInstanced(6, 1, 0, 0, 0);
	//DirectXCommon::GetInstance()->GetCommands().List->DrawInstanced(6, 1, 0, 0);
}



/// <summary>
/// 頂点データを設定する
/// </summary>
void Sprite::SetVertex(WorldTransform transform) {

	VertexData* vertexData = nullptr;
	TransformationMatrix* transformaationMatData = nullptr;
	Material* materialData = nullptr;
	uint32_t* indexData = nullptr;

	// 書き込みができるようにする
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.TransformationMatrix->Map(0, nullptr, reinterpret_cast<void**>(&transformaationMatData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));


	// Sprite用のWorldViewProjectonMatrixを作る
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform.scale_, transform.rotate_, transform.translation_);
	Matrix4x4 viewMatrix = MakeIdentity4x4();
	Matrix4x4 projectionMatrix =
		MakeOrthographicMatrix(0.0f, 0.0f, float(WinApp::GetInstance()->GetClientWidth()), float(WinApp::GetInstance()->GetCliendHeight()), 0.0f, 100.0f);
	Matrix4x4 worldProjectionMatrix =
		Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	transformaationMatData->WVP = worldProjectionMatrix;


	// 左下
	vertexData[0].position = { pos_.x, pos_.y + size_.y, 0.0f, 1.0f };
	vertexData[0].texCoord = { 0.0f, 1.0f };

	// 左上
	vertexData[1].position = { pos_.x, pos_.y, 0.0f, 1.0f };
	vertexData[1].texCoord = { 0.0f, 0.0f };


	// 右下
	vertexData[2].position = { pos_.x + size_.x, pos_.y + size_.y, 0.0f, 1.0f };
	vertexData[2].texCoord = { 1.0f, 1.0f };
	
	// 右上
	vertexData[3].position = { pos_.x + size_.x, pos_.y, 0.0f, 1.0f };
	vertexData[3].texCoord = { 1.0f, 0.0f };


	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;


	materialData->color = color_;
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