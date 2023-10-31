#pragma once


#include <d3dx12.h>
#include <dxcapi.h>

#include "Function.h"
#include "Struct.h"
#include "DirectXCommon.h"
#include "ShaderManager.h"



class LightGraphicPipeline {

public: // メンバ関数

	/// <summary>
	/// LightGraphicPipelineクラスのインスタンス取得
	/// </summary>
	static LightGraphicPipeline* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// PSOを設定する
	/// </summary>
	static void SetLightPso();

	/// <summary>
	/// LightPSOの取得
	/// </summary>
	static PsoProperty GetPsoProperty() { return LightGraphicPipeline::GetInstance()->lightPso_; }


private: // メンバ変数

	PsoProperty lightPso_{};
};