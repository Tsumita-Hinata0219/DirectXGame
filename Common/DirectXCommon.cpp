#include "DirectXCommon.h"



void DirectXCommon::Initialize(int32_t ClientWidth, int32_t ClientHeight, HWND hwnd) {

	ClientWidth_ = ClientWidth;
	ClientHeight_ = ClientHeight;
	hwnd_ = hwnd;


	/* ----- デバッグレイヤー -----*/
#ifdef _DEBUG

	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController_)))) {
		// デバッグレイヤーを有効にする
		debugController_->EnableDebugLayer();
		// さらにGPU側でもチェックを行うようにする
		debugController_->SetEnableGPUBasedValidation(TRUE);
	}

#endif // _DEBUG



	// DxgiFactoryを生成する
	CreateDxgiFactory();

	// D3D12Deviceを生成する
	CreateDevice();

	// エラーと警告の抑制
	DebugErrorInfoQueue();

	// コマンドキューを生成する
	CreateCommandQueue();

	// コマンドアロケータを生成する
	CreateCommandAllocator();

	// コマンドを生成する
	CreateCommandList();

	// スワップチェーンを生成する
	CreateSwapChain();

	// ディスクリプタヒープの生成
	CreateRtvDescriptorHeap();

	// フェンスを作る
	MakeFence();

	// DXCの初期化
	InitializeDXC();

	// PSOを設定する
	SetPSO();

	// ViewportとScissor
	SetViewport();
	SetScissor();
}



// 解放処理
void DirectXCommon::Release() {

	CloseHandle(fenceEvent_);
	fence_->Release();
	graphicsPipelineState_->Release();
	signatureBlob_->Release();
	if (errorBlob_) {
		errorBlob_->Release();
	}
	rootSignature_->Release();
	pixelShaderBlob_->Release();
	vertexShaderBlob_->Release();


	rtvDescriptorHeap_->Release();
	swapChainResources_[0]->Release();
	swapChainResources_[1]->Release();

	swapChain_->Release();
	commandList_->Release();
	commandAllocator_->Release();
	commandQueue_->Release();

	device_->Release();
	useAdapter_->Release();
	dxgiFactory_->Release();
}



void DirectXCommon::PreDraw() {

	// コマンドを積み込んで確定させる
	// これから書き込むバックバッファのインデックスを取得
	UINT backBufferIndex_ = swapChain_->GetCurrentBackBufferIndex();


	// Barrierを設定する
	// 今回のバリアはTransition
	barrier_.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	// Noneにしておく
	barrier_.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	// バリアを張る対象のリソース。現在のバックバッファに対して行う
	barrier_.Transition.pResource = swapChainResources_[backBufferIndex_];
	// 遷移前(現在)のResourceState
	barrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	// 遷移後のResourceState
	barrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	// TransitionBarrierを張る
	commandList_->ResourceBarrier(1, &barrier_);


	// 描画先のRTVを設定する
	commandList_->OMSetRenderTargets(
		1, &rtvHandles_[backBufferIndex_],
		false,
		nullptr);


	// 指定した色で画面全体をクリアする
	float clearColor[] = { 0.1f, 0.25f, 0.5f, 1.0f }; // 青っぽい色。RGBAの順

	commandList_->ClearRenderTargetView(
		rtvHandles_[backBufferIndex_],
		clearColor,
		0, nullptr);

	// いざ描画！！！！！
	commandList_->RSSetViewports(1, &viewport_); // Viewportを設定
	commandList_->RSSetScissorRects(1, &scissorRect_); // Scissorを設定
	// RootSignatureを設定。PSOに設定してるけど別途設定が必要
	commandList_->SetGraphicsRootSignature(rootSignature_);
	commandList_->SetPipelineState(graphicsPipelineState_); // PSOを設定
}


void DirectXCommon::PostDraw() {

	// 状態を遷移
	// 画面に描く処理はすべて終わり、画面に映すので、状態を遷移
	// 今回はRenderTargetからPresentにする
	barrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

	// TransitionBarrierを張る
	commandList_->ResourceBarrier(1, &barrier_);


	// コマンドをキックする
	// コマンドリストの内容を確定させる・全てのコマンドを積んでからCloseすること
	hr_ = commandList_->Close();
	assert(SUCCEEDED(hr_));

	// GPUにコマンドリストの実行を行わせる
	ID3D12CommandList* commandLists[] = { commandList_ };
	commandQueue_->ExecuteCommandLists(1, commandLists);


	// GPUとOSに画面の交換を行うよう通知する
	swapChain_->Present(0, 1);


	// Fenceの値を更新
	fenceValue_++;

	// GPUがここまで辿り着いたときに、Fenceの値を指定した値に代入するようにSignalを送る
	commandQueue_->Signal(fence_, fenceValue_);

	// Fenceの値が指定したSignal値にたどり着いているか確認するか
	// GetCompletedValueの初期値はFence作成時に渡した初期値
	if (fence_->GetCompletedValue() < fenceValue_) {
		// 指定したSignalにたどりついていないので、辿り着くまで待つようにイベントを設定する
		fence_->SetEventOnCompletion(fenceValue_, fenceEvent_);
		// イベントを待つ
		WaitForSingleObject(fenceEvent_, INFINITE);
	}

	swapChain_->Present(1, 0);

	// 次のフレーム用のコマンドリストを準備
	hr_ = commandAllocator_->Reset();
	assert(SUCCEEDED(hr_));
	hr_ = commandList_->Reset(commandAllocator_, nullptr);
	assert(SUCCEEDED(hr_));
}



/* ---DirectX初期化--- */
/// ここから↓
//////////////////////////////

void DirectXCommon::CreateDxgiFactory() {

	// DXGIファクトリーの生成
	// HRESULTはWindows系のエラーコードであり、
	// 関数が成功したかどうかをSUCCEEDEDマクロで判定できる
	dxgiFactory_ = nullptr;
	hr_ = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory_));

	// 初期化の根本的な部分でエラーが出た場合はプログラムが間違ってるかどうか、
	// どうにもできない場合が多いのでassertにしておく
	assert(SUCCEEDED(hr_));



	// いい順にアダプタを頼む
	for (UINT i = 0; dxgiFactory_->EnumAdapterByGpuPreference(i,
		DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter_)) !=
		DXGI_ERROR_NOT_FOUND; i++)
	{
		// アダプターの情報を取得する
		DXGI_ADAPTER_DESC3 adapterDesc{};
		hr_ = useAdapter_->GetDesc3(&adapterDesc);
		assert(SUCCEEDED(hr_)); // 取得できないのは一大事

		// ソフトウェアアダプタ出なければ採用！
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			// 採用したアダプタの情報をログに出力。wstringのほうなので注意
			Log(ConvertString(std::format(L"USE Adapater:{}\n", adapterDesc.Description)));
			break;
		}
		useAdapter_ = nullptr; // ソフトウェアアダプタの場合は見なかったことにする
	}
	// 適切なアダプタが見つからなかったので起動できない
	assert(useAdapter_ != nullptr);
}



/* ----- D3D12Deviceを生成する ----- */

void DirectXCommon::CreateDevice() {

	// 昨日レベルとログ出力用の文字列
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_12_2,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0
	};

	const char* featureLevelStrings[] = { "12.2", "12.1", "12.0" };


	// 高い順に生成できるか試していく
	for (size_t i = 0; i < _countof(featureLevels); ++i) {
		// 採用したアダプターでデバイスを生成
		hr_ = D3D12CreateDevice(useAdapter_, featureLevels[i], IID_PPV_ARGS(&device_));
		
		// 指定した昨日レベルでデバイスが生成できたかを確認
		if (SUCCEEDED(hr_)) {
			// 生成できたのでログ出力を行ってループを抜ける
			Log(std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
			break;
		}
	}

	// デバイスの生成がうまく行かなかったので起動できない
	assert(device_ != nullptr);
	Log("Complete create D3D12Device!!!\n"); // 初期化完了のログを出す

}

//////////////////////////////
/// ここまで↑
/* ---DirectX初期化--- */



/* ----- エラーと警告の抑制 ----- */

void DirectXCommon::DebugErrorInfoQueue() {


#ifdef _DEBUG

	if (SUCCEEDED(device_->QueryInterface(IID_PPV_ARGS(&infoQueue_)))) {

		// ヤバいエラー時に止まる
		infoQueue_->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);

		// エラー時に止まる
		infoQueue_->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);

		// 警告時に止まる
		infoQueue_->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);


		// 抑制するメッセージのID
		D3D12_MESSAGE_ID denyIds_[] = {
			// Windows11でのDXGIデバッグレイヤーとDX12デバッグレイヤーの相互作用バグによるエラーメッセージ
			// https://stackoverflow.com/questions/69805245/directx-12-application-is-crashing-in-windows-11
			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};

		//抑制するレベル
		D3D12_MESSAGE_SEVERITY severities_[] = { D3D12_MESSAGE_SEVERITY_INFO };
		filter_.DenyList.NumIDs = _countof(denyIds_);
		filter_.DenyList.pIDList = denyIds_;
		filter_.DenyList.NumSeverities = _countof(severities_);
		filter_.DenyList.pSeverityList = severities_;
		// 指定したメッセージの表示を抑制する
		infoQueue_->PushStorageFilter(&filter_);


		// 解放
		infoQueue_->Release();
	}

#endif // _DEBUG
}



/* ----- コマンドキューを生成する ----- */

void DirectXCommon::CreateCommandQueue() {

	// コマンドキューを生成する
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	hr_ = device_->CreateCommandQueue(
		&commandQueueDesc,
		IID_PPV_ARGS(&commandQueue_));


	// コマンドキューの生成がうまくいかなかったので起動できない
	assert(SUCCEEDED(hr_));
}



/* ----- コマンドアロケータを生成する ----- */
void DirectXCommon::CreateCommandAllocator() {

	// コマンドアロケータを生成する
	hr_ = device_->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&commandAllocator_));


	// コマンドアロケータの生成がうまくいかなかったので起動できない
	assert(SUCCEEDED(hr_));
}



/* ----- コマンドリストを生成する ----- */

void DirectXCommon::CreateCommandList() {

	// コマンドリストを生成する
	hr_ = device_->CreateCommandList(
		0, D3D12_COMMAND_LIST_TYPE_DIRECT, 
		commandAllocator_, 
		nullptr,
		IID_PPV_ARGS(&commandList_));


	// コマンドリストの生成がうまくいかなかったので起動できない
	assert(SUCCEEDED(hr_));
}



/* ----- スワップチェーンを生成する ----- */

void DirectXCommon::CreateSwapChain() {

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	swapChainDesc.Width = ClientWidth_;	  // 画面の幅、ウィンドウのクライアント領域を同じものにしてく
	swapChainDesc.Height = ClientHeight_; // 画面の高さ、ウィンドウのクライアント領域を同じものにしておく
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 色の形式
	swapChainDesc.SampleDesc.Count = 1; // マルチサンプルしない
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 描画のターゲットとして利用する
	swapChainDesc.BufferCount = 2; // ダブルバッファ
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // モニタにうつしたら、中身を破棄

	// コマンドキュー、ウィンドウハンドル、設定を渡して生成する
	hr_ = dxgiFactory_->CreateSwapChainForHwnd(
		commandQueue_, 
		hwnd_,
		&swapChainDesc, 
		nullptr, 
		nullptr, 
		reinterpret_cast<IDXGISwapChain1**>(&swapChain_));

	assert(SUCCEEDED(hr_));
}



/* ----- ディスクリプタヒープの生成 ----- */

void DirectXCommon::CreateRtvDescriptorHeap() {

	D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc{};

	// レンダーターゲットビュー用
	rtvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; 

	// ダブルバッファように二つ。多くても別に構わない
	rtvDescriptorHeapDesc.NumDescriptors = 2; 
	hr_ = device_->CreateDescriptorHeap(
		&rtvDescriptorHeapDesc, 
		IID_PPV_ARGS(&rtvDescriptorHeap_));

	// ディスクリプタヒープが作れなかったので起動できない
	assert(SUCCEEDED(hr_));


	// SwapChainからResourceを引っ張ってくる
	CreateSwapChainResources();


	// RTVを作る
	SettingRTV();
}



/* ----- SwapChainからResourceを引っ張ってくる ----- */

void DirectXCommon::CreateSwapChainResources() {

	hr_ = swapChain_->GetBuffer(0, IID_PPV_ARGS(&swapChainResources_[0]));

	// うまく取得できなければ起動できない
	assert(SUCCEEDED(hr_));


	hr_ = swapChain_->GetBuffer(1, IID_PPV_ARGS(&swapChainResources_[1]));

	// うまく取得できなければ起動できない
	assert(SUCCEEDED(hr_));
}



/* ----- RTVを作る ----- */

void DirectXCommon::SettingRTV() {

	// RTVの設定
	rtvDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 出力結果をSRGBに変換して書き込む
	rtvDesc_.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D; // 2sテクスチャとして書き込む

	// ディスクリプタの先頭を取得する
	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle = rtvDescriptorHeap_->GetCPUDescriptorHandleForHeapStart();

	// まず1つ目を作る。1つ目は最初のところに作る。作る場所をこちらで指定してあげる必要がある
	rtvHandles_[0] = rtvStartHandle;
	device_->CreateRenderTargetView(
		swapChainResources_[0], 
		&rtvDesc_, 
		rtvHandles_[0]);

	// 2つ目のディスクリプタハンドルを得る(自力で)
	rtvHandles_[1].ptr = 
		rtvHandles_[0].ptr + device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	// 2つ目を作る
	device_->CreateRenderTargetView(
		swapChainResources_[1], 
		&rtvDesc_, 
		rtvHandles_[1]);


	////DescriptorHandleとDescriptorHeap
	typedef struct D3D12_CPU_DESCRIPTOR_HANDLE {
		SIZE_T ptr;
	}D3D12_CPU_DESCRIPTOR_HANDLE;

	////Descriptorの位置を決める
	rtvHandles_[0] = rtvStartHandle;

	rtvHandles_[1].ptr = 
		rtvHandles_[0].ptr + device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

}



// 状態を遷移する
void DirectXCommon::ChanegResourceState() {

	// 画面に描く処理はすべて終わり、画面に映すので、状態を遷移
	// 今回はRenderTargetからPresentにする
	barrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

	// TransitionBarrierを張る
	commandList_->ResourceBarrier(1, &barrier_);
}



/* ----- Fenceを生成する ----- */

void DirectXCommon::MakeFence() {

	// 初期値0でFenceを作る
	hr_ = device_->CreateFence(fenceValue_, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_));
	assert(SUCCEEDED(hr_));
	// FenceのSignalを待つためのイベントを作成する
	HANDLE fenceEvent_ = CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(fenceEvent_ != nullptr);
}



/* ----- DXCの初期化 ----- */

void DirectXCommon::InitializeDXC() {

	// dxcCompilerを初期化
	hr_ = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils_));
	assert(SUCCEEDED(hr_));
	hr_ = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler_));
	assert(SUCCEEDED(hr_));


	// 現時点でincludeはしないが、includeに対応するための設定を行っておく
	hr_ = dxcUtils_->CreateDefaultIncludeHandler(&includeHandler_);
	assert(SUCCEEDED(hr_));
}



/* ----- CompileShader関数 ----- */

IDxcBlob* DirectXCommon::CompileShader(
	// CompilerするShaderファイルへのパス
	const std::wstring& filePath,
	// Compilerに使用するProfile
	const wchar_t* profile,
	// 初期化で生成したものを3つ
	IDxcUtils* dxcUtils,
	IDxcCompiler3* dxcCompiler,
	IDxcIncludeHandler* includeHandler)
{
	/* --- 1. hlslファイルを読む --- */

	// これからシェーダーをコンパイルする旨をログに出す
	Log(ConvertString(std::format(L"Begin CompileShader, path:{}, profile:{}\n", filePath, profile)));
	// hlslを読み込む
	HRESULT hr_ = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource_);
	// 読み込めなかったら止める
	assert(SUCCEEDED(hr_));
	// 読み込んだファイルの内容を設定する
	shaderSourceBuffer_.Ptr = shaderSource_->GetBufferPointer();
	shaderSourceBuffer_.Size = shaderSource_->GetBufferSize();
	shaderSourceBuffer_.Encoding = DXC_CP_UTF8; // UTF8の文字コードであることを通知


	/* --- 2.Compilerする --- */

	LPCWSTR arguments[] = {
		filePath.c_str(),  // コンパイル対象のhlslファイル名
		L"-E", L"main",  // エントリーポイントの指定。基本的にmain以外にはしない
		L"-T", profile,  // ShaderProfileの設定
		L"-Zi", L"-Qembed_debug",  // デバッグ用の情報を埋め込む
		L"-Od",  // 最適化を外しておく
		L"-Zpr",  // メモリレイアウトは行優先
	};
	// 実際にShaderをコンパイルする
	hr_ = dxcCompiler->Compile(
		&shaderSourceBuffer_,        // 読み込んだファイル
		arguments,					// コンパイルオプション
		_countof(arguments),		// コンパイルオプションの数
		includeHandler,				// includeが含まれた諸々
		IID_PPV_ARGS(&shaderResult_)	// コンパイル結果
	);
	// コンパイルエラーではなくdxcが起動できないなど致命的な状況
	assert(SUCCEEDED(hr_));


	/* --- 3. 警告・エラーが出てないか確認する --- */

	shaderResult_->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError_), nullptr);
	if (shaderError_ != nullptr && shaderError_->GetStringLength() != 0) {
		// 警告・エラーゼッタイ
		Log(shaderError_->GetStringPointer());
		assert(false);
	}


	/* --- 4. Compiler結果を受け取って返す --- */

	// コンパイル結果から実行用のバイナリ部分を取得
	hr_ = shaderResult_->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob_), nullptr);
	assert(SUCCEEDED(hr_));
	// 成功したログを出す
	Log(ConvertString(std::format(L"Compile Succeded, path{}, profile:{}\n", filePath, profile)));
	// もう使わないリソースを解放
	shaderSource_->Release();
	shaderResult_->Release();
	// 実行用のバイナリを返却
	return shaderBlob_;
}



/* --- RootSignatureを作成 --- */

void DirectXCommon::MakeRootSignature() {

	// RootSignature作成
	descriptionRootSignature_.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	// シリアライズしてバイナリにする
	hr_ = D3D12SerializeRootSignature(&descriptionRootSignature_,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob_, &errorBlob_);
	if (FAILED(hr_)) {
		Log(reinterpret_cast<char*>(errorBlob_->GetBufferPointer()));
		assert(false);
	}
	// バイナリを元に生成
	hr_ = device_->CreateRootSignature(0, signatureBlob_->GetBufferPointer(),
		signatureBlob_->GetBufferSize(), IID_PPV_ARGS(&rootSignature_));
	assert(SUCCEEDED(hr_));
}



/* --- InputLayoutを設定する --- */

void DirectXCommon::SetInputLayout() {

	// InputLayout
	inputElementDescs_[0].SemanticName = "POSITION";
	inputElementDescs_[0].SemanticIndex = 0;
	inputElementDescs_[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs_[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputLayoutDesc_.pInputElementDescs = inputElementDescs_;
	inputLayoutDesc_.NumElements = _countof(inputElementDescs_);
}



/* --- BlendStateを設定する --- */

void DirectXCommon::SetBlendState() {

	// BlendStateの設定
	// 全ての色要素を書き込む
	blendDesc_.RenderTarget[0].RenderTargetWriteMask =
		D3D12_COLOR_WRITE_ENABLE_ALL;
}



/* --- RasiterzerStateを設定する --- */

void DirectXCommon::SetRasiterzerState() {

	// RasiterzerStateの設定
	// 裏面(時計回り)を表示しない
	rasterizerDesc_.CullMode = D3D12_CULL_MODE_BACK;
	// 三角形の中を塗りつぶす
	rasterizerDesc_.FillMode = D3D12_FILL_MODE_SOLID;
}



/* --- Shaderをcompileする --- */

void DirectXCommon::SetShaderCompile() {

	// Shaderをコンパイルする
	vertexShaderBlob_ = CompileShader(L"Object3d.VS.hlsl",
		L"vs_6_0", dxcUtils_, dxcCompiler_, includeHandler_);
	assert(vertexShaderBlob_ != nullptr);
	pixelShaderBlob_ = CompileShader(L"Object3d.PS.hlsl",
		L"ps_6_0", dxcUtils_, dxcCompiler_, includeHandler_);
	assert(pixelShaderBlob_ != nullptr);
}



/* --- PSOを生成する --- */

void DirectXCommon::CreatePipelineStateObject() {

	graphicsPipelineStateDesc_.pRootSignature = rootSignature_; // RootSignature
	graphicsPipelineStateDesc_.InputLayout = inputLayoutDesc_; // InputLayout
	graphicsPipelineStateDesc_.VS = { vertexShaderBlob_->GetBufferPointer(),
	vertexShaderBlob_->GetBufferSize() }; // VertexShader
	graphicsPipelineStateDesc_.PS = { pixelShaderBlob_->GetBufferPointer(),
	pixelShaderBlob_->GetBufferSize() }; // PixelShader
	graphicsPipelineStateDesc_.BlendState = blendDesc_; // BlendState
	graphicsPipelineStateDesc_.RasterizerState = rasterizerDesc_; // RasterizeState


	// 書き込むRTVの情報
	graphicsPipelineStateDesc_.NumRenderTargets = 1;
	graphicsPipelineStateDesc_.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;


	// 利用するトポロジ(形状)もタイプ。三角形
	graphicsPipelineStateDesc_.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


	// どのように画面に色を打ち込むかの設定(気にしなくて良い)
	graphicsPipelineStateDesc_.SampleDesc.Count = 1;
	graphicsPipelineStateDesc_.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;


	// 実際に生成
	hr_ = device_->CreateGraphicsPipelineState(&graphicsPipelineStateDesc_,
		IID_PPV_ARGS(&graphicsPipelineState_));
	assert(SUCCEEDED(hr_));
}



/* --- PSOを設定する --- */

void DirectXCommon::SetPSO() {

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



/* ----- ViewportとScissor ----- */

void DirectXCommon::SetViewport() {

	// ビューポート
	// クライアント領域のサイズと一緒にして画面全体に表示
	viewport_.Width = float(ClientWidth_);
	viewport_.Height = float(ClientHeight_);
	viewport_.TopLeftX = 0;
	viewport_.TopLeftY = 0;
	viewport_.MinDepth = 0.0f;
	viewport_.MaxDepth = 1.0f;
}

void DirectXCommon::SetScissor() {

	// シザー矩形
	// 基本的にビューポートと同じ矩形が構成されるようにする
	scissorRect_.left = 0;
	scissorRect_.right = ClientWidth_;
	scissorRect_.top = 0;
	scissorRect_.bottom = ClientHeight_;
}

