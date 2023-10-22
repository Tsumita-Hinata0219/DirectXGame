#include "GraphicPipelineManager.h"


/// <summary>
/// PSOクラスのインスタンス取得
/// </summary>
GraphicPipelineManager* GraphicPipelineManager::GetInstance() {

	static GraphicPipelineManager instance;
	return &instance;
}



/// <summary>
/// 初期化処理
/// </summary>
void GraphicPipelineManager::Initialize() {

	SPSO sPso = GraphicPipelineManager::GetInstance()->sPso_;
	ShadersType shaders = ShaderManager::GetInstance()->GetShaderType();

	sPso.normal = SetPSO(shaders.Noraml);
	sPso.Sprite = SetPSO(shaders.Sprite);
	sPso.Light = SetPSO(shaders.Light);
}



/* --- PSOを設定する --- */

PsoProperty GraphicPipelineManager::SetPSO(ShadersMode type) {

	/* --- RootSignatureを作成 --- */
	//MakeRootSignature();
	// RootSignature作成
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	D3D12_ROOT_PARAMETER rootParameters[3]{};
	D3D12_DESCRIPTOR_RANGE descriptorRange[1]{};
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
	D3D12_STATIC_SAMPLER_DESC staticSamplers[1]{};
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
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr_ = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr_)) {
		Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	// バイナリを元に生成
	ID3D12RootSignature* rootSignature = nullptr;
	hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(hr_));



	/* --- InputLayoutを設定する --- */
	//SetInputLayout();
	// InputLayout
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3]{};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[2].SemanticName = "NORMAL";
	inputElementDescs[2].SemanticIndex = 0;
	inputElementDescs[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputElementDescs[2].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);



	/* --- BlendStateを設定する --- */
	//SetBlendState();
	// BlendStateの設定
	// 全ての色要素を書き込む
	D3D12_BLEND_DESC blendDesc{};
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;



	/* --- RasiterzerStateを設定する --- */
	//SetRasiterzerState();
	// RasiterzerStateの設定
	// 裏面(時計回り)を表示しない
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	// 三角形の中を塗りつぶす
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;



	/* --- Shaderをcompileする --- */
	//SetShaderCompile();
	// Shaderをコンパイルする
	IDxcBlob* vertexShaderBlob = nullptr;
	IDxcBlob* pixelShaderBlob = nullptr;
	vertexShaderBlob = DirectXCommon::GetInstance()->CompileShader(
		L"Resources/shaders/Object3d.VS.hlsl",
		L"vs_6_0",
		DirectXCommon::GetInstance()->GetDxcUtils(),
		DirectXCommon::GetInstance()->GetDxcCompiler(),
		DirectXCommon::GetInstance()->GetIncludeHandler());
	assert(vertexShaderBlob != nullptr);

	pixelShaderBlob = DirectXCommon::GetInstance()->CompileShader(
		L"Resources/shaders/Object3d.PS.hlsl",
		L"ps_6_0",
		DirectXCommon::GetInstance()->GetDxcUtils(),
		DirectXCommon::GetInstance()->GetDxcCompiler(),
		DirectXCommon::GetInstance()->GetIncludeHandler());
	assert(pixelShaderBlob != nullptr);



	/* --- PSOを生成する --- */
	//CreatePipelineStateObject();
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc = DirectXCommon::GetInstance()->GetDepthStencilDesc();
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	ID3D12PipelineState* graphicsPipelineState = nullptr;

	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.pRootSignature = GraphicPipelineManager::GetInstance()->usePso_.rootSignature; // RootSignature
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.InputLayout = GraphicPipelineManager::GetInstance()->usePso_.inputLayoutDesc; // InputLayout
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.VS = { GraphicPipelineManager::GetInstance()->usePso_.vertexShaderBlob->GetBufferPointer(),
	GraphicPipelineManager::GetInstance()->usePso_.vertexShaderBlob->GetBufferSize() }; // VertexShader
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.PS = { GraphicPipelineManager::GetInstance()->usePso_.pixelShaderBlob->GetBufferPointer(),
	GraphicPipelineManager::GetInstance()->usePso_.pixelShaderBlob->GetBufferSize() }; // PixelShader
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.BlendState = GraphicPipelineManager::GetInstance()->usePso_.blendDesc; // BlendState
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.RasterizerState = GraphicPipelineManager::GetInstance()->usePso_.rasterizerDesc; // RasterizeState


	// 書き込むRTVの情報
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.NumRenderTargets = 1;
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;


	// 利用するトポロジ(形状)もタイプ。三角形
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


	// どのように画面に色を打ち込むかの設定(気にしなくて良い)
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.SampleDesc.Count = 1;
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;


	// Depthの機能を有効化する
	depthStencilDesc.DepthEnable = true;
	// 書き込む
	depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	// 比較関数はLessEqual。つまり、近ければ描画される
	depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	// DepthStencilの設定
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.DepthStencilState = depthStencilDesc;
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;


	DirectXCommon::GetInstance()->SetDepthStencilDesc(depthStencilDesc);


	// 実際に生成
	HRESULT hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateGraphicsPipelineState(&GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc,
		IID_PPV_ARGS(&GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineState));
	assert(SUCCEEDED(hr_));
}



/* --- RootSignatureを作成 --- */

void GraphicPipelineManager::MakeRootSignature() {

	// RootSignature作成
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	D3D12_ROOT_PARAMETER rootParameters[3]{};
	D3D12_DESCRIPTOR_RANGE descriptorRange[1]{};
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
	D3D12_STATIC_SAMPLER_DESC staticSamplers[1]{};
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
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr_ = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr_)) {
		Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	// バイナリを元に生成
	ID3D12RootSignature* rootSignature = nullptr;
	hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(hr_));
}



/* --- InputLayoutを設定する --- */

void GraphicPipelineManager::SetInputLayout() {

	// InputLayout
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3]{};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[2].SemanticName = "NORMAL";
	inputElementDescs[2].SemanticIndex = 0;
	inputElementDescs[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputElementDescs[2].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);
}



/* --- BlendStateを設定する --- */

void GraphicPipelineManager::SetBlendState() {

	// BlendStateの設定
	// 全ての色要素を書き込む
	D3D12_BLEND_DESC blendDesc{};
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
}



/* --- RasiterzerStateを設定する --- */

void GraphicPipelineManager::SetRasiterzerState() {

	// RasiterzerStateの設定
	// 裏面(時計回り)を表示しない
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	// 三角形の中を塗りつぶす
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
}



/* --- Shaderをcompileする --- */

void GraphicPipelineManager::SetShaderCompile() {

	// Shaderをコンパイルする
	IDxcBlob* vertexShaderBlob = nullptr;
	IDxcBlob* pixelShaderBlob = nullptr;
	vertexShaderBlob = DirectXCommon::GetInstance()->CompileShader(
		L"Resources/shaders/Object3d.VS.hlsl",
		L"vs_6_0",
		DirectXCommon::GetInstance()->GetDxcUtils(),
		DirectXCommon::GetInstance()->GetDxcCompiler(),
		DirectXCommon::GetInstance()->GetIncludeHandler());
	assert(vertexShaderBlob != nullptr);

	pixelShaderBlob = DirectXCommon::GetInstance()->CompileShader(
		L"Resources/shaders/Object3d.PS.hlsl",
		L"ps_6_0",
		DirectXCommon::GetInstance()->GetDxcUtils(),
		DirectXCommon::GetInstance()->GetDxcCompiler(),
		DirectXCommon::GetInstance()->GetIncludeHandler());
	assert(pixelShaderBlob != nullptr);
}



/* --- PSOを生成する --- */

void GraphicPipelineManager::CreatePipelineStateObject() {

	D3D12_DEPTH_STENCIL_DESC depthStencilDesc = DirectXCommon::GetInstance()->GetDepthStencilDesc();
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	ID3D12PipelineState* graphicsPipelineState = nullptr;

	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.pRootSignature = GraphicPipelineManager::GetInstance()->usePso_.rootSignature; // RootSignature
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.InputLayout = GraphicPipelineManager::GetInstance()->usePso_.inputLayoutDesc; // InputLayout
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.VS = { GraphicPipelineManager::GetInstance()->usePso_.vertexShaderBlob->GetBufferPointer(),
	GraphicPipelineManager::GetInstance()->usePso_.vertexShaderBlob->GetBufferSize() }; // VertexShader
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.PS = { GraphicPipelineManager::GetInstance()->usePso_.pixelShaderBlob->GetBufferPointer(),
	GraphicPipelineManager::GetInstance()->usePso_.pixelShaderBlob->GetBufferSize() }; // PixelShader
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.BlendState = GraphicPipelineManager::GetInstance()->usePso_.blendDesc; // BlendState
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.RasterizerState = GraphicPipelineManager::GetInstance()->usePso_.rasterizerDesc; // RasterizeState


	// 書き込むRTVの情報
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.NumRenderTargets = 1;
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;


	// 利用するトポロジ(形状)もタイプ。三角形
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


	// どのように画面に色を打ち込むかの設定(気にしなくて良い)
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.SampleDesc.Count = 1;
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;


	// Depthの機能を有効化する
	depthStencilDesc.DepthEnable = true;
	// 書き込む
	depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	// 比較関数はLessEqual。つまり、近ければ描画される
	depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	// DepthStencilの設定
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.DepthStencilState = depthStencilDesc;
	GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;


	DirectXCommon::GetInstance()->SetDepthStencilDesc(depthStencilDesc);


	// 実際に生成
	HRESULT hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateGraphicsPipelineState(&GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineStateDesc,
		IID_PPV_ARGS(&GraphicPipelineManager::GetInstance()->usePso_.graphicsPipelineState));
	assert(SUCCEEDED(hr_));
}
