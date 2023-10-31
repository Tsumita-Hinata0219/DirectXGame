#pragma once


#include <d3dx12.h>
#include <dxcapi.h>

#include "Function.h"
#include "Struct.h"
#include "DirectXCommon.h"
#include "ShaderManager.h"



class NormalGraphicPipeline {

public: // メンバ関数

	/// <summary>
	/// NormalGraphicPipelineクラスのインスタンス取得
	/// </summary>
	static NormalGraphicPipeline* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// PSOを設定する
	/// </summary>
	static void SetNormalPso();

	/// <summary>
	/// ModelPSOの取得
	/// </summary>
	static PsoProperty GetPsoProperty() { return NormalGraphicPipeline::GetInstance()->normalPso_; }


private: // メンバ関数

	/// <summary>
	/// RootSignatureを作成
	/// </summary>
	static void MakeRootSignature();

	/// <summary>
	/// InputLayoutを設定する
	/// </summary>
	static void SetInputLayout();

	/// <summary>
	/// BlendStateを設定する
	/// </summary>
	static void SetBlendState();

	/// <summary>
	/// RasiterzerStateを設定する
	/// </summary>
	static void SetRasiterzerState();

	/// <summary>
	/// Shaderをcompileする
	/// </summary>
	static void SetShaderCompile();

	/// <summary>
	/// PSOを生成する
	/// </summary>
	static void CreatePipelineStateObject();


private: // メンバ変数

	PsoProperty normalPso_;


	/* --- RootSignatureを作成 --- */
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature_{};
	D3D12_ROOT_PARAMETER rootParameters_[3]{};
	D3D12_DESCRIPTOR_RANGE descriptorRange_[1]{};
	D3D12_STATIC_SAMPLER_DESC staticSamplers_[1]{};


	/* --- InputLayoutを設定する --- */
	D3D12_INPUT_ELEMENT_DESC inputElementDescs_[2]{};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc_{};


	/* --- BlendStateを設定する --- */
	D3D12_BLEND_DESC blendDesc_{};


	/* --- RasiterzerStateを設定する --- */
	D3D12_RASTERIZER_DESC rasterizerDesc_{};


	/* --- Shaderをcompileする --- */
	IDxcBlob* vertexShaderBlob_ = nullptr;
	IDxcBlob* pixelShaderBlob_ = nullptr;


	/* --- PSOを生成する --- */
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc_{};
};