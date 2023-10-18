#include "GraphicPipelineManager.h"


/// <summary>
/// PSOクラスのインスタンス取得
/// </summary>
GraphicPipelineManager* GraphicPipelineManager::GetInstance() {

	static GraphicPipelineManager instance;
	return &instance;
}



/* --- PSOを設定する --- */

void GraphicPipelineManager::SetPSO() {

	// RootSignatureを作成
	MakeRootSignature();

	// InputLayoutを設定する
	SetInputLayout();

	// BlendStateを設定する
	SetBlendState();

	// RasiterzerStateを設定する
	SetRasiterzerState();

	// Shaderをcompileする
	SetShaderCompile();

	// PSOを生成する
	CreatePipelineStateObject();
}



/* --- RootSignatureを作成 --- */

void GraphicPipelineManager::MakeRootSignature() {

	// RootSignature作成
	GraphicPipelineManager::GetInstance()->usePso_.descriptionRootSignature_.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	// 色に関する
	GraphicPipelineManager::GetInstance()->usePso_.rootParameters_[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; // CBVを使う
	GraphicPipelineManager::GetInstance()->usePso_.rootParameters_[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
	GraphicPipelineManager::GetInstance()->usePso_.rootParameters_[0].Descriptor.ShaderRegister = 0; // レジスタ番号0とバインド

	// 頂点位置に関する
	GraphicPipelineManager::GetInstance()->usePso_.rootParameters_[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;//CSVで使う
	GraphicPipelineManager::GetInstance()->usePso_.rootParameters_[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;//VERTEXShaderで使う
	GraphicPipelineManager::GetInstance()->usePso_.rootParameters_[1].Descriptor.ShaderRegister = 0;//レジスタ番号を0にバインド
	GraphicPipelineManager::GetInstance()->usePso_.descriptionRootSignature_.pParameters = GraphicPipelineManager::GetInstance()->usePso_.rootParameters_; // ルートパラメータ配列へのポインタ
	GraphicPipelineManager::GetInstance()->usePso_.descriptionRootSignature_.NumParameters = _countof(GraphicPipelineManager::GetInstance()->usePso_.rootParameters_); // 配列の長さ

	// テクスチャに関する
	GraphicPipelineManager::GetInstance()->usePso_.descriptorRange_[0].BaseShaderRegister = 0; // 0から始まる
	GraphicPipelineManager::GetInstance()->usePso_.descriptorRange_[0].NumDescriptors = 1; // 数は1つ
	GraphicPipelineManager::GetInstance()->usePso_.descriptorRange_[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // offsetを自動計算
	GraphicPipelineManager::GetInstance()->usePso_.rootParameters_[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // DescriptorTableを使う
	GraphicPipelineManager::GetInstance()->usePso_.rootParameters_[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixShaderで使う
	GraphicPipelineManager::GetInstance()->usePso_.rootParameters_[2].DescriptorTable.pDescriptorRanges = GraphicPipelineManager::GetInstance()->usePso_.descriptorRange_; // Tableの中身の配列を指定
	GraphicPipelineManager::GetInstance()->usePso_.rootParameters_[2].DescriptorTable.NumDescriptorRanges = _countof(GraphicPipelineManager::GetInstance()->usePso_.descriptorRange_); // Tableで利用する

	// Samplerの設定
	GraphicPipelineManager::GetInstance()->usePso_.staticSamplers_[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR; // バイリニアフィルタ
	GraphicPipelineManager::GetInstance()->usePso_.staticSamplers_[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 0～1の範囲外をリピート
	GraphicPipelineManager::GetInstance()->usePso_.staticSamplers_[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	GraphicPipelineManager::GetInstance()->usePso_.staticSamplers_[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	GraphicPipelineManager::GetInstance()->usePso_.staticSamplers_[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER; // 比較しない
	GraphicPipelineManager::GetInstance()->usePso_.staticSamplers_[0].MaxLOD = D3D12_FLOAT32_MAX; // ありったけのMipmapを使う
	GraphicPipelineManager::GetInstance()->usePso_.staticSamplers_[0].ShaderRegister = 0; // レジスタ番号0を使う
	GraphicPipelineManager::GetInstance()->usePso_.staticSamplers_[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
	GraphicPipelineManager::GetInstance()->usePso_.descriptionRootSignature_.pStaticSamplers = GraphicPipelineManager::GetInstance()->usePso_.staticSamplers_;
	GraphicPipelineManager::GetInstance()->usePso_.descriptionRootSignature_.NumStaticSamplers = _countof(GraphicPipelineManager::GetInstance()->usePso_.staticSamplers_);


	// シリアライズしてバイナリにする
	HRESULT hr_ = D3D12SerializeRootSignature(&GraphicPipelineManager::GetInstance()->usePso_.descriptionRootSignature_,
		D3D_ROOT_SIGNATURE_VERSION_1, &GraphicPipelineManager::GetInstance()->usePso_.signatureBlob_, &GraphicPipelineManager::GetInstance()->usePso_.errorBlob_);
	if (FAILED(hr_)) {
		Log(reinterpret_cast<char*>(GraphicPipelineManager::GetInstance()->usePso_.errorBlob_->GetBufferPointer()));
		assert(false);
	}
	// バイナリを元に生成
	hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateRootSignature(0, GraphicPipelineManager::GetInstance()->usePso_.signatureBlob_->GetBufferPointer(),
		GraphicPipelineManager::GetInstance()->usePso_.signatureBlob_->GetBufferSize(), IID_PPV_ARGS(&GraphicPipelineManager::GetInstance()->usePso_.rootSignature_));
	assert(SUCCEEDED(hr_));
}



/* --- InputLayoutを設定する --- */

void GraphicPipelineManager::SetInputLayout() {

	// InputLayout
	GraphicPipelineManager::GetInstance()->usePso_.inputElementDescs_[0].SemanticName = "POSITION";
	GraphicPipelineManager::GetInstance()->usePso_.inputElementDescs_[0].SemanticIndex = 0;
	GraphicPipelineManager::GetInstance()->usePso_.inputElementDescs_[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	GraphicPipelineManager::GetInstance()->usePso_.inputElementDescs_[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	GraphicPipelineManager::GetInstance()->usePso_.inputElementDescs_[1].SemanticName = "TEXCOORD";
	GraphicPipelineManager::GetInstance()->usePso_.inputElementDescs_[1].SemanticIndex = 0;
	GraphicPipelineManager::GetInstance()->usePso_.inputElementDescs_[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	GraphicPipelineManager::GetInstance()->usePso_.inputElementDescs_[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	GraphicPipelineManager::GetInstance()->usePso_.inputLayoutDesc_.pInputElementDescs = GraphicPipelineManager::GetInstance()->usePso_.inputElementDescs_;
	GraphicPipelineManager::GetInstance()->usePso_.inputLayoutDesc_.NumElements = _countof(GraphicPipelineManager::GetInstance()->usePso_.inputElementDescs_);
}



/* --- BlendStateを設定する --- */

void GraphicPipelineManager::SetBlendState() {

	// BlendStateの設定
	// 全ての色要素を書き込む
	GraphicPipelineManager::GetInstance()->usePso_.blendDesc_.RenderTarget[0].RenderTargetWriteMask =
		D3D12_COLOR_WRITE_ENABLE_ALL;
}



/* --- RasiterzerStateを設定する --- */

void GraphicPipelineManager::SetRasiterzerState() {

	// RasiterzerStateの設定
	// 裏面(時計回り)を表示しない
	GraphicPipelineManager::GetInstance()->usePso_.rasterizerDesc_.CullMode = D3D12_CULL_MODE_BACK;
	// 三角形の中を塗りつぶす
	GraphicPipelineManager::GetInstance()->usePso_.rasterizerDesc_.FillMode = D3D12_FILL_MODE_SOLID;
}



/* --- Shaderをcompileする --- */

void GraphicPipelineManager::SetShaderCompile() {

	// Shaderをコンパイルする
	GraphicPipelineManager::GetInstance()->usePso_.vertexShaderBlob_ = DirectXCommon::GetInstance()->CompileShader(
		L"Resources/shaders/Object3d.VS.hlsl",
		L"vs_6_0",
		DirectXCommon::GetInstance()->GetDxcUtils(),
		DirectXCommon::GetInstance()->GetDxcCompiler(),
		DirectXCommon::GetInstance()->GetIncludeHandler());
	assert(GraphicPipelineManager::GetInstance()->usePso_.vertexShaderBlob_ != nullptr);

	GraphicPipelineManager::GetInstance()->usePso_.pixelShaderBlob_ = DirectXCommon::GetInstance()->CompileShader(
		L"Resources/shaders/Object3d.PS.hlsl",
		L"ps_6_0",
		DirectXCommon::GetInstance()->GetDxcUtils(),
		DirectXCommon::GetInstance()->GetDxcCompiler(),
		DirectXCommon::GetInstance()->GetIncludeHandler());
	assert(GraphicPipelineManager::GetInstance()->usePso_.pixelShaderBlob_ != nullptr);
}



/* --- PSOを生成する --- */

void GraphicPipelineManager::CreatePipelineStateObject() {

	D3D12_DEPTH_STENCIL_DESC depthStencilDesc = DirectXCommon::GetInstance()->GetDepthStencilDesc();

	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.pRootSignature = GraphicPipelineManager::GetInstance()->usePso_.rootSignature_; // RootSignature
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.InputLayout = GraphicPipelineManager::GetInstance()->usePso_.inputLayoutDesc_; // InputLayout
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.VS = { GraphicPipelineManager::GetInstance()->usePso_.vertexShaderBlob_->GetBufferPointer(),
	GraphicPipelineManager::GetInstance()->usePso_.vertexShaderBlob_->GetBufferSize() }; // VertexShader
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.PS = { GraphicPipelineManager::GetInstance()->usePso_.pixelShaderBlob_->GetBufferPointer(),
	GraphicPipelineManager::GetInstance()->usePso_.pixelShaderBlob_->GetBufferSize() }; // PixelShader
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.BlendState = GraphicPipelineManager::GetInstance()->usePso_.blendDesc_; // BlendState
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.RasterizerState = GraphicPipelineManager::GetInstance()->usePso_.rasterizerDesc_; // RasterizeState


	// 書き込むRTVの情報
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.NumRenderTargets = 1;
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;


	// 利用するトポロジ(形状)もタイプ。三角形
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


	// どのように画面に色を打ち込むかの設定(気にしなくて良い)
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.SampleDesc.Count = 1;
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;


	// Depthの機能を有効化する
	depthStencilDesc.DepthEnable = true;
	// 書き込む
	depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	// 比較関数はLessEqual。つまり、近ければ描画される
	depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	// DepthStencilの設定
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.DepthStencilState = depthStencilDesc;
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;


	DirectXCommon::GetInstance()->SetDepthStencilDesc(depthStencilDesc);


	// 実際に生成
	HRESULT hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateGraphicsPipelineState(&GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc_,
		IID_PPV_ARGS(&GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineState_));
	assert(SUCCEEDED(hr_));
}
