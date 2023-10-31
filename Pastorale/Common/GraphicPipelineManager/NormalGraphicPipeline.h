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


private: // メンバ変数

	PsoProperty normalPso_;
};