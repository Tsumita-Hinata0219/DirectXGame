#include "Model.h"



// 初期化処理
void Model::Initialize() {

	// ワールドトランスフォームの設定
	worldTansform_.scale_ = { 1.0f, 1.0f, 1.0f };
	worldTansform_.rotate_ = { 0.0f, 0.0f, 0.0f };
	worldTansform_.translation_ = { 0.0f, 0.0f, 0.0f };

	// 座標の設定
	size_ = 0.5f;

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



// 三角形の描画
void Model::Draw(WorldTransform worldTransform, Matrix4x4& viewMatrix) {

	// 頂点データを設定する
	SetVertex(worldTransform, viewMatrix);

	// RootSignatureを設定。
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootSignature(NormalGraphicPipeline::GetInstance()->GetPsoProperty().rootSignature);
	// PSOを設定
	DirectXCommon::GetInstance()->GetCommands().List->SetPipelineState(NormalGraphicPipeline::GetInstance()->GetPsoProperty().graphicsPipelineState);

	///// いざ描画！！！！！
	// VBVを設定
	DirectXCommon::GetInstance()->GetCommands().List->IASetVertexBuffers(0, 1, &resource_.VertexBufferView);
	DirectXCommon::GetInstance()->GetCommands().List->IASetIndexBuffer(&resource_.IndexBufferView);

	// 形状を設定
	DirectXCommon::GetInstance()->GetCommands().List->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// CBVを設定する
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	// wvp用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootConstantBufferView(1, resource_.TransformationMatrix->GetGPUVirtualAddress());

	// DescriptorTableを設定する
	if (!useTexture_ == 0) {
		TextureManager::GetInstance()->SetGraphicsRootDescriptorTable(2, useTexture_);
	}

	// 描画！(DrawCall / ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	DirectXCommon::GetInstance()->GetCommands().List->DrawIndexedInstanced(6, 1, 0, 0, 0);
	//DirectXCommon::GetInstance()->GetCommands().List->DrawInstanced(6, 1, 0, 0);
}



/// <summary>
/// 頂点データを設定する
/// </summary>
void Model::SetVertex(WorldTransform worldTransform, Matrix4x4& viewMatrix) {

	VertexData* vertexData = nullptr;
	TransformationMatrix* transformaationMatData = nullptr;
	Material* materialData = nullptr;
	uint32_t* indexData = nullptr;

	// 書き込みができるようにする
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.TransformationMatrix->Map(0, nullptr, reinterpret_cast<void**>(&transformaationMatData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));

	// Sphere用のWorldViewProjectionMatrixを作る
	Matrix4x4 worldMatrixSphere = MakeAffineMatrix(worldTransform.scale_, worldTransform.rotate_, worldTransform.translation_);
	transformaationMatData->WVP = Multiply(worldMatrixSphere, viewMatrix);
	transformaationMatData->World = MakeIdentity4x4();
	pos_ = worldTransform.translation_;

	// 左下
	vertexData[0].position = { pos_.x - size_, pos_.y - size_, pos_.z, 1.0f };
	vertexData[0].texCoord = { 0.0f, 1.0f };
	vertexData[0].normal = { 0.0f, 1.0f, 0.0f };

	// 左上
	vertexData[1].position = { pos_.x - size_, pos_.y + size_, pos_.z, 1.0f };
	vertexData[1].texCoord = { 0.0f, 0.0f };
	vertexData[1].normal = { 0.0f, 1.0f, 0.0f };


	// 右下
	vertexData[2].position = { pos_.x + size_, pos_.y - size_, pos_.z, 1.0f };
	vertexData[2].texCoord = { 1.0f, 1.0f };
	vertexData[2].normal = { 0.0f, 1.0f, 0.0f };

	// 右上
	vertexData[3].position = { pos_.x + size_, pos_.y + size_, pos_.z, 1.0f };
	vertexData[3].texCoord = { 1.0f, 0.0f };
	vertexData[3].normal = { 0.0f, 1.0f, 0.0f };


	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;


	// 引数の色コードをVector4に変換してmaterialDate_に送る
	materialData->color = color_;
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


