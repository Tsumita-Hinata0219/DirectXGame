#pragma once


#include <d3dx12.h>
#include <dxcapi.h>

#include "Function.h"
#include "Struct.h"
#include "DirectXCommon.h"
#include "ShaderManager.h"


class NormalGraphicPipeline {

public: // ƒƒ“ƒoŠÖ”

	/// <summary>
	/// ‰Šú‰»ˆ—
	/// </summary>
	void Initialize();

	/// <summary>
	/// PSO‚ğİ’è‚·‚é
	/// </summary>
	void SetNormalPso();


private: // ƒƒ“ƒoŠÖ”

	/// <summary>
	/// RootSignature‚ğì¬
	/// </summary>
	void MakeRootSignature();

	/// <summary>
	/// InputLayout‚ğİ’è‚·‚é
	/// </summary>
	void SetInputLayout();

	/// <summary>
	/// BlendState‚ğİ’è‚·‚é
	/// </summary>
	void SetBlendState();

	/// <summary>
	/// RasiterzerState‚ğİ’è‚·‚é
	/// </summary>
	void SetRasiterzerState();

	/// <summary>
	/// Shader‚ğcompile‚·‚é
	/// </summary>
	void SetShaderCompile();

	/// <summary>
	/// PSO‚ğ¶¬‚·‚é
	/// </summary>
	void CreatePipelineStateObject();


private: // ƒƒ“ƒo•Ï”

	PsoProperty normalPso_;


	/* --- RootSignature‚ğì¬ --- */
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature_{};
	D3D12_ROOT_PARAMETER rootParameters_[3]{};
	D3D12_DESCRIPTOR_RANGE descriptorRange_[1]{};
	D3D12_STATIC_SAMPLER_DESC staticSamplers_[1]{};


	/* --- InputLayout‚ğİ’è‚·‚é --- */
	D3D12_INPUT_ELEMENT_DESC inputElementDescs_[3]{};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc_{};


	/* --- BlendState‚ğİ’è‚·‚é --- */
	D3D12_BLEND_DESC blendDesc_{};


	/* --- RasiterzerState‚ğİ’è‚·‚é --- */
	D3D12_RASTERIZER_DESC rasterizerDesc_{};


	/* --- Shader‚ğcompile‚·‚é --- */
	IDxcBlob* vertexShaderBlob_ = nullptr;
	IDxcBlob* pixelShaderBlob_ = nullptr;


	/* --- PSO‚ğ¶¬‚·‚é --- */
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc_{};
};