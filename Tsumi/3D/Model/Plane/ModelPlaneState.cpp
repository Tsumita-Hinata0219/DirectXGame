#include "ModelPlaneState.h"
#include "Model.h"


/// <summary>
/// 初期化処理
/// </summary>
void ModelPlaneState::Initialize(Model* pModel) {

	pModel;

	// 座標の設定
	size_ = 0.5f;

	// リソースの作成
	resource_.Vertex = CreateResource::CreateBufferResource(sizeof(VertexData) * 4);
	resource_.TransformationMatrix = CreateResource::CreateBufferResource(sizeof(Matrix4x4));
	resource_.Material = CreateResource::CreateBufferResource(sizeof(Vector4));
	resource_.VertexBufferView = CreateResource::CreateVertexBufferView(sizeof(VertexData) * 4, resource_.Vertex.Get(), 4);

	resource_.Index = CreateResource::CreateBufferResource(sizeof(uint32_t) * 6);
	resource_.IndexBufferView = CreateResource::CreateIndexBufferview(sizeof(uint32_t) * 6, resource_.Index.Get());

}


/// <summary>
/// 描画処理
/// </summary>
void ModelPlaneState::Draw(Model* pModel, WorldTransform worldTransform, ViewProjection view) {

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
	Matrix4x4 worldMatrixSphere = MakeAffineMatrix(worldTransform.scale, worldTransform.rotate, worldTransform.translate);
	transformaationMatData->WVP = Multiply(worldMatrixSphere, view.matProjection);
	transformaationMatData->World = MakeIdentity4x4();
	Vector3 pos = worldTransform.translate;

	// 左下
	vertexData[0].position = { pos.x - size_, pos.y - size_, pos.z, 1.0f };
	vertexData[0].texCoord = { 0.0f, 1.0f };
	vertexData[0].normal = { 0.0f, 1.0f, 0.0f };

	// 左上
	vertexData[1].position = { pos.x - size_, pos.y + size_, pos.z, 1.0f };
	vertexData[1].texCoord = { 0.0f, 0.0f };
	vertexData[1].normal = { 0.0f, 1.0f, 0.0f };


	// 右下
	vertexData[2].position = { pos.x + size_, pos.y - size_, pos.z, 1.0f };
	vertexData[2].texCoord = { 1.0f, 1.0f };
	vertexData[2].normal = { 0.0f, 1.0f, 0.0f };

	// 右上
	vertexData[3].position = { pos.x + size_, pos.y + size_, pos.z, 1.0f };
	vertexData[3].texCoord = { 1.0f, 0.0f };
	vertexData[3].normal = { 0.0f, 1.0f, 0.0f };


	// 頂点インデックス
	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;


	// マテリアルの設定
	materialData->color = pModel->GetColor();

	// コマンドコール
	CommandCall(pModel->GetUseTexture());
}


/// <summary>
/// コマンドコール処理
/// </summary>
void ModelPlaneState::CommandCall(uint32_t texture) {

	// RootSignatureを設定。
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootSignature(NormalGraphicPipeline::GetInstance()->GetPsoProperty().rootSignature);
	// PSOを設定
	DirectXCommon::GetInstance()->GetCommandList()->SetPipelineState(NormalGraphicPipeline::GetInstance()->GetPsoProperty().graphicsPipelineState);

	///// いざ描画！！！！！
	// VBVを設定
	DirectXCommon::GetInstance()->GetCommandList()->IASetVertexBuffers(0, 1, &resource_.VertexBufferView);
	DirectXCommon::GetInstance()->GetCommandList()->IASetIndexBuffer(&resource_.IndexBufferView);

	// 形状を設定
	DirectXCommon::GetInstance()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// CBVを設定する
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	// wvp用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(1, resource_.TransformationMatrix->GetGPUVirtualAddress());

	// DescriptorTableを設定する
	if (!texture == 0) {
		DescriptorManager::SetGraphicsRootDescriptorTable(3, texture);
	}

	// 描画！(DrawCall / ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	DirectXCommon::GetInstance()->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
}