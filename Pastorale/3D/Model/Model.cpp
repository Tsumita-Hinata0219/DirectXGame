#include "Model.h"



// 解放処理
Model::~Model() {

}



// 初期化処理
void Model::Initialize() {

	// ワールドトランスフォームの設定
	worldTansform_.scale_ = { 1.0f, 1.0f, 1.0f };
	worldTansform_.rotate_ = { 0.0f, 0.0f, 0.0f };
	worldTansform_.translation_ = { 0.0f, 0.0f, 0.0f };

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



// 三角形の描画
void Model::Draw(TriangleElement element, WorldTransform& transform, Matrix4x4& ViewMatrix) {

	// 頂点データを設定する
	SetVertex(element, transform, ViewMatrix);

	// RootSignatureを設定。
	DirectXCommon::GetInstance()->GetCommands().List->SetGraphicsRootSignature(NormalGraphicPipeline::GetInstance()->GetPsoProperty().rootSignature);
	// PSOを設定
	DirectXCommon::GetInstance()->GetCommands().List->SetPipelineState(NormalGraphicPipeline::GetInstance()->GetPsoProperty().graphicsPipelineState);

	///// いざ描画！！！！！
	// VBVを設定
	DirectXCommon::GetInstance()->GetCommands().List->IASetVertexBuffers(0, 1, &resource_.BufferView);

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
	DirectXCommon::GetInstance()->GetCommands().List->DrawInstanced(6, 1, 0, 0);
}



/// <summary>
/// 頂点データを設定する
/// </summary>
void Model::SetVertex(TriangleElement element, WorldTransform& transform, Matrix4x4& ViewMatrix) {

	VertexData* vertexData = nullptr;
	TransformationMatrix* transformaationMatData = nullptr;
	Material* materialData = nullptr;

	// 書き込みができるようにする
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.TransformationMatrix->Map(0, nullptr, reinterpret_cast<void**>(&transformaationMatData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));

	//行列を作る
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform.scale_, transform.rotate_, transform.translation_);
	// 単位行列を書き込んでおく
	transformaationMatData->WVP = Multiply(worldMatrix, ViewMatrix);


	// Triangle
	// 1枚目
	vertexData[0].position = element.bottomLeft;  // 左下
	vertexData[1].position = element.top;         // 上
	vertexData[2].position = element.bottomRight; // 右下
	// 2枚目
	vertexData[3].position = { -0.5f, -0.5,0.5f,1.0f };  // 左下
	vertexData[4].position = { 0.0f, 0.0f,  0.0f,1.0f }; // 上
	vertexData[5].position = { 0.5f,-0.5f,-0.5f,1.0f };  // 右下

	// Texture
	// 1枚目
	vertexData[0].texCoord = { 0.0f, 1.0f }; // 左下
	vertexData[1].texCoord = { 0.5f, 0.0f }; // 上
	vertexData[2].texCoord = { 1.0f, 1.0f }; // 右下
	// 2枚目
	vertexData[3].texCoord = { 0.0f, 1.0f }; // 左下
	vertexData[4].texCoord = { 0.5f, 0.0f }; // 上
	vertexData[5].texCoord = { 1.0f, 1.0f }; // 右下


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


