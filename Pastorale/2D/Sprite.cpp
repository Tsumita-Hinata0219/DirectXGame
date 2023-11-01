#include "Sprite.h"



/// <summary>
/// 初期化処理
/// </summary>
void Sprite::Initialize(Vector2 pos, Vector2 size) {

	// 座標の設定
	position_ = pos;

	// 座標の設定
	position_ = size;

	// テクスチャの設定
	// デフォルトではuvCheckerを使う
	useTexture_ = 1;

	// 色の設定
	color_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// リソースの作成
	resource_.Vertex = CreateResource::CreateBufferResource(sizeof(VertexData) * 6);
	resource_.TransformationMatrix = CreateResource::CreateBufferResource(sizeof(Matrix4x4));
	resource_.Material = CreateResource::CreateBufferResource(sizeof(Vector4));
	resource_.BufferView = CreateResource::CreateBufferView(sizeof(VertexData) * 6, resource_.Vertex, 6);
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
	DirectXCommon::GetInstance()->GetCommands().List->IASetVertexBuffers(0, 1, &resource_.BufferView); // VBVを設定

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
	DirectXCommon::GetInstance()->GetCommands().List->DrawInstanced(6, 1, 0, 0);
}



/// <summary>
/// 頂点データを設定する
/// </summary>
void Sprite::SetVertex(WorldTransform transform) {

	VertexData* vertexData = nullptr;
	TransformationMatrix* transformaationMatData = nullptr;
	Material* materialData = nullptr;

	// 書き込みができるようにする
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.TransformationMatrix->Map(0, nullptr, reinterpret_cast<void**>(&transformaationMatData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));


	// Sprite用のWorldViewProjectonMatrixを作る
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform.scale_, transform.rotate_, transform.translation_);
	Matrix4x4 viewMatrix = MakeIdentity4x4();
	Matrix4x4 projectionMatrix =
		MakeOrthographicMatrix(0.0f, 0.0f, float(WinApp::GetInstance()->GetClientWidth()), float(WinApp::GetInstance()->GetCliendHeight()), 0.0f, 100.0f);
	Matrix4x4 worldProjectionMatrix =
		Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	transformaationMatData->WVP = worldProjectionMatrix;


	/// 三角形
	// １枚目
	vertexData[0].position = { position_.x, position_.y + size_.y, 0.1f };           // 左下
	vertexData[1].position = { position_.x, position_.y, 0.1f };                     // 左上
	vertexData[2].position = { position_.x + size_.x, position_.y + size_.y, 0.1f }; // 右下
	// ２枚目
	vertexData[3].position = { position_.x, position_.y, 0.1f };	                    // 左上
	vertexData[4].position = { position_.x + size_.x, position_.y, 0.1f };           // 右上
	vertexData[5].position = { position_.x + size_.x, position_.y + size_.y, 0.1f }; // 右下

	/// テクスチャ
	// １枚目
	vertexData[0].texCoord = { 0.0f, 1.0f };
	vertexData[1].texCoord = { 0.0f, 0.0f };
	vertexData[2].texCoord = { 1.0f, 1.0f };
	// ２枚目
	vertexData[3].texCoord = { 0.0f, 0.0f };
	vertexData[4].texCoord = { 1.0f, 0.0f };
	vertexData[5].texCoord = { 1.0f, 1.0f };

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