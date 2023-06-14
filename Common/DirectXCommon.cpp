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



	/* ----- エラーと警告の抑制 ----- */
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


void DirectXCommon::Release() {

	CloseHandle(fenceEvent_);
	fence_->Release();


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
		//infoQueue_->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);


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
