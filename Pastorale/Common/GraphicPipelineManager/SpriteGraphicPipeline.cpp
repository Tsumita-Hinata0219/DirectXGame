#include "SpriteGraphicPipeline.h"



/// <summary>
/// SpriteGraphicPipelineクラスのインスタンス取得
/// </summary>
SpriteGraphicPipeline* SpriteGraphicPipeline::GetInstance() {
	static SpriteGraphicPipeline instance;
	return &instance;
}



// 初期化処理
void SpriteGraphicPipeline::Initialize() {}



/* --- PSOを設定する --- */
void SpriteGraphicPipeline::SetSpritePso() {

	// RootSignatureを作成
	SpriteGraphicPipeline::MakeRootSignature();

	// InputLayoutを設定する
	SpriteGraphicPipeline::SetInputLayout();

	// BlendStateを設定する
	SpriteGraphicPipeline::SetBlendState();

	// RasiterzerStateを設定する
	SpriteGraphicPipeline::SetRasiterzerState();

	// Shaderをcompileする
	SpriteGraphicPipeline::SetShaderCompile();

	// PSOを生成する
	SpriteGraphicPipeline::CreatePipelineStateObject();
}



/* --- RootSignatureを作成 --- */
void SpriteGraphicPipeline::MakeRootSignature() {

	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	D3D12_ROOT_PARAMETER rootParameters[3]{};
	D3D12_DESCRIPTOR_RANGE descriptorRange[1]{};
	D3D12_STATIC_SAMPLER_DESC staticSamplers[1]{};

	// RootSignature作成
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	// 色に関する
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; // CBVを使う
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
	rootParameters[0].Descriptor.ShaderRegister = 0; // レジスタ番号0とバインド

	// 頂点位置に関する
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;//CSVで使う
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;//VERTEXShaderで使う
	rootParameters[1].Descriptor.ShaderRegister = 0;//レジスタ番号を0にバインド
	descriptionRootSignature.pParameters = rootParameters; // ルートパラメータ配列へのポインタ
	descriptionRootSignature.NumParameters = _countof(rootParameters); // 配列の長さ

	// テクスチャに関する
	descriptorRange[0].BaseShaderRegister = 0; // 0から始まる
	descriptorRange[0].NumDescriptors = 1; // 数は1つ
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // offsetを自動計算
	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // DescriptorTableを使う
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixShaderで使う
	rootParameters[2].DescriptorTable.pDescriptorRanges = descriptorRange; // Tableの中身の配列を指定
	rootParameters[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange); // Tableで利用する

	// Samplerの設定
	staticSamplers[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR; // バイリニアフィルタ
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 0～1の範囲外をリピート
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER; // 比較しない
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX; // ありったけのMipmapを使う
	staticSamplers[0].ShaderRegister = 0; // レジスタ番号0を使う
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);


	// シリアライズしてバイナリにする
	HRESULT hr_ = D3D12SerializeRootSignature(
		&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&SpriteGraphicPipeline::GetInstance()->spritePso_.signatureBlob,
		&SpriteGraphicPipeline::GetInstance()->spritePso_.errorBlob);
	if (FAILED(hr_)) {
		Log(reinterpret_cast<char*>(SpriteGraphicPipeline::GetInstance()->spritePso_.errorBlob->GetBufferPointer()));
		assert(false);
	}

	// バイナリを元に生成
	hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateRootSignature(
		0,
		SpriteGraphicPipeline::GetInstance()->spritePso_.signatureBlob->GetBufferPointer(),
		SpriteGraphicPipeline::GetInstance()->spritePso_.signatureBlob->GetBufferSize(),
		IID_PPV_ARGS(&SpriteGraphicPipeline::GetInstance()->spritePso_.rootSignature));
	assert(SUCCEEDED(hr_));



	SpriteGraphicPipeline::GetInstance()->descriptionRootSignature_ = descriptionRootSignature;
	for (int i = 0; i < 3; i++) {
		SpriteGraphicPipeline::GetInstance()->rootParameters_[i] = rootParameters[i];
	}
	SpriteGraphicPipeline::GetInstance()->descriptorRange_[0] = descriptorRange[0];
	SpriteGraphicPipeline::GetInstance()->staticSamplers_[0] = staticSamplers[0];
}



/* --- InputLayoutを設定する --- */
void SpriteGraphicPipeline::SetInputLayout() {

	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3]{};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};

	// InputLayout
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);



	for (int i = 0; i < 3; i++) {
		SpriteGraphicPipeline::GetInstance()->inputElementDescs_[i] = inputElementDescs[i];
	}
	SpriteGraphicPipeline::GetInstance()->inputLayoutDesc_ = inputLayoutDesc;
}



/* --- BlendStateを設定する --- */
void SpriteGraphicPipeline::SetBlendState() {

	D3D12_BLEND_DESC blendDesc{};

	// BlendStateの設定
	// 全ての色要素を書き込む
	blendDesc.RenderTarget[0].RenderTargetWriteMask =
		D3D12_COLOR_WRITE_ENABLE_ALL;



	SpriteGraphicPipeline::GetInstance()->blendDesc_ = blendDesc;
}



/* --- RasiterzerStateを設定する --- */
void SpriteGraphicPipeline::SetRasiterzerState() {

	D3D12_RASTERIZER_DESC rasterizerDesc{};

	// RasiterzerStateの設定
	// 裏面(時計回り)を表示しない
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	// 三角形の中を塗りつぶす
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;



	SpriteGraphicPipeline::GetInstance()->rasterizerDesc_ = rasterizerDesc;
}



/* --- Shaderをcompileする --- */
void SpriteGraphicPipeline::SetShaderCompile() {

	IDxcBlob* vertexShaderBlob = nullptr;
	IDxcBlob* pixelShaderBlob = nullptr;

	// Shaderをコンパイルする
	vertexShaderBlob = ShaderManager::GetInstance()->GetShaderType().Sprite.VertexBlob;
	assert(vertexShaderBlob != nullptr);

	pixelShaderBlob = ShaderManager::GetInstance()->GetShaderType().Sprite.PixelBlob;
	assert(pixelShaderBlob != nullptr);



	SpriteGraphicPipeline::GetInstance()->vertexShaderBlob_ = vertexShaderBlob;
	SpriteGraphicPipeline::GetInstance()->pixelShaderBlob_ = pixelShaderBlob;
}



/* --- PSOを生成する --- */

void SpriteGraphicPipeline::CreatePipelineStateObject() {

	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc = DirectXCommon::GetInstance()->GetDepthStencilDesc();

	graphicsPipelineStateDesc.pRootSignature = SpriteGraphicPipeline::GetInstance()->spritePso_.rootSignature; // RootSignature
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[2]{};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};

	// InputLayout
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;//SpriteGraphicPipeline::GetInstance()->inputLayoutDesc_; // InputLayout
	graphicsPipelineStateDesc.VS = {
		SpriteGraphicPipeline::GetInstance()->vertexShaderBlob_->GetBufferPointer(),
	SpriteGraphicPipeline::GetInstance()->vertexShaderBlob_->GetBufferSize() }; // VertexShader
	graphicsPipelineStateDesc.PS = {
		SpriteGraphicPipeline::GetInstance()->pixelShaderBlob_->GetBufferPointer(),
	SpriteGraphicPipeline::GetInstance()->pixelShaderBlob_->GetBufferSize() }; // PixelShader
	graphicsPipelineStateDesc.BlendState = SpriteGraphicPipeline::GetInstance()->blendDesc_; // BlendState
	graphicsPipelineStateDesc.RasterizerState = SpriteGraphicPipeline::GetInstance()->rasterizerDesc_; // RasterizeState


	// 書き込むRTVの情報
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;


	// 利用するトポロジ(形状)もタイプ。三角形
	graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


	// どのように画面に色を打ち込むかの設定(気にしなくて良い)
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;


	// Depthの機能を有効化する
	depthStencilDesc.DepthEnable = true;
	// 書き込む
	depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	// 比較関数はLessEqual。つまり、近ければ描画される
	depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	// DepthStencilの設定
	graphicsPipelineStateDesc.DepthStencilState = depthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;


	DirectXCommon::GetInstance()->SetDepthStencilDesc(depthStencilDesc);


	// 実際に生成
	HRESULT hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateGraphicsPipelineState(
		&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&SpriteGraphicPipeline::GetInstance()->spritePso_.graphicsPipelineState));
	assert(SUCCEEDED(hr_));

	SpriteGraphicPipeline::GetInstance()->graphicsPipelineStateDesc_ = graphicsPipelineStateDesc;
}