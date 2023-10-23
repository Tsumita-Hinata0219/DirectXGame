#pragma once


#include <d3dx12.h>
#include <dxcapi.h>

#include "Function.h"
#include "Struct.h"
#include "DirectXCommon.h"
#include "ShaderManager.h"



class SpriteGraphicPipeline {

public: // �����o�֐�

	/// <summary>
	/// SpriteGraphicPipeline�N���X�̃C���X�^���X�擾
	/// </summary>
	static SpriteGraphicPipeline* GetInstance();

	/// <summary>
	/// ����������
	/// </summary>
	static void Initialize();

	/// <summary>
	/// PSO��ݒ肷��
	/// </summary>
	static void SetSpritePso();


private: // �����o�֐�

	/// <summary>
	/// RootSignature���쐬
	/// </summary>
	static void MakeRootSignature();

	/// <summary>
	/// InputLayout��ݒ肷��
	/// </summary>
	static void SetInputLayout();

	/// <summary>
	/// BlendState��ݒ肷��
	/// </summary>
	static void SetBlendState();

	/// <summary>
	/// RasiterzerState��ݒ肷��
	/// </summary>
	static void SetRasiterzerState();

	/// <summary>
	/// Shader��compile����
	/// </summary>
	static void SetShaderCompile();

	/// <summary>
	/// PSO�𐶐�����
	/// </summary>
	static void CreatePipelineStateObject();


private: // �����o�ϐ�

	PsoProperty spritePso_;


	/* --- RootSignature���쐬 --- */
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature_{};
	D3D12_ROOT_PARAMETER rootParameters_[3]{};
	D3D12_DESCRIPTOR_RANGE descriptorRange_[1]{};
	D3D12_STATIC_SAMPLER_DESC staticSamplers_[1]{};


	/* --- InputLayout��ݒ肷�� --- */
	D3D12_INPUT_ELEMENT_DESC inputElementDescs_[3]{};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc_{};


	/* --- BlendState��ݒ肷�� --- */
	D3D12_BLEND_DESC blendDesc_{};


	/* --- RasiterzerState��ݒ肷�� --- */
	D3D12_RASTERIZER_DESC rasterizerDesc_{};


	/* --- Shader��compile���� --- */
	IDxcBlob* vertexShaderBlob_ = nullptr;
	IDxcBlob* pixelShaderBlob_ = nullptr;


	/* --- PSO�𐶐����� --- */
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc_{};
};