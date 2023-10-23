#pragma once

#include <d3dx12.h>
#include <dxcapi.h>

#include "Function.h"
#include "Struct.h"
#include "DirectXCommon.h"
#include "ShaderManager.h"


class GraphicPipelineManager {

public: // メンバ関数

	/// <summary>
	/// PSOクラスのインスタンス取得
	/// </summary>
	static GraphicPipelineManager* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// PSOを設定するする
	/// </summary>
	static PsoProperty SetPSO(ShadersMode type);


#pragma region Get 取得

	/// <summary>
	/// 
	/// </summary>

#pragma endregion 


private: // メンバ変数

	SPSO sPso_;
};