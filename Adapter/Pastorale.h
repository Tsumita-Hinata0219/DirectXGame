#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Model.h"


//Pastorale//パストラーレ
//PASTORALE ENGINE


class Pastorale {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Pastorale();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Pastorale();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="title"> タイトルバー </param>
	/// <param name="Width"> ウィンドウ縦幅 </param>
	/// <param name="Height"> ウィンドウ横幅 </param>
	void Initialize(const wchar_t* title, const int32_t Width, const int32_t Height);

	/// <summary>
	/// メッセージの処理
	/// </summary>
	bool ProcessMessage();

	/// <summary>
	/// フレームの開始
	/// </summary>
	void BeginFrame();

	/// <summary>
	/// フレームの終了
	/// </summary>
	void EndFrame();

	/// <summary>
	/// 三角形の描画
	/// </summary>
	/// <param name="bottomLeft"></param>
	/// <param name="top"></param>
	/// <param name="bottoomRight"></param>
	void DrawTriangle(Vector4 bottomLeft, Vector4 top, Vector4 bottoomRight, unsigned int color);

private:

	// WinAppの生成
	WinApp* winApp_ = nullptr;
	// DirectXCommonの生成
	DirectXCommon* dXCommon_ = nullptr;
	// Modelの生成
	Model* model_ = nullptr;




	// 頂点リソースにデータを書き込む
	Vector4* vertexData_ = nullptr;


	// 頂点リソース用のヒープ設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties_{};

	D3D12_RESOURCE_DESC vertexResourceDesc_{};

	ID3D12Resource* vertexResource_ = nullptr;


	// 頂点リソース用のヒープ設定
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
};

