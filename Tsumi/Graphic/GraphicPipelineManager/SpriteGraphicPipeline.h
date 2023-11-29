#pragma once


#include <d3dx12.h>
#include <dxcapi.h>

#include "Function.h"
#include "Struct.h"
#include "DirectXCommon.h"
#include "ShaderManager.h"



class SpriteGraphicPipeline {

public: // メンバ関数

	/// <summary>
	/// SpriteGraphicPipelineクラスのインスタンス取得
	/// </summary>
	static SpriteGraphicPipeline* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// PSOを設定する
	/// </summary>
	static void SetSpritePso();

	/// <summary>
	/// SpritePSOの取得
	/// </summary>
	static PsoProperty GetPsoProperty() { return SpriteGraphicPipeline::GetInstance()->spritePso_; }


private: // メンバ変数

	PsoProperty spritePso_;
};